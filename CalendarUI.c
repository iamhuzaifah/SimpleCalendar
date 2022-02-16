#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CalendarUI.h"


void initializeHolidays(FILE *file, struct event_Detail input_Array[12][31][EVENTS_PER_DAY])
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

	while (fgets(line, sizeof(line), file)) 
	{
		// getting X, Y for array
		month = strtol(strtok(line, "/"),buffer_Str, 10);
		day = strtol(strtok(NULL, "/"), buffer_Str, 10);
		
		for (int i = 0; i < EVENTS_PER_DAY; i++)

			if (input_Array[month-1][day-1][i].name == NULL) {

				// storing to buffer variables
				strcpy(buffer_Name, strtok(NULL, "/"));
				strcpy(buffer_Detail, strtok(NULL, "/"));

				// allocating space needed in memory and storing to array
				input_Array[month - 1][day - 1][i].name = malloc(strlen(buffer_Name));
				strcpy(input_Array[month - 1][day - 1][i].name, buffer_Name);

				input_Array[month - 1][day - 1][i].detail = malloc(strlen(buffer_Detail));
				strcpy(input_Array[month - 1][day - 1][i].detail, buffer_Detail);

				break;
			}
	}
	
}