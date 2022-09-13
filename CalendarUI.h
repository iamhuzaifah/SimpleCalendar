#pragma once
#ifndef CALENDARUI_H_
#define CALENDARUI_H_

#define EVENTS_PER_DAY (10)

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void initializeArray(FILE* file, struct Data** holiday_Array, char file_Type);
void userMenu(struct Data** holiday_Array, struct Data** event_Array);
void dailyView(struct Data** input_Array, int day, int month, int year);

struct event_Info
{
	char* name;
	char* detail;
	int time_Start;
	int time_End;
	int year;
};

struct Data
{
	struct event_Info* event_Array;
	int size;
};

struct daily_Event_obj
{
	int timeTracker;
	struct event_Info info;
};

#endif // !CALENDARUI_H_
