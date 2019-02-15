// Compile by 
// UNIX >>> 
// cd src && gcc -c freader.c freader-lib.c && gcc -o ../bin/freader freader.o freader-lib.o && rm *.o && cd ..
// WINDOWS >>>
// cd src && gcc -c freader.c freader-lib.c && gcc -o ../bin/freader freader.o freader-lib.o && del *.o && cd ..
#include "freader-lib.h"
#include "freader-compile-args.h"

int main(int argc, char** argv)
{
    #ifdef WINDOWS // For 
    setlocale(LC_ALL, "");
    #endif

    // This variables will init from command-args
    int terminal_size = 100;

    char file_name[FILENAME_MAX];
    BOOL is_file_name_init = FALSE;

    int pause = 500;

    for (int i = 1; i < argc; i++)
    {
        if (i >= argc) // Because there are some jokes with i
        {
            break;  
        }

        if (!strcmp(argv[i], "-len")) // terminal-size
        {
            if (argv[++i] == NULL)
            {
                PERROR("There are not terminal buffer size after -len!");
            }

            terminal_size = atoi(argv[++i]);
            i++;
        }
        else if (!strcmp(argv[i], "-file")) // file-name
        {
            if (argv[++i] == NULL)
            {
                PERROR("There are not file name after -file!");
            }
            strcpy(file_name, argv[i]);
            is_file_name_init = TRUE;
            i++;
        }
        else if (!strcmp(argv[i], "-pause"))
        {
            if (argv[++i] == NULL)
            {
                PERROR("There are not pause value after -pause!");
            }
            pause = atoi(argv[i]);
            i++;
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
        PERROR("There are not any file with this name!");
    }
    
    
    int c; // Because EOF bigger than char
    char buf[WORD_LEN_MAX]; // For words
    int buf_count = 0; // With every new char in word - this counter will grow
    while ((c = fgetc(input)) != EOF)
    {
        if (c == ' ' || c == '\n')
        {
            buf[buf_count] = '\0'; // There are can be garbage

            centerOut(buf, buf_count, terminal_size);
            fflush(stdout); // to see this text in pause
            sleep(pause);
            
            clean(terminal_size - buf_count); 

            memset(buf, 0, buf_count); // Clean array
            buf_count = 0;
        }
        else
        {
            buf[buf_count++] = (char)c;
        }
    }

    return 0;
}