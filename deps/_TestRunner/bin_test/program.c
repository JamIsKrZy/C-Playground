#include "essential.h"


#define TEST_CASES\
    TEST_CASE(func_one, DEFAULT_SSIZE)\
    TEST_CASE(func_two, DEFAULT_SSIZE)\
    TEST_CASE(func_three, DEFAULT_SSIZE)\

#include "runtime.h"


TEST(func_one){
    printf("Operation murtify\n");
    RETURN_SUCCESS;
}

TEST(func_two){
    // printf("Im in Test 1");
    printf("Flaming High\n");

    RETURN_SUCCESS;
}


TEST(func_three){
    // printf("Im in Test 1");
    printf("Cheese Burger\n");

    RETURN_SUCCESS;
}
