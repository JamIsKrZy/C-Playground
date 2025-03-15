
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
    printf("|  \033[1m%-*s\033[0m  |  \033[1m%-*s\033[0m  |\n", (int)max_width+4, title, (int)RESULT_WIDTH, res);
    draw_horizontal_line(hor_len);
}

void display_row_content(char* text, bool result, size_t max_width){
    printf("|    ↳ %-*s  |   %-*s |\n", (int)max_width, text, (int)RESULT_WIDTH_W_COLOR, get_result_str(result));
}

void display_folder_title(char* text, size_t max_width){
    printf("| 📂 %-*s   %-*s  |\n", (int)max_width + 4, text, (int)RESULT_WIDTH, "");
}



static int count_passed(ProcessResults *res){
    int count = 0;
    size_t len = res->len;

    for(size_t i=0; i< len ; i++){
        if(res->res[i]) count++;
    }
    return count;
}

void display_total(size_t max_width, int passed, int total){

    char buffer[32];
    snprintf(buffer, 32,"%d / %d", passed, total);

    printf("|  %-*s  |  %-*s  |\n", 
            (int)max_width+4, "TOTAL:", 
            (int)RESULT_WIDTH, buffer);
}


inline static size_t get_longest(size_t i, size_t j){
    return i > j? i : j;
}

size_t longest_string_to_display(TestFilesData *data){
    size_t longest = TITLE_WIDTH + INDENT;
    TestFilesDataIter iter = init_file_data_iter(data);
    char *catch;
    while ((catch = next_folder(&iter)))
    {
        
        longest = get_longest(longest, strlen(catch));

        while ((catch = next_files_by_name(&iter)))
        {
        
            longest = get_longest(longest, strlen(catch));
        }
        
    }
    return longest;
}



void display_result_table(TestFilesData *data, ProcessResults results){
    if(!data && !results.res) return; 

    //Get the longest text size among the texts
    size_t max_width = longest_string_to_display(data);
    size_t i = 0;
    TestFilesDataIter iter = init_file_data_iter(data);
    display_header(max_width);

    char *catch;
    while ((catch = next_folder(&iter)))
    {
     
        if(next_file_is_empty(&iter)) continue;
        display_folder_title(catch, max_width);   
        draw_horizontal_line(HORIZONTAL_LEN(max_width));
        

        while ((catch = next_files_by_name(&iter)))
        {

            display_row_content(catch, results.res[i], max_width);
            draw_horizontal_line(HORIZONTAL_LEN(max_width));

            i++;
        }
        
    }

    display_total(max_width, count_passed(&results), results.len);
    draw_horizontal_line(HORIZONTAL_LEN(max_width));
}
