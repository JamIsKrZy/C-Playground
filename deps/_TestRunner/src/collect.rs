use std::{fs, io, path::Path};

#[cfg(target_os = "linux")]
use std::os::unix::fs::PermissionsExt;

use walkdir::{DirEntry, WalkDir};

#[derive(Debug)]
pub enum CollectErr {
    FolderReadProblem,
    InternalConversion,
}

type FileName = String;
type FilePath = String;

#[derive(Debug)]
pub struct FileCollection {
    pub exe_info: Vec<(FileName, FilePath)>,
    pub folder_group: Vec<(String, usize)>,
}

impl FileCollection {
    fn new() -> Self {
        Self {
            exe_info: Vec::new(),
            folder_group: Vec::new(),
        }
    }

    #[inline]
    pub fn len(&self) -> usize {
        self.exe_info.len()
    }

    pub fn str_file_name_from(&self, idx: usize) -> &str {
        match self.exe_info.get(idx) {
            Some(string) => string.1.as_str(),
            None => "(null)",
        }
    }

    #[cfg(target_os = "linux")]
    pub fn insert_path(&mut self, path: &Path) {
        let path_string = path
            .to_str()
            .expect("There was a problem in collecting file metadata")
            .to_string();

        let file_name = path_string
            .rsplit_once("/")
            .map(|some| some.1)
            .unwrap_or("undefined name")
            .to_string();

        self.exe_info.push((file_name, path_string));

        let parent_folder = FileCollection::get_parent(path);
        if parent_folder.is_empty() {
            return;
        }

        if let Some((group, size)) = self.folder_group.last_mut() {
            if group == parent_folder {
                *size += 1;
            } else {
                self.folder_group.push((parent_folder.to_owned(), 1));
            }
        } else {
            self.folder_group.push((parent_folder.to_owned(), 1));
        }
    }

    fn get_parent(path: &Path) -> &str {
        path.parent()
            .map(|p| p.to_str().unwrap_or(""))
            .unwrap_or("")
    }
}

fn is_hidden(dir: &DirEntry) -> bool {
    dir.file_name()
        .to_str()
        .map(|s| s.starts_with("."))
        .unwrap_or(false)
}

#[cfg(target_os = "linux")]
fn is_executable(path: &Path) -> bool {
    if let Ok(metadata) = fs::metadata(path) {
        let permissions = metadata.permissions();
        let mode = permissions.mode();
        // Check if any execute bit is set (owner, group, or others)
        mode & 0o111 != 0
    } else {
        false
    }
}

#[cfg(target_os = "windows")]
fn is_executable(path: &Path) -> bool {
    todo!()
}

pub fn collect_test_files<P: AsRef<Path>>(path: P) -> Result<FileCollection, CollectErr> {
    let mut exec_paths = FileCollection::new();

    let dir_walker = WalkDir::new(path).into_iter();
    for entry in dir_walker.filter_entry(|e| !is_hidden(e)) {
        let _ = entry.map(|dir| {
            let path = dir.path();
            // println!("{:?}, {:?}", path.to_str(), path.is_file());

            if path.is_file() && is_executable(path) {
                exec_paths.insert_path(path);
            }
        });
    }

    Ok(exec_paths)
}

#[cfg(test)]
mod test {}
