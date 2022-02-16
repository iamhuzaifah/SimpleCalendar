#pragma once
#ifndef CALENDARUI_H_
#define CALENDARUI_H_

#define EVENTS_PER_DAY (10)

struct dates
{
	int time;
	int year;
};

struct event_Detail
{
	char name;
	char detail;
};

struct custom_Event_Day
{
	struct dates date[EVENTS_PER_DAY];
	struct event_Detail details[EVENTS_PER_DAY];
};

struct holiday_Event_Day
{
	struct event_Detail details[EVENTS_PER_DAY];
};

struct custom_Event_Month
{
	struct custom_Event_Day event_day[31];
};

struct holiday_Event_Month
{
	struct holiday_Event_Day event_day[31];
};
#endif // !CALENDARUI_H_
