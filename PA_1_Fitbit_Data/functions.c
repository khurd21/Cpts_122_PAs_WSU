//  Cpts_122_Fitbit_Data
//  functions.c
//  PA_1_Fitbit_Data
//
//  Created by Kyle Hurd on 8/26/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"


int file_check_if_open(FILE* file) {
    /*
    Name: Kyle Hurd
    Date: 08/26/2020
    Description: Checks if the file passed in
                 is equal to NULL or not and
                 returns 0 for equalling NULL
                 and 1 for not.
    */
    if (file == NULL) {
        perror("FAILURE: ");
        return FALSE;
    }
    else {
        printf("File opened successfully.\n");
        return TRUE;
    }
}

void get_24hr_fitbit_data(FILE* infile, FitbitData *fitbit_data) {
    /*
     Name:        Kyle Hurd
     Date:        08/28/2020
     Description: Grabs all information within a .csv file with the correct
                  TARGET and timestamp and places it in an array with a size
                  of total minutes in one day (1440) to collect
                  minute-by-minute data for 24 hrs.
                  Also cleans up any missing data by supplementing the missing
                  data with a -1. Anything representing a negative value
                  should be ignored in determining statistic values.
     */
    char temp_array[BUFFER_SIZE]; // to hold each line from .csv file
    char* temp_token;
    int i = 0, data_location = 0;
    
first_item:
    if (!feof(infile) && i < MINUTES_PER_DAY) { //  && i < MINUTES_PER_DAY
        data_location = 0;
        fgets(temp_array, sizeof(temp_array), infile);
            
        temp_token = strtok(temp_array, COMMA);
        if (strncmp(temp_token, TARGET, sizeof(TARGET)) == FALSE) {
            strncpy(fitbit_data[i].patient, temp_token,
                    sizeof(fitbit_data[i].patient));
        }
        else {
            goto first_item;
        }
            
    subsequent_items: // STILL NEED TO CHECK FOR NULL OR MISSING DATA
            data_location++;
            if (data_location < DATA_PER_LINE) {
                temp_token = strtok(NULL, COMMA); // FINISH THIS SECTION
                
                switch (data_location) {
                    case 1: // MINUTES
                        if (i == 0) {
                        strncpy(fitbit_data[i].minute, temp_token,
                                sizeof(fitbit_data[i].minute));
                        }
                        else if (strncmp(fitbit_data[i].minute, fitbit_data[i-1].minute,
                                         sizeof(fitbit_data[i].minute)) == FALSE) {
                            goto first_item;
                        }
                        else {
                            strncpy(fitbit_data[i].minute, temp_token,
                                    sizeof(fitbit_data[i].minute));
                        }
                        break;
                    case 2: // CALORIES
                        fitbit_data[i].calories = (temp_token == NULL) ? BLANK : atof(temp_token);
                        // temp_token[0] == '\n' && temp_token[1] == '\0' ???
                        break;
                    case 3: // DISTANCE
                        fitbit_data[i].distance = (temp_token == NULL) ? BLANK : atof(temp_token);
                        break;
                    case 4: // FLOORS
                        fitbit_data[i].floors = (temp_token == NULL) ? BLANK : atoi(temp_token);
                        break;
                    case 5: // HEART RATE
                        fitbit_data[i].heart_rate = (temp_token == NULL) ? BLANK : atoi(temp_token);
                        break;
                    case 6: // STEPS
                        fitbit_data[i].steps = (temp_token == NULL) ? BLANK : atoi(temp_token);
                        break;
                    case 7: // SLEEP LEVEL
                        fitbit_data[i].sleep_level = (temp_token == NULL) ? NONE : atoi(temp_token);
                        break;
                    default: // SHOULD NOT HAPPEN
                        printf("Error found at switchcase within get_24hr_fitbit_data().\n");
                }
                goto subsequent_items;
            }
            else {
                i++;
                goto first_item;
            }
        }
    else printf("Reached end of file.\n");
    rewind(infile);
}

