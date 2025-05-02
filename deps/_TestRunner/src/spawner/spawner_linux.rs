use std::ffi::CString;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::iter::Enumerate;
use std::os::fd::FromRawFd;
use std::os::fd::IntoRawFd;
use std::os::fd::OwnedFd;
use std::sync::mpsc;
use std::sync::mpsc::Receiver;
use std::sync::mpsc::Sender;
use std::thread;
use std::thread::sleep;
use std::time::Duration;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::Ordering;

use crate::TestRecordHolder::TRecord;
use crate::DEFAULT_POOL_COUNT;


use nix::libc::posix_spawn;
use nix::libc::posix_spawn_file_actions_destroy;
use nix::libc::waitpid;
use nix::libc::WEXITSTATUS;
use nix::libc::WIFEXITED;
use nix::libc::WIFSIGNALED;
use nix::libc::WIFSTOPPED;
use nix::libc::WNOHANG;
use nix::libc::WSTOPSIG;
use nix::libc::WTERMSIG;
use nix::{libc::{self, posix_spawn_file_actions_adddup2, posix_spawn_file_actions_init, posix_spawn_file_actions_t}};
use termion::color;

use crate::collect::FileCollection;

#[derive(Debug)]
enum SyncronizeErr{
    CorruptedData
}

#[derive(Debug)]
enum SpawnErr{
    FailedToConvertCChar,
    SpawnChildFailed
}

#[derive(Debug)]
enum ProcessErr{
    FailedExit,
    Crashed,
    Stopped,
    UndefinedTermination,
}

fn init_pipe_with_file_action() -> (Vec<OwnedFd>, Vec<OwnedFd>, Vec<posix_spawn_file_actions_t>) {

    let mut readfd_list = Vec::<OwnedFd>::with_capacity(DEFAULT_POOL_COUNT);
    let mut writefd_list = Vec::<OwnedFd>::with_capacity(DEFAULT_POOL_COUNT);
    let mut action_files: Vec<posix_spawn_file_actions_t> = Vec::with_capacity(DEFAULT_POOL_COUNT);

    for _ in 0..DEFAULT_POOL_COUNT{
        let (readfd, writefd) = unistd::pipe().expect("Failed to create pipelines");

        action_files.push(
            file_action_init(&readfd, &writefd)
        );

        readfd_list.push(readfd);
        writefd_list.push(writefd);
    }

    (readfd_list, writefd_list, action_files)
}


fn file_action_init(
    readfd: &OwnedFd,
    writefd: & OwnedFd
) -> posix_spawn_file_actions_t {  

    let mut file_action: posix_spawn_file_actions_t = unsafe { std::mem::zeroed() };

    use std::os::fd::AsRawFd;

    use nix::libc::posix_spawn_file_actions_addclose;

    let raw_file_action: *mut _ = &mut file_action;
    unsafe {
        posix_spawn_file_actions_init(raw_file_action); 

        posix_spawn_file_actions_adddup2(raw_file_action, writefd.as_raw_fd(), libc::STDOUT_FILENO);

        posix_spawn_file_actions_addclose(raw_file_action, writefd.as_raw_fd());
        posix_spawn_file_actions_addclose(raw_file_action, readfd.as_raw_fd());
    }

    file_action
}



use std::sync::Arc;
use nix::unistd;




fn spawn_process(
    pid: &mut libc::pid_t,
    exe_str: &str,
    file_action: &posix_spawn_file_actions_t
) -> Result<(), SpawnErr>{
    let pid_ref = pid as *mut _;

    let exe = CString::new(exe_str)
        .map_err(|_| SpawnErr::FailedToConvertCChar)?;

    let file_action = file_action as *const _;

    let argv = [exe.as_ptr(), std::ptr::null()];

    let ret;
    unsafe {
        ret = posix_spawn(
            pid_ref,
            exe.as_ptr(),
            file_action,
            std::ptr::null(),
            argv.as_ptr() as *mut _,
            std::ptr::null()
        );
    }

    if ret != 0 {
        return Err(SpawnErr::SpawnChildFailed);
    }

    Ok(())
} 

fn read_pid_status(
    pid: &libc::pid_t,
    origin: &str,
) -> Result<bool, ProcessErr>{

    let mut status: libc::c_int = 0;

    let pid_r = unsafe {
        waitpid(*pid, &mut status as *mut _, WNOHANG)
    };

    if pid_r == 0 {
        //process still runing

        println!(
            "{}[ Running... ] {}{}",
            termion::color::Fg(color::Rgb(255, 195, 51)),
            origin,
            termion::color::Fg(color::Reset)
        );
        return Ok(false);
    }

    if WIFEXITED(status) {
        // Process returned from main

        let exit_stat = WEXITSTATUS(status);
        if exit_stat == 0 {

            println!(
                "{}[ Finished Executing - {} ]{}",
                termion::color::Fg(color::Green),
                origin,
                termion::color::Fg(color::Reset)
            );

            return Ok(true);
        } else {

            println!(
                "{}[ Failed - {} ]{}",
                termion::color::Fg(color::Red),
                origin,
                termion::color::Fg(color::Reset)
            );

            return Err(ProcessErr::FailedExit);
        }

    } else if WIFSIGNALED(status) {
        // Process crashed from segfault

        let signal = WTERMSIG(status);
        println!(
            "{}[ Process Crashed: Origin:{}, Signal:{} ]{}",
            termion::color::Fg(color::Red),
            origin,
            signal,
            termion::color::Fg(color::Reset)
        );
        return Err(ProcessErr::Crashed);
        
    } else if WIFSTOPPED(status) {

        let signal = WSTOPSIG(status);
        println!(
            "{}[ Process Stopped: Origin:{}, Signal:{} ]{}",
            termion::color::Fg(color::Red),
            origin,
            signal,
            termion::color::Fg(color::Reset)
        );
        return Err(ProcessErr::Stopped);

    } 
    
    Err(ProcessErr::UndefinedTermination)
}


