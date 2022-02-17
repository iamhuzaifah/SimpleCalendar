#pragma once
#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_
#include "CalendarUI.h"

int dayofweek(int day, int month, int year);
int getMonthDays(int month, int year);
void displayMonth(int month, int year);
void displayYear(int year, struct event_Detail holiday_Array[12][31][EVENTS_PER_DAY]);
int getMenuInt(int lower_bound, int upper_bound);
int getInteger(void);

#endif // !COMMONHELPERS_H_