void calc_24hr_fitbit_data(FitbitData *fitbit_data, FinalStats *final_stats) {
    /*
     Name: Kyle Hurd
     Date: 08/31/2020
     Description:  Takes two structs of type FitbitData and FinalStats
                   and determines statistical values such as total calories,
                   distance, floors, steps, avg heart rate, and longest interval
                   of poor sleep. All of this information is determined by
                   the information provided by the FitbitData struct and placed
                   within FinalStats struct via pointer.
     
     Dependencies: FitbitData struct must be complete with no NULL values.
                   Missing information must be a -1 or highest possible
                   integer for an unsigned int.
     */
    // DECLARATIONS
    int i = 0, length_of_sleep = 0, flag_for_sleep = 0, temp_start_placeholder = 0,
    num_minutes_recorded_heart_rate = 0;
    final_stats->max_steps_one_minute = 0; // initialized to zero to compare with other steps
    final_stats->max_poor_sleep_start = 0;
    final_stats->max_poor_sleep_end = 0;
    final_stats->total_distance = 0;
    final_stats->total_floors = 0;
    final_stats->total_steps = 0;
    final_stats->total_calories = 0;
    final_stats->total_heart_rate_24hr = 0.0;
    
    // START OF CODE
loop:
    
    // GATHERING THE TOTALS FOR CALS, DISTANCE, FLOORS, STEPS AND HEART RATE
    final_stats->total_calories        += (fitbit_data[i].calories   != BLANK) ? fitbit_data[i].calories   : FALSE;
    final_stats->total_distance        += (fitbit_data[i].distance   != BLANK) ? fitbit_data[i].distance   : FALSE;
    final_stats->total_floors          += (fitbit_data[i].floors     != BLANK) ? fitbit_data[i].floors     : FALSE;
    final_stats->total_steps           += (fitbit_data[i].steps      != BLANK) ? fitbit_data[i].steps      : FALSE;
    final_stats->total_heart_rate_24hr += (fitbit_data[i].heart_rate != BLANK) ? fitbit_data[i].heart_rate : FALSE;
    num_minutes_recorded_heart_rate    += (fitbit_data[i].heart_rate != FALSE) ? TRUE                      : FALSE;
    
    // CHECKING FOR MAXIMUMS
    final_stats->max_steps_one_minute = (fitbit_data[i].steps >= final_stats->max_steps_one_minute) ? fitbit_data[i].steps : final_stats->max_steps_one_minute;
    
    // CHECKING AND UPDATING LONGEST DURATION OF POOR SLEEP. FIX ME IF BETTER SOLUTION!
    if (fitbit_data[i].sleep_level > ASLEEP && flag_for_sleep == FALSE) {
        length_of_sleep = FALSE;
        flag_for_sleep = TRUE;
        temp_start_placeholder = i;
        length_of_sleep++;
    }
    else if (fitbit_data[i].sleep_level > ASLEEP && flag_for_sleep == TRUE) {
        length_of_sleep++;
    }
    else if (fitbit_data[i].sleep_level <= ASLEEP && flag_for_sleep == TRUE) {
        final_stats->max_poor_sleep_start = (length_of_sleep >= (i - temp_start_placeholder)) ? temp_start_placeholder : final_stats->max_poor_sleep_start;
        final_stats->max_poor_sleep_end   = (length_of_sleep >= (i - temp_start_placeholder)) ? (i - 1)                : final_stats->max_poor_sleep_end;
        flag_for_sleep = FALSE;
    }
    else {
        final_stats->max_poor_sleep_start = final_stats->max_poor_sleep_start;
        final_stats->max_poor_sleep_end   = final_stats->max_poor_sleep_end;
    }

    i++;
    
    if (i < MINUTES_PER_DAY) goto loop;
    else {
        //printf("Total Heart Rate: %lf\n", final_stats->total_heart_rate_24hr);
        //printf("Num Minutes of Recorded heart rate: %d\n", num_minutes_recorded_heart_rate);
        //printf("%d\n", num_minutes_recorded_heart_rate);
        final_stats->avg_heart_rate_one_minute = final_stats->total_heart_rate_24hr / (float)num_minutes_recorded_heart_rate;
    }
    // DONE.
}

void display_24hr_fitbit_data_outfile(FILE* outfile, FinalStats *final_stats, FitbitData *fitbit_data) {
    /*
     Name: Kyle Hurd
     Date: 08/31/2020
     Description: Prints the final statistical values to an
                  outfile in a .csv format. A space is placed
                  after each comma.
     */
    fprintf(outfile, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
    fprintf(outfile, "%lf, %lf, %u, %u, %lf, %u, %s:%s\n",
            final_stats->total_calories, final_stats->total_distance,
            final_stats->total_floors, final_stats->total_steps,
            final_stats->avg_heart_rate_one_minute, final_stats->max_steps_one_minute,
            fitbit_data[final_stats->max_poor_sleep_start].minute,
            fitbit_data[final_stats->max_poor_sleep_end].minute);
}

void display_24hr_fitbit_data_screen(FinalStats *final_stats, FitbitData *fitbit_data) {
    /*
     Name: Kyle Hurd
     Date: 08/31/2020
     Description: Prints the final statistical values to the
                  terminal screen as a csv format. A space is placed
                  after each comma.
     */
    printf("Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
    printf("%lf, %lf, %u, %u, %lf, %u, %s:%s\n",
            final_stats->total_calories, final_stats->total_distance,
            final_stats->total_floors, final_stats->total_steps,
            final_stats->avg_heart_rate_one_minute, final_stats->max_steps_one_minute,
            fitbit_data[final_stats->max_poor_sleep_start].minute,
            fitbit_data[final_stats->max_poor_sleep_end].minute);
}
