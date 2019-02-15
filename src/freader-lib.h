#ifndef FREADER_LIB
#define FREADER_LIB

// Headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "freader-compile-args.h"
// // // //

// Macros

/*
*   I have not crossplatform decision 
*   for functions which can call pause,
*   so I added this macro for windows and unix platforms.
*/

#ifdef WINDOWS
#include <windows.h>
#include <locale.h>
#define sleep(a) Sleep((a))
#endif

#ifdef UNIX
typedef char BOOL;
#include <unistd.h>
#define sleep(a) usleep((a) * 1000) // ... because there are MICROseconds.
#endif

typedef unsigned int uint;
#define TRUE 1
#define FALSE 0

// Displays a certain number of spaces. (Inline functions for gays)
#define PRINTER(THIS, HOW_MANY) {for(int i=0;i<(HOW_MANY);i++){putchar(THIS);}fflush(stdout);} 

#define PERROR(a) puts(a);exit(-1)

// // // //

// Functions

// Clean terminal 
void clean(
    int size
);
// Display string in center of s_size buffer
void centerOut(
    const char* s, // String for display
    int s_size, // Size of string
    int out_size // Size of terminal buffer
);
 
// // // //

// Constants

extern const char* const help_text; // For -help

// // // //
#endif