#pragma once
#ifndef CALENDARUI_H_
#define CALENDARUI_H_

#define EVENTS_PER_DAY (10)

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void initializeArray(FILE* file, struct Data** holiday_Array, char file_Type);
void userMenu(struct Data** holiday_Array, struct Data** event_Array);
void dailyView(struct custom_Event_Day event_Array[12][31], int day, int month, int year);

struct dates
{
	int time_start;
	int time_end;
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

struct daily_Event_obj 
{
	int timeTracker;
	int timeStart;
	int timeEnd;
	struct event_Detail detail;
};


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

#endif // !CALENDARUI_H_
