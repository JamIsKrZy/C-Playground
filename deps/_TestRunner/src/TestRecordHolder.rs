use std::{
    collections::{BTreeMap, HashMap, HashSet},
    sync::{Mutex, RwLock},
};

enum RecordErr {
    TestMapCorrupted,
    TestInfoCorrupted,
    RecordAlreadyExist,
    StatusIsDefined,
}

enum TestStatus {
    Fail,
    Success,
}

enum LogType {
    Debug(String),
    Info(String),
    Warning(String),
}



enum InfoAction{
    Register(String, )
}


pub fn format_info(info: String) -> {

    let sl = info.split("-").collect::<Vec<_>>();

    match sl[0] {
        "register" => {

        }
        "staus" =>{

        } 
        "log" =>{

        } 
        _ => { println!("Undefined actions info") }
    }
}




type Status = Option<TestStatus>;
type Logs = Vec<LogType>;
type TestKeys = HashSet<String>;

struct Test(Status, Mutex<Logs>);

struct TestCollection {
    test_map: BTreeMap<String, TestKeys>,
    test_info: HashMap<String, Test>,
}

pub struct TRecord(RwLock<TestCollection>);

impl TRecord {
    pub fn new() -> Self {
        Self(RwLock::new(TestCollection {
            test_map: BTreeMap::new(),
            test_info: HashMap::new(),
        }))
    }

    pub fn register_process(&self, process_name: String) -> Result<(), RecordErr> {
        let mut collection = self.0.write().map_err(|_| RecordErr::TestMapCorrupted)?;

        if collection.test_map.contains_key(&process_name) {
            return Err(RecordErr::RecordAlreadyExist);
        } else {
            collection
                .test_map
                .insert(process_name, HashSet::with_capacity(4));
            Ok(())
        }
    }

    pub fn register_test(&self, process_from: &str, test_name: String) -> Result<(), RecordErr> {
        let mut collection = self.0.write().map_err(|_| RecordErr::TestMapCorrupted)?;

        Ok(())
    }

    pub fn update_test_status(
        &self,
        process_from: &str,
        test_name: String,
        status: TestStatus,
    ) -> Result<(), RecordErr> {
        Ok(())
    }

    pub fn append_test_logs(&self, process_from: &str, test_name: String) {

    }
}
