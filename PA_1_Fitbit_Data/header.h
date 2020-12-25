//  Cpts_122_Fitbit_Data
//  header.h
//  PA_1_Fitbit_Data
//
//  Created by Kyle Hurd on 8/26/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

/*
Alterations:
 
If the user wishes to calculate the fitbit statistics from the
given .csv format within a lesser or larger amount of time
(total amount of minnutes), they can simply adjust the #define MINUTES_PER_DAY constant
within the header.h file for the amount of minutes in the provided file.
For example, if you want to only calculate statistics in half a day, place 1220
instead of 1440.
TRUE and FALSE definitions should remain untouched. If you have information that needs to be
included that equals a -1, adjust the BLANK definition in the header file to one not included
in the .csv file to read.
If the file to be read separates information other than ",", change the #define COMMA to equal
another character in which the information is separated.
If you wish to compare data from another fitbit, change the TARGET name to the correct fitbit
patient name.
*/

#ifndef header_h
#define header_h

// LIBRARIES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// CONSTANTS
#define BUFFER_SIZE 64
#define MINUTES_PER_DAY 1440
#define DATA_PER_LINE 8
#define TRUE 1
#define FALSE 0
#define BLANK -1
#define TARGET "12cx7"
#define COMMA ","


// TYPEDEF ENUM / STRUCTS

// enumerated values for level of sleep. Used in FitbitData Struct
typedef enum sleep {
    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

// Patient,minute,calories,distance,floors,heart,steps,sleep_level
typedef struct fitbit{
    char patient[10];
    char minute[9];
    double calories;
    double distance;
    unsigned int floors;
    unsigned int heart_rate;
    unsigned int steps;
    Sleep sleep_level;
} FitbitData;

typedef struct final_stats {
    double total_calories;
    double total_distance;
    unsigned int total_floors;
    unsigned int total_steps;
    double total_heart_rate_24hr;
    double avg_heart_rate_one_minute;
    unsigned int max_steps_one_minute;
    unsigned int max_poor_sleep_start;
    unsigned int max_poor_sleep_end;
} FinalStats;

// FUNCTION DECLARATIONS
int file_check_if_open(FILE* file);

void get_24hr_fitbit_data(FILE* infile, FitbitData *fitbit_data);
void calc_24hr_fitbit_data(FitbitData *fitbit_data, FinalStats *final_stats);
void display_24hr_fitbit_data_outfile(FILE* outfile, FinalStats *final_stats, FitbitData *fitbit_data);
void display_24hr_fitbit_data_screen(FinalStats *final_stats, FitbitData *fitbit_data);
#endif /* header_h */