fn fill_spawn_pool(
    pid: &mut libc::pid_t,
    pid_index_ref: &mut usize,
    file_details: (usize, &(String, String)),
    file_action: &posix_spawn_file_actions_t
){
    
    //spawn new process
    let stat = spawn_process(
        pid,
        file_details.1.1.as_str(),
        &file_action
    );

    match stat {
        Ok(_) => {
            println!(
                "{}[ Executing: {} ]{}",
                color::Fg(color::Rgb(255, 195, 51)),
                file_details.1.0,
                color::Fg(color::Reset)
            );
            *pid_index_ref = file_details.0;
        },
        Err(e) => {
            println!(
                "{}[ Set-up Failed: {} [{:?}]]{}",
                color::Fg(color::Magenta),
                file_details.0,
                e,
                color::Fg(color::Reset)
            );
        },
    }   

}



type PidsTrack = ([libc::pid_t; DEFAULT_POOL_COUNT], [usize; DEFAULT_POOL_COUNT] );

pub fn spawn_executable(fc: FileCollection){
    
    let (readfd_list,writefd_list,mut file_actions) = init_pipe_with_file_action();

    let mut pids: PidsTrack = ([-1; DEFAULT_POOL_COUNT],[0; DEFAULT_POOL_COUNT]);
    let mut file_iter = fc.exe_info.iter().enumerate();

    let flag = Arc::new(AtomicBool::new(true));
    let reports = Arc::new(TRecord::new());
    

    
    //start thread to read from pipline
    let pipeline_worker;
    let record_worker;
    {
        let flag_clone = flag.clone();
        let flag_clone2 = flag.clone();
        let report_clone = reports.clone();

        let (sender, reciever) = mpsc::channel::<String>();
        
        pipeline_worker = thread::spawn( move || {
            read_pipeline(readfd_list, sender, flag_clone)
        });
        record_worker = thread::spawn(move || {
            format_info_worker(report_clone, reciever, flag_clone2);
        }) 
    }


    let mut executable_left = fc.len();

    while executable_left > 0 {
        
        for i in 0..DEFAULT_POOL_COUNT {
            if pids.0[i] != -1 {continue;}
            let Some(file_detials) = file_iter.next() else {
                break;
            };


            fill_spawn_pool(
                &mut pids.0[i], 
                &mut pids.1[i], 
                file_detials, 
                &file_actions[i]
            );

        }



        for i in 0..DEFAULT_POOL_COUNT {
            if pids.0[i] == -1 {continue;}

            //Get proccesses progress
            sleep(Duration::from_millis(100));
            let stat = {
                read_pid_status(
                    &pids.0[i], 
                    fc.str_file_name_from(pids.1[i])
                )
            };


            match stat {
                Ok(res) => {
                    if res {
                        //process finished
                        //store data that program finished
                        pids.0[i] = -1;
                        
                    } else {
                        //process still running
                        continue;
                    }
                },
                Err(_) => {
                    // store in data that program failed
                    pids.0[i] = -1;
                },
            }
            
            executable_left = executable_left.saturating_sub(1);
        }

    }
    


    unsafe {
        while let Some(mut fa) = file_actions.pop() {
            posix_spawn_file_actions_destroy(&mut fa as *mut _);
            
        }
    }

    drop(writefd_list);
    flag.store(false, Ordering::Relaxed);
    if let Err(e) = pipeline_worker.join() {
        panic!("Pipeline worker panicked: {:?}", e);
    }

    if let Err(e) = record_worker.join(){
        panic!("Record worker panicked: {:?}", e);
    }
    

}




fn read_pipeline(
    readfds: Vec<OwnedFd>,
    sender: Sender<String>,
    flag: Arc<AtomicBool>
) -> Result<(), SyncronizeErr> {

    println!("[ ThreadRunner is Listening ]");
    println!("[ Pipeline Reader Active ]");

    let readfds: Vec<_> = readfds.into_iter().map(|i| unsafe {
        File::from_raw_fd(i.into_raw_fd()) 
    }).collect();

    // Phase 1: Actively listen while FLAG is true
    while flag.load(Ordering::Relaxed) {
        for i in 0..DEFAULT_POOL_COUNT{
            let buf = BufReader::new(&readfds[i]);
            for line in buf.lines() {
                if let Ok(s) = line {
                    // println!("Read string (live): {}", s);
                    sender.send(s).expect("Receiver hanged up");

                } else {
                    eprintln!("Invalid UTF-8");
                }
            }
        }
    }

    // Phase 2: Drain until EOF
    println!("[ Draining remaining pipe content ]");
    
    for i in 0..DEFAULT_POOL_COUNT {
        let buf = BufReader::new(&readfds[i]);
        for line in buf.lines() {
            if let Ok(s) = line {
                // println!("Read string (live): {}", s);
                sender.send(s).expect("Receiver hanged up");
            } else {
                eprintln!("Invalid UTF-8");
                break;
            }
        }
    }

    drop(sender);
    println!("[ Closing Pipeline Reader ]");
    Ok(())
}


fn format_info_worker(
    record: Arc<TRecord>,
    reciever: Receiver<String>,
    flag: Arc<AtomicBool>
){
    
    while let Ok(s) = reciever.recv(){
        println!("Reciever End:{}", s);
        
    }


}

