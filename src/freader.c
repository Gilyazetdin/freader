// Compile by 
// UNIX >>> 
// cd src && gcc -c freader.c freader-lib.c && gcc -o ../bin/freader freader.o freader-lib.o && rm *.o && cd ..
// WINDOWS >>>
// cd src && gcc -c freader.c freader-lib.c && gcc -o ../bin/freader freader.o freader-lib.o && del *.o && cd ..
#include "freader-lib.h"
#include "freader-compile-args.h"

int main(int argc, char** argv)
{
    #ifdef WINDOWS 
    SetConsoleOutputCP(65001); // UTF-8
    #endif

    // This variables will init from command-args
    int terminal_size = 100;

    char file_name[FILENAME_MAX];
    BOOL is_file_name_init = FALSE;

    int pause = 500; // stdvalue

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-len"))
        {
            terminal_size = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-file"))
        {
            strcpy(file_name, argv[++i]);
            is_file_name_init = TRUE;
        }
        else if (!strcmp(argv[i], "-pause"))
        {
            pause = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-help"))
        {
            puts(help_text);
        }
        else
        {
            PERROR("Incorrect argument!");
        }                
    }


    // Checking for correct values
    if (is_file_name_init == FALSE)
    {
        PERROR("You didn't init file name!");
    }
    
    FILE* input;
    if ((input = fopen(file_name, "r")) == NULL)
    {
        printf("There are not any file with \"%s\" name!", file_name);
        exit(-1);
    }
    
    // Because EOF bigger than char
    int c; 
    // For words
    char buf[WORD_LEN_MAX]; 
    // With every new char in word - this counter will grow
    int buf_count = 0; 
    while (TRUE)
    {
        c = fgetc(input);
        BOOL was_eof = FALSE;
        if (c == EOF)
        {
            was_eof = TRUE;
        }
        if (c == ' ' || c == '\n' || was_eof)
        {
            buf[buf_count] = '\0'; // Garbage

            centerOut(buf, buf_count, terminal_size);
            fflush(stdout); //To see this text in pause
            sleep(pause);
            
            clean(terminal_size - buf_count); 

            memset(buf, 0, buf_count); // Clean array
            buf_count = 0;
        }
        else
        {
            buf[buf_count++] = (char)c;
        }
        if (was_eof)
        {
            break;
        }
    }

    return 0;
}