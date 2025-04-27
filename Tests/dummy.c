
#include "../testlib/essential.h"

#define TEST_CASES\
    TEST_CASE(test_1, DEFAULT_SSIZE)\
    TEST_CASE(test_2, DEFAULT_SSIZE)\
    TEST_CASE(test_3, DEFAULT_SSIZE)

#include "runtime.h"


TEST(test_1){

    assert(4==4);

    RETURN_SUCCESS;
}

TEST(test_2){

    int left = 5;
    int right = 7;

    assert( left == right );

    RETURN_SUCCESS;
}

TEST(test_3){

    assert(4==3);

    RETURN_SUCCESS;
}