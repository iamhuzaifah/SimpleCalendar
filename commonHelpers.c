/*
============================================
Helper functions used throughout the program
============================================
*/

#include <stdio.h>

char* days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
char* months_Name[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };


// Take date and return 0 - 6 indicating what day falls on the date
int dayofweek(int day, int month, int year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

// Take month and year and return how many days the month has, also checks for leap year
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

 // Take month and year and return a visual of the month with each date placed under the day it falls on
void displayMonth(int month, int year)
{
    int count = dayofweek(1, month, year);
    
    printf(" %s\n", months_Name[month-1]);
    printf(" Su Mo Tu We Th Fr Sa\n");

    for (int i = 0; i < dayofweek(1, month, year); i++)
    {
        printf("   ");
    }

    for (int i = 1; i <= getMonthDays(month, year); i++)
    {
        for (int x = 0; x < 7; x++)
        {
            if (x == dayofweek(i, month, year))
            {
                printf("%3i", i);
            }
        }

        count++;

        if (count == 7)
        {
            printf("\n");
            count = 0;
        }
    }
}

 // Take year and display all the months
void displayYear(int year)
{
    int month_counter = 0;
    // for every 4 months
    for (int x = 0; x < 1; x++)
    {
        int month_buffer[4][5][7] = { {{0}} };
        // for every month in buffer
        for (int month = 0; month < 4; month++)
        {
            int count = dayofweek(1, month, year);
            int week = 0;
            // for every day in month
            for (int date = 1; date <= getMonthDays(month, year); date++)
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

        printf(" January                February               March\n");
        // for every week
        for (int i = 0; i < 5; i++)
        {
            // for every month
            for (int j = 1; j < 4; j++)
            {
                // for every day
                for (int c = 0; c < 7; c++)
                {
                    printf("%3i", month_buffer[j][i][c]);
                }
                printf("  ");
                
            }
            printf("\n");
        }
    }
}