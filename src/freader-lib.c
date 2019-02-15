#include "freader-lib.h"

void clean(
    int size
    )   
{
    putchar('\r');
    PRINTER(' ', size);
    putchar('\r');
}

void centerOut(
    const char* s,
    int s_size,
    int out_size
    )
{
    const int how_many_spaces = (out_size - s_size) / 2 + ((out_size % 2) ? 0 : 1); 
    PRINTER(' ', how_many_spaces);
    fputs(s, stdout); 
    PRINTER(' ', how_many_spaces);
}

const char* const help_text = // Text for -help argument
"FReader is program for fast reading files in console. Created by Dioderoid."
"Usage:"
"./freader.out -[ARGUMENT NAME] [VALUE]"
"-len   -> set terminal buffer length (nececcary for correct center-display). Standard value is 100."
"-file  -> set file name, where program will get text for displaying"
"-pause -> set pause duration for each word in miliseconds. Standart value is 500."
"-help  -> show this text\n";