
/** Functions for File Explorer
 *
 * BeXCool 2020
 * Petr Pavlik <bxc@post.cz>
 *
 */


#ifndef FE_FUNCTIONS_H_INCLUDED
#define FE_FUNCTIONS_H_INCLUDED
#endif // FE_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "colors.h"

void delay(int number_of_seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

int command(char url[1000], char lastDir[1000]) {

    if(strcmp(url, "$root") == 0){
        strcpy(lastDir, "");
        text_color(COLOR_YELLOW);
        printf("\nRemoved current URL.");
        text_color(COLOR_WHITE);
        return(lastDir);
        }else if(strcmp(url, "$abort") == 0) {
                    text_color(COLOR_YELLOW);
                    printf("\nAborted current action.");
                    text_color(COLOR_WHITE);
                    return(1);
        } else {
            return(0);
        }
}
