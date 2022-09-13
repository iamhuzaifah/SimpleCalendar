#define _CRT_SECURE_NO_WARNINGS
#include "commonHelpers.h"
#include "CalendarUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>

int main(void)
{
    // changing window size for program
    changeWindowSize();

    // declaring the two arrays, one for holidays and one for custom events
    struct Data** holiday_Array = calloc(12, sizeof(struct Data**));

    for (int i = 0; i < 12; i++)
    {
        holiday_Array[i] = calloc(getMonthDays(i + 1, 2020) ,sizeof(struct Data));
    }

    struct Data** custom_Array = calloc(12, sizeof(struct Data**));

    for (int i = 0; i < 12; i++)
    {
        custom_Array[i] = calloc(getMonthDays(i + 1, 2020), sizeof(struct Data));
    }


    // opening and initializing holidays
    FILE* holiday_File = fopen("Holidays.txt", "r");
    initializeArray(holiday_File, holiday_Array, 'H');

    // opening and initializing custom events
    FILE* custom_File = fopen("CustomEvents.txt", "r");
    initializeArray(custom_File, custom_Array, 'C');

    userMenu(holiday_Array, custom_Array);

    /*
    int count = 1;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < getMonthDays(i + 1, 2020); j++)
        {
            for (int k = 0; k < holiday_Array[i][j].size; k++)
            {
                if (holiday_Array[i][j].event_Array[k].name != NULL)
                {
                    printf("%d %s %s\n", count, holiday_Array[i][j].event_Array[k].name, holiday_Array[i][j].event_Array[k].detail);
                    count++;
                }
                
            }
            
        }
    }

    count = 1;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < getMonthDays(i + 1, 2020); j++)
        {
            for (int k = 0; k < custom_Array[i][j].size; k++)
            {
                if (custom_Array[i][j].event_Array[k].name != NULL)
                {
                    printf("%d %s %s %d %d %d\n", count, custom_Array[i][j].event_Array[k].name, custom_Array[i][j].event_Array[k].detail, custom_Array[i][j].event_Array[k].time_Start, custom_Array[i][j].event_Array[k].time_End, custom_Array[i][j].event_Array[k].year);
                    count++;
                }

            }

        }
    }
    */

    return 0;
}

