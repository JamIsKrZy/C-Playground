#![allow(unu)]

mod TestRecordHolder;
mod collect;
mod displayer;
mod spawner;

use spawner::spawn_executable;
use termion::color;

const DEFAULT_OUTPUT: [&str; 2] = ["marmalade.txt", "thingy-majig.json"];
const DEFAULT_SOURCE: &str = "bin_test";
const DEFAULT_POOL_COUNT: usize = 5;

fn main() {
    // Read any argument eing passed
    let args: Vec<String> = std::env::args().collect();

    println!("Passed Arguments: {:?}", args);

    // Do some matching for configurations
    let root_path = DEFAULT_SOURCE;

    println!(
        "{}[ Collecting Compiled Test in {}... ]{}",
        color::Fg(color::Yellow),
        root_path,
        color::Fg(color::Reset)
    );

    let file_collection = collect::collect_test_files(DEFAULT_SOURCE);
    let file_collection = match file_collection {
        Ok(c) => c,
        Err(e) => {
            println!("There was a problem in collection files: {:?}", e);
            return;
        }
    };

    // println!("{:?}\n", file_collection);
    println!(
        "{}[ Setting up executables... ]{}",
        color::Fg(color::Yellow),
        color::Fg(color::Reset)
    );
    spawn_executable(file_collection);

    println!(
        "{}[ Finished Executing ]{}",
        color::Fg(color::Green),
        color::Fg(color::Reset)
    );
}
