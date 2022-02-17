#define _CRT_SECURE_NO_WARNINGS
#include "commonHelpers.h"
#include "CalendarUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
    FILE* holiday_File = fopen("Holidays.txt", "r");

    struct event_Detail holiday_Array[12][31][EVENTS_PER_DAY] = { 0 };

    initializeHolidays(holiday_File, holiday_Array);

    displayYear(2022, holiday_Array);
    userMenu(holiday_Array);

    return 0;

}

