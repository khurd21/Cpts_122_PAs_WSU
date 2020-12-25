//  Cpts_122_FitbitData
//  main.c
//  PA_1_Fitbit_Data
//
//  Created by Kyle Hurd on 8/26/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"

int main(int argc, const char * argv[]) {
    /*
     Name: Kyle Hurd
     Date: 09/02/2020
     Description: Driver. Opens FILES, declare variables
                  needed for output. Needs access to a .csv file
                  containing fitbit data of 8 types of data per
                  line. It must be formatted per line in the following
                  method, excluding parantheses:
                    (Patient,minute,calories,distance,floors,heart,steps,sleep_level)
                  
     Alterations: If the user wishes to calculate the fitbit statistics from the
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
    // Opening Files
    FILE* infile;
    FILE* outfile;
    infile = fopen("FitbitData.csv", "r"); int infile_open_check;
    outfile = fopen("Results.csv", "w"); int outfile_open_check;
    
    infile_open_check = file_check_if_open(infile);
    outfile_open_check = file_check_if_open(outfile);
    
    if (infile_open_check == FALSE || outfile_open_check == FALSE) exit(0);
    else ; // Add code here if needed
    
    // Declarations
    FitbitData fitbit_data[MINUTES_PER_DAY]; // total minutes in a day 24hr * 60min = 1440
    FinalStats final_stats_fitbit_data; // 1 total_cal, 2 total_distance, 3 total_floors, 4 total_steps, 5 avg_heart_rate, 6 max_steps_one_min, 7 max_poor_sleep_start, 8 max_poor_sleep_end
    
    // Start of code
    get_24hr_fitbit_data(infile, fitbit_data);
    calc_24hr_fitbit_data(fitbit_data, &final_stats_fitbit_data);
    display_24hr_fitbit_data_outfile(outfile, &final_stats_fitbit_data, fitbit_data);
    display_24hr_fitbit_data_screen(&final_stats_fitbit_data, fitbit_data);
    
    // Closing Files
    infile =  (fclose(infile)  == 0) ? NULL : infile;
    outfile = (fclose(outfile) == 0) ? NULL : outfile;
    
    if (infile == NULL) printf("File closed successfully.\n");
    else printf("Error closing infile.\n");
    if (outfile == NULL) printf("File closed successfully.\n");
    else printf("Error closing outfile.\n");
    
    return 0;
}
