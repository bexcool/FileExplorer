
/**  Command line colors
 *
 *   02/2021
 *   Petr Pavlik <bxc@post.cz>
 *
 *   This header function is for adding colors easily to your command line interface.
 *
 *   Use like this:
 *   text_color(COLOR);
 *
 */

#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
#endif // COLORS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define COLOR_INVISIBLE 0
#define COLOR_LOW_BLUE 1
#define COLOR_LOW_GREEN 2
#define COLOR_LOW_LIGHT_BLUE 3
#define COLOR_LOW_RED 4
#define COLOR_LOW_PINK 5
#define COLOR_LOW_YELLOW 6
#define COLOR_LOW_WHITE 7
#define COLOR_GRAY 8
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_LIGHT_BLUE 11
#define COLOR_RED 12
#define COLOR_PINK 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

void text_color(int color_number) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, color_number);
}
