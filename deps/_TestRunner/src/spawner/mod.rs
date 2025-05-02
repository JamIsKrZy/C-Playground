#[cfg(target_os = "linux")]
mod spawner_linux;
#[cfg(target_os = "linux")]
pub use spawner_linux::*;

#[cfg(target_os = "windows")]
mod spawner_win;
#[cfg(target_os = "windows")]
use spawner_win::*;
