# Test Library
This library provides the utilities needed to setup test cases right away. No need for too much function declaration just indicate the tests then pass it.  

How this library works makes the test cases run its own process thread for each test case made. Declare the test cases and the runtime will attach those test cases and run it for you and provide the information needed.


## Guide

### Quick Start
```c
#include "testlib.h"

#define TEST_CASES\
    TEST_CASE(testing, DEFAULT_SSIZE)\
    TEST_CASE(fail_add, DEFAULT_SSIZE)\

#include "runtime.h"

TEST(testing){

    int arr[2] = {11,22};

    assert(arr[1] == 11);
    assert(arr[2] == 22);

    RETURN_SUCCESS;
}


TEST(fail_add){

    int value_1 = 111;
    int value_2 = 212;

    int add = value_1 + value_2;

    //expected to detect the test case to fails
    assert( add == 333 );

    RETURN_SUCCESS;
}


```

### Caution
The program will fail if you create a test case where 


## Working on features
- Passing information to the parent thread
- TEST_TO_FAIL


