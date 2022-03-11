#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CalendarUI.h"
#include "commonHelpers.h"
#define CURR_YEAR 2022


// takes holiday file and array and stores all the data
void initializeArray(FILE *file, struct Data** input_Array, char file_Type)
{
	char line[256];
	char* buffer_Str[256];
	char buffer_Name[50], buffer_Detail[50];
	int day, month;
	// Read the from file
	if (!file) 
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	// initializing the structure's array to 
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < getMonthDays(i + 1, 2020); j++)
		{
			input_Array[i][j].event_Array = calloc(EVENTS_PER_DAY, sizeof(struct event_Info));
		}
	}

	// inputting data into the array
	while (fgets(line, sizeof(line), file)) 
	{
		// getting X, Y for array
		month = strtol(strtok(line, "/"),buffer_Str, 10);
		day = strtol(strtok(NULL, "/"), buffer_Str, 10);
		
		for (int i = 0; i < EVENTS_PER_DAY; i++)
		{
			if (input_Array[month - 1][day - 1].event_Array[i].name == NULL) {

				// storing to buffer variables
				strcpy(buffer_Name, strtok(NULL, "/"));
				strcpy(buffer_Detail, strtok(NULL, "/"));

				// allocating space needed in memory and storing to array
				input_Array[month - 1][day - 1].event_Array[i].name = malloc(strlen(buffer_Name));
				strcpy(input_Array[month - 1][day - 1].event_Array[i].name, buffer_Name);

				input_Array[month - 1][day - 1].event_Array[i].detail = malloc(strlen(buffer_Detail));
				strcpy(input_Array[month - 1][day - 1].event_Array[i].detail, buffer_Detail);

				if (file_Type == 'C')
				{
					input_Array[month - 1][day - 1].event_Array[i].time_Start = strtol(strtok(NULL, "/"), buffer_Str, 10);
					input_Array[month - 1][day - 1].event_Array[i].time_End = strtol(strtok(NULL, "/"), buffer_Str, 10);
					input_Array[month - 1][day - 1].event_Array[i].year = strtol(strtok(NULL, "/"), buffer_Str, 10);
				}

				break;
			}
		}
	}
	
	// reallocating the array to minimize data use
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < getMonthDays(i + 1, 2020); j++)
		{
			for (int k = 0; k < EVENTS_PER_DAY; k++)
			{
				if (input_Array[i][j].event_Array[k].name == NULL)
				{
					input_Array[i][j].size = k;
					input_Array[i][j].event_Array = realloc(input_Array[i][j].event_Array, (input_Array[i][j].size * sizeof(struct event_Info)));
					break;
				}
			}
		}
	}
	return;
	
}

void dailyView(struct custom_Event_Day event_Array[12][31], int day, int month, int year)
{

	struct daily_Event_obj time_Array[48] = { 0 };
	int time_Track = 0;
	for (int i = 0; i < 48; i++)
	{
		if (i % 2 == 1)
		{
			time_Array[i].timeTracker = time_Track;
			time_Track = time_Track + 70;
		}
		else
		{
			time_Array[i].timeTracker = time_Track;
			time_Track = time_Track + 30;
		}
		
		

	}

	if (event_Array[month - 1][day - 1].details[0].name != NULL)
	{
		for (int j = 0; j < EVENTS_PER_DAY; j++)
		{
			if (event_Array[month - 1][day - 1].date[j].year == CURR_YEAR)
			{
				for (int i = 0; i < 48; i++)
				{
					if (time_Array[i].timeTracker == event_Array[month - 1][day - 1].date[j].time_start)
					{
						time_Array[i].timeStart = event_Array[month - 1][day - 1].date[j].time_start;
						time_Array[i].timeEnd = event_Array[month - 1][day-1].date[j].time_end;
						strcpy(time_Array[i].detail.name, event_Array[month - 1][day - 1].details[j].name);
					}
				}
			}
		}
	}

	printf("Day View - %i//%i//%i\n", day, month, year);
	printf("---------------------------");
	for (int  i = 0; i < 48; i++)
	{
		if (time_Array[i].detail.name != NULL)
		{
			int counter = i;
			printf("| %-20s |", time_Array[i].detail.name);
			do
			{
				printf("|=========================|\n");
				counter++;
			}while (time_Array[i].timeEnd != time_Array[counter].timeTracker);
		}
		else
		{
			printf("|                         |\n");
		}
	}
	
	
	printf("");
}

void manageDateMenu()
{
	int menu_Input = 0;
	do
	{
		system("cls");
		printf("\n=======================================\n");
		printf("=             Date Manager            =\n");
		printf("=======================================\n");
		printf("1. Add Event\n");
		printf("2. Delete Event\n");
		printf("3. Edit Event\n");
		printf("4. Event Search\n");
		printf("0. Quit\n");
		printf("Please Select an option listed Above: ");
		menu_Input = getMenuInt(0, 4);

		switch (menu_Input)
		{
			
		}
	} while (menu_Input != 0);
}

void userMenu(struct Data** holiday_Array, struct Data** event_Array)
{
	int menu_Input = 0;
	do
	{
		system("cls");
		todayHeader(holiday_Array);
		printf("\n=======================================\n");
		printf("=           Simple Calender           =\n");
		printf("=======================================\n");
		printf("1. Daily View\n");
		printf("2. Weekly View\n");
		printf("3. Monthly View\n");
		printf("4. Yearly View\n");
		printf("5. Manage My Dates\n");
		printf("0. Quit\n");
		printf("Please Select an option listed Above: ");
		menu_Input = getMenuInt(0, 5);

		switch (menu_Input)
		{
		case 1:
			printf("Please enter a date (DD MM YYYY): ");
			dailyView(event_Array, 1, 7, 2022);
		}
	} while (menu_Input != 0);
	

}