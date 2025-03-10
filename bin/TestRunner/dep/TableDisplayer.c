
#include <stdio.h>
#include <string.h>
#include "TableDisplayer.h"



char* get_result_str(bool result){
    switch (result){
        case true:
            return "\033[32mPASS\033[0m";
        
        case false:
            return "\033[31mFAIL\033[0m";
    }
}


size_t get_longest_str(char *str[], size_t size){
    size_t larg_len = 10;
    size_t t;

    for(size_t i=0; i < size; i++){
        t = strlen(str[i]);
        if(t > larg_len){
            larg_len = t;
        }
    }
    
    return larg_len;
}

void draw_horizontal_line(size_t len){                
    char str_display[len+1];
    memset(str_display, '-', len);
    str_display[len] = '\0';

    printf("%s\n", str_display);
}



void display_header(size_t max_width){
    size_t hor_len = HORIZONTAL_LEN(max_width);
    
    char *title = "Test Names";
    char *res = "Result";

    draw_horizontal_line(hor_len);    
    printf("|  \033[1m%-*s\033[0m  |  \033[1m%-*s\033[0m  |\n", (int)max_width, title, (int)RESULT_WIDTH, res);
    draw_horizontal_line(hor_len);
}

void display_row(char* text, bool result, size_t max_width){
    printf("|  %-*s  |  %-*s  |\n", (int)max_width, text, (int)RESULT_WIDTH_W_COLOR, get_result_str(result));
}



static int count_passed(ProcessResult *res){
    int count = 0;

    for(size_t i=0; i<res->len; i++){
        if(res->res[i]) count++;
    }
    return count;
}

void display_total(size_t max_width, int passed, int total){

    char buffer[32];
    snprintf(buffer, 32,"%d / %d", passed, total);

    printf("|  %-*s  |  %-*s  |\n", 
            (int)max_width, "TOTAL:", 
            (int)RESULT_WIDTH, buffer);
}


void display_result_table(ProcessResult* res){
    if(!res) return;
    //Get the longest text size among the texts
    size_t max_width = string_longest_size(&res->file_names, TITLE_WIDTH);
    //Padding - 2 Left and Right

    display_header(max_width);
    size_t items = res->len;

    for (size_t i = 0; i < items; i++)
    {
        display_row(
            vector_string_get(&res->file_names, i), 
            res->res[i], 
            max_width
        );
        draw_horizontal_line(HORIZONTAL_LEN(max_width));
    }

    display_total(max_width, count_passed(res), items);
    draw_horizontal_line(HORIZONTAL_LEN(max_width));
}
