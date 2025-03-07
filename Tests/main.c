#include <stdio.h>

int main(int argc, char const *argv[])
{
    /*
    Code	Color	Code	Background Color
    30	    Black	40	    Black
    31	    Red	    41	    Red
    32	    Green	42	    Green
    33	    Yellow	43	    Yellow
    34	    Blue	44	    Blue
    35	    Magenta	45	    Magenta
    36	    Cyan	46	    Cyan
    37	    White	47	    White

    Code	Effect
    1      	Bold
    4	    Underline
    7	    Invert (swap FG/BG)
    */


    printf("\033[31mThis is red text\033[0m\n");
    printf("\033[32mThis is green text\033[0m\n");
    printf("\033[33mThis is yellow text\033[0m\n");
    printf("\033[34mThis is blue text\033[0m\n");
    printf("\033[35mThis is magenta text\033[0m\n");
    printf("\033[36mThis is cyan text\033[0m\n\n");


    printf("\033[1;31mBold Red\033[0m\n");
    printf("\033[4;34mUnderlined Blue\033[0m\n\n");
    
    printf("\033[1;33;44mBold Yellow on Blue Background\033[0m\n");
    return 0;
}
