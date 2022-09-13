#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

// view the saved dates for the inputted day
void dailyView(struct Data** input_Array, int day, int month, int year)
{
	struct daily_Event_obj* time_Array = calloc(48, sizeof(struct daily_Event_obj));
	int time_Track = 0, counter;
	bool curr_Event = false;

	// initializing the time in the array
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

	// importing data into the time day array
	if (input_Array[month - 1][day - 1].event_Array[0].name != NULL)
	{
		for (int j = 0; j < EVENTS_PER_DAY; j++)
		{
			if (input_Array[month - 1][day - 1].event_Array[j].year == CURR_YEAR)
			{
				for (int i = 0; i < 48; i++)
				{
					if (time_Array[i].timeTracker == input_Array[month - 1][day - 1].event_Array[j].time_Start)
					{
						time_Array[i].info.time_Start = input_Array[month - 1][day - 1].event_Array[j].time_Start;
						time_Array[i].info.time_End = input_Array[month - 1][day-1].event_Array[j].time_End;

						time_Array[i].info.name = malloc(strlen(input_Array[month - 1][day - 1].event_Array[j].name));
						strcpy(time_Array[i].info.name, input_Array[month - 1][day - 1].event_Array[j].name);
					}
				}
			}
		}
	}

	printf(" Day View - %i-%i-%i\n", day, month, year);
	printf("--------------------------------+\n");
	for (int  i = 0; i < 48; i++)
	{
		// printing name of event
		if (time_Array[i].info.name != NULL)
		{
			curr_Event = true;
			counter = time_Array[i].info.time_End;
			printf(" %-5d| %-23s |\n", time_Array[i].timeTracker, time_Array[i].info.name);
		}
		else
		{
			// printing the equal signs to indicate the block is booked
			if (curr_Event == true)
			{
				if (counter >= time_Array[i].timeTracker)
				{
					printf(" %-5d|=========================|\n", time_Array[i].timeTracker);
				}

				if (counter == time_Array[i].timeTracker)
				{
					curr_Event = false;
				}
			}
			// printing free block 
			else
			{
				printf(" %-5d|                         |\n", time_Array[i].timeTracker);
			}
		}
	}

	printf("");
}

// Adds event to array of custom events
void addEvent(struct Data** event_Array)
{
	char name, detail;
	int day, month, year, startTime, endTime;
	system("cls");
	printf("\n=======================================\n");
	printf("=       Date Manager: Add Event       =\n");
	printf("=======================================\n");

	printf("Year: ");
	getIntPositive(&year);

	printf("Month: ");
	
	//getRangeInt(1, getMonthDays(year));
	
	printf("Name: \n");
	scanf("%s", &name);

	printf("Detail: ");
	scanf("%s", &detail);

	printf("Start Time: ");
	//scanf("%d", );
}

// manage dates in custom event array
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
		menu_Input = getRangeInt(0, 4);

		switch (menu_Input)
		{
			
		}
	} while (menu_Input != 0);
}

// main menu
void userMenu(struct Data** holiday_Array, struct Data** event_Array)
{
	/*
	TO DO:
		- daily view
			- finish the user input interface
		- weekly view
			- design UI
			- finish code
			- finish user input interface
		- monthly view
			- finish user input interface
		- yearly view
		- manage dates menu
			- finish code
			- user input interface

		- NEED TO MAKE USER INPUT FOOL PROOF
	*/
	int menu_Input = 0;
	do
	{
		system("cls");
		todayHeader(holiday_Array);
		printf("\n=======================================\n");
		printf("=           Simple Calendar           =\n");
		printf("=======================================\n");
		printf("1. Daily View\n");
		printf("2. Weekly View\n");
		printf("3. Monthly View\n");
		printf("4. Yearly View\n");
		printf("5. Manage My Dates\n");
		printf("0. Quit\n");
		printf("Please Select an option listed Above: ");
		menu_Input = getRangeInt(0, 5);

		switch (menu_Input)
		{
		// Daily View
		case 1:
			system("cls");
			printf("Please enter a date (DD MM YYYY): ");
			dailyView(event_Array, 7, 1, 2022);
			pauseExecution();

		// Weekly View
		case 2:
			printf("Please enter a date. The week containing the date will be displayed");

		// Monthly View
		case 3:
			printf("Please enter a month and year in format MM YYYY");

		// Yearly View
		case 4:
			printf("Please enter a year in format YYYY");

		// Manage my Dates Menu
		case 5:
			;
		// Quit
		case 0:
			;
		}
		
	} while (menu_Input != 0);
	

}