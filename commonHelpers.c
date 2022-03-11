/*
============================================
Helper functions used throughout the program
============================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "commonHelpers.h"
#include <windows.h>

char* days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
char* months_Name[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

// changes window size
void changeWindowSize()
{
    HWND hWnd;
    SetConsoleTitle("test");
    hWnd = FindWindow(NULL, "test");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize = {93, 50};//GetLargestConsoleWindowSize(hOut);
    SMALL_RECT DisplayArea = { 0, 0, 0, 0 };

    SetConsoleScreenBufferSize(hOut, NewSBSize);

    DisplayArea.Right = NewSBSize.X - 1;
    DisplayArea.Bottom = NewSBSize.Y - 1;

    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

    ShowWindow(hWnd, SW_MAXIMIZE);
}

// displays the events that take place today
//  --- NEED TO DO: add custom_Array in this
void displayDayEvents(int day, int month, int year, struct Data** input_Array)
{

    if (input_Array[month - 1][day - 1].size > 0 /*need to add other array here*/)
    {
        printf("Events on %d-%d-%d\n", day, month, year);
        printf("====================\n\n");
    }
    if (input_Array[month - 1][day - 1].size > 0)
    {
        printf("+---------------------------------------+\n");
        printf("| Holidays/Special Events               |\n");
        printf("+---------------------------------------+\n");

        int i = 0;
        while (input_Array[month - 1][day - 1].event_Array[i].name != NULL)
        {
            printf("| %-37s |\n", input_Array[month - 1][day - 1].event_Array[i].name);
            i++;
        }
        printf("+---------------------------------------+\n");
    }
}

// finds todays date
void todayHeader(struct Data** input_Array)
{
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    displayDayEvents(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, input_Array);
}

// Take date and return 0 - 6 indicating what day falls on the date
int dayofweek(int day, int month, int year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

// Take month and year and return how many days the month has, also checks for leap year
// takes value 1 - 12 for month
int getMonthDays(int month, int year)
{
    int month_array[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2)
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            return 29;
        }
    }
    return month_array[month - 1];
}

// changes print colur to blue
void blue() 
{
    printf("\033[0;34m");
}

// resets print colour back to white
void reset_colour() 
{
    printf("\033[0m");
}

// prints the day, utilizes different colours depending on what is needed
void holidayDateDisplay(struct Data** input_Array, int day, int month)
{
    if (input_Array[month - 1][day - 1].size > 0)
    {
        blue();
        printf("%3i", day);
        reset_colour();
    }
    else
    {
        printf("%3i", day);
    }
}

 // Take month and year and return a visual of the month with each date placed under the day it falls on
void displayMonth(int month, int year, struct Data** input_Array)
{
    int month_Buffer[6][7] = { {0} };
    int count = dayofweek(1, month, year);
    int week = 0;

    printf("+----------------------+\n");
    printf("| %-9s %10d |\n", months_Name[month-1], year);
    printf("|----------------------|\n");
    printf("| Su Mo Tu We Th Fr Sa |\n");

    // for every day in month
    for (int date = 1; date <= getMonthDays(month, year); date++)
    {
        // checking if date = day of week
        for (int x = 0; x < 7; x++)
        {
            if (x == dayofweek(date, month, year))
            {
                month_Buffer[week][count] = date;
            }
        }

        count++;

        if (count == 7)
        {
            count = 0;
            week++;
        }
    }

    // for every week
    for (int i = 0; i < 6; i++)
    {
        printf("|");

        // for every day
        for (int c = 0; c < 7; c++)
        {
            if (month_Buffer[i][c] != 0)
            {
                holidayDateDisplay(input_Array, month_Buffer[i][c], month);
                printf("%3i", month_Buffer[i][c]);
            }
            else
            {
                printf("   ");
            }
        }
        printf(" |\n");
    }
    printf("+----------------------+\n");
}

 // Takes year input and display all the months in a 4 x 3 grid
void displayYear(int year, struct Data** input_Array)
{
    printf("+-------------------------------------------------------------------------------------------+\n");
    printf("| %47d                                           |\n", year);
    int month_counter = 1; // tracks the months for name
    int month_tracker = 1; // tracks the months for date

    // for every 4 months
    for (int x = 0; x < 3; x++)
    {
        int month_buffer[4][6][7] = { {{0}} };

        // for every month in buffer
        for (int month = 0; month < 4; month++)
        {
            int count = dayofweek(1, month + month_counter, year);
            int week = 0;

            // for every day in month
            for (int date = 1; date <= getMonthDays(month + month_counter, year); date++)
            {
                // checking if date = day of week
                for (int x = 0; x < 7; x++)
                {
                    if (x == dayofweek(date, month, year))
                    {
                        month_buffer[month][week][count] = date;
                    }
                }

                count++;

                if (count == 7)
                {
                    count = 0;
                    week++;
                }
            }
        }

        
        printf("+-------------------------------------------------------------------------------------------+\n");
        printf("| %-20s | %-20s | %-20s | %-20s |\n", months_Name[month_counter - 1], months_Name[month_counter], months_Name[month_counter + 1], months_Name[month_counter + 2]);
        printf("|-------------------------------------------------------------------------------------------|\n");
        printf("| Su Mo Tu We Th Fr Sa | Su Mo Tu We Th Fr Sa | Su Mo Tu We Th Fr Sa | Su Mo Tu We Th Fr Sa |\n");

        // for every week
        for (int i = 0; i < 6; i++)
        {
            printf("|");

            // for every month
            for (int j = 0; j < 4; j++)
            {
                // for every day
                for (int c = 0; c < 7; c++)
                {
                    if (month_buffer[j][i][c] != 0)
                    {
                        holidayDateDisplay(input_Array, month_buffer[j][i][c], month_counter + j);
                        //printf("%3i", month_buffer[j][i][c]);
                    }
                    else
                    {
                        printf("   ");
                    }
                    
                }
                printf(" |");
                
            }
            printf("\n");
            
        }
        
        month_counter = month_counter + 4;
    }
    printf("+-------------------------------------------------------------------------------------------+\n");
}

// clears input buffer
void clearStandardInputBuffer(void)
{
    do
    {
        ;
    } while (getchar() != '\n');
}

int getInteger(void)
{
    int input;
    char line = 0;

    while (line != '\n')
    {
        scanf("%d%c", &input, &line);
        if (line != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
    }
    return input;
}

int getMenuInt(int lower_bound, int upper_bound)
{
    int rnge;

    do
    {
        rnge = getInteger();

        if (rnge < lower_bound || rnge > upper_bound)
        {
            printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
        }
    } while (rnge < lower_bound || rnge > upper_bound);
    return rnge;
}