#pragma once
#ifndef CALENDARUI_H_
#define CALENDARUI_H_

#define EVENTS_PER_DAY (5)

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void initializeHolidays(FILE* file, struct event_Detail input_Array[12][31][EVENTS_PER_DAY]);
void userMenu(struct event_Detail input_Array[12][31][EVENTS_PER_DAY]);

struct dates
{
	int time;
	int year;
};

struct event_Detail
{
	char* name;
	char* detail;
};

struct custom_Event_Day
{
	struct dates date[EVENTS_PER_DAY];
	struct event_Detail details[EVENTS_PER_DAY];
};

struct custom_Event_Month
{
	struct custom_Event_Day event_day[31];
};


#endif // !CALENDARUI_H_
