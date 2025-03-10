#ifndef TABLE_DISPLAYER_H
#define TABLE_DISPLAYER_H


#include <stdbool.h>
#include <stddef.h>
#include "ProcessPID.h"


#define BORDER 1
#define PADDING 2 
#define RESULT_WIDTH 6
#define RESULT_WIDTH_W_COLOR 15
#define TITLE_WIDTH 10
#define HORIZONTAL_LEN(str_len) BORDER + PADDING + str_len + PADDING + \
                                BORDER + PADDING + RESULT_WIDTH + PADDING + BORDER



void display_result_table(ProcessResult* res);





#endif