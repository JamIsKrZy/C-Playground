# Collection in C


The purpose of this repository is to able to play and test with C code.
For the learning purposes if you want to test out any C Code like 
building a data structure then make a test for it.

The primary purpose of this was supposed to be building data structure from
scratch then test with it. But in the process of making this repository, 
this can be used by any purpose for learning


**Quick Start**
1. Build bin <br>
build the necceessary bin for executing the program
```
make build_bin
```

2. Build the collection and tests
```
make 
```

3. Run the tests
```
make tests 
```

**OPTIONAL**: for quicker command to compile all collections and tests and executes the tests right away
```
make run
```






## How to Build Collection
The building process is to compile the collection .c files to object(".o")
files stored in the "/build" folder.

**Build Whole**
```
make compile_one file=(file_name.c)  
```

<br>

**Build Specific File** [not yet supported]
```
make compile_one file=(file_name.c)  
```


## How to Test

1. **Build the Test** <br>
this is to compile inside the Test file to executable.
```
make build_test
```

2. a.) **Run Specific Tests** []  <br>
```
make test
```

2. b.) **Run Specific Tests** []  <br>
```
make test --only="File1.c, File2.c"
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
