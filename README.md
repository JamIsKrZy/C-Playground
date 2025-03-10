# Collection in C


The purpose of this repository is to able to play and test with C code.
For the learning purposes if you want to test out any C Code like 
building a data structure then make a test for it.

The primary purpose of this was supposed to be building data structure from
scratch then test with it. But in the process of making this repository, 
this can be used by any purpose for learning


The process to execute thee program is to
1. Build the bin executables
2. Build the Modules
3. Build the test (this compiles with the compiled modules)
4. Run the test

## How to Build
The building process is to compile the collection .c files to object(".o")
files stored in the "/build" folder.

- **Build Whole Repository**
```
make  
```

- **Build Specific File**
```
make compile_one file=(file_name.c)  
```


## How to Test
[In the Process]


**Pre-Requisite**: Make sure the bin is compiled
```
make exe
```

1. **Build the Test** <br>
this is to compile inside the Test file to executable.
Ready for the executable for running test to be used
```
make tests
```


2. **Run the Test**   <br>
use the executable file, to run the test
```
./bin/test
```







# File Structure

### 📂 bin
**Executables stored** 
- TestRunner - Runs the test binaries

### 📂 build
Objects are stored in the 


### 📂 Collections
Data Structures are stored in the directory. Could be either a Data Structure or Algorthm.

Create a folder to create a respective module purpose


### 📂 test_bin
Executables ready to be run by the TestRunner executable from bin 


### 📂 tests
Test Files that contains the flow of the test. To run the test, 
it needs to be builded turn to executable files and stored in the test_bin folder
