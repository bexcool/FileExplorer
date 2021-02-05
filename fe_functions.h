#ifndef FE_FUNCTIONS_H_INCLUDED
#define FE_FUNCTIONS_H_INCLUDED
#endif // FE_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
