#pragma once
#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_
#include "CalendarUI.h"
#include <windows.h>
#include<conio.h>
#include<time.h>

int dayofweek(int day, int month, int year);
int getMonthDays(int month, int year);
void displayMonth(int month, int year, struct Data** input_Array);
void displayYear(int year, struct Data** input_Array);
int getMenuInt(int lower_bound, int upper_bound);
int getInteger(void);
void changeWindowSize();
void todayHeader(struct Data** input_Array);

#endif // !COMMONHELPERS_H_
