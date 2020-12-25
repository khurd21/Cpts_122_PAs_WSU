//
//  testFunctions.c
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/24/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "testFunctionsHeader.h"
#include "header.h"

void containsCommaDisplayResult(char *string, int flag) {
    
    if (flag == 0) {
        printf("String: %s\n**Does not contain a comma**\n", string);
    }
    else {
        printf("String: %s\n**Contains a comma**\n", string);
    }
}

int checkRunTime(char *runTime) {
    
    int hr, min;
    
    sscanf(runTime, "%d:%d", &hr, &min);
    if (hr < 0 || hr > 24) {
        printf("Hour unable to be converted to integer.\n");
        return 1;
    }
    if (min < 0 || min > 59) {
        printf("minute unable to be converted to integer.\n");
        return 1;
    }
    printf("Minutes and hours are within appropriate bounds.\n");
    return 0;
}

void checkYear(int n) {
    
    if (n > 2020) {
        printf("Number exceeds 2020.\n");
    }
    else if (n < 1888) {
        printf("Film was created in 1888.\n");
    }
    else {
        printf("Year of movie is within a reasonable bound.\n");
    }
}

void checkTimesPlayed(int n) {
    
    if (n < 0) {
        printf("Number times played cannot be negative.\n");
    }
    else {
        printf("Number of times played is of a positive value.\n");
    }
}

void checkRating(int n) {
    
    if (n < 1 || n > 5) {
        printf("Rating exceeded bounds of [1-5].\n");
    }
    else {
        printf("Rating is within the bounds of [1-5].\n");
    }
}

void insertTestFunction() {
    /*
     Name: Kyle Hurd
     Date: 09/26/2020
     Description: Tests the variables that would exist within the Node for the
                  records. The notes declared the code should be self-sufficient.
                  However, the error to check for the code are repetive, so I created
                  functions to be called by this one to check for commas, check for
                  domain, and display results.
     */
    // VARIABLES TO BE TESTED
    char*movieTitle = "Bohemian Rapsody",
        *director = "Bryan Singer",
        *description = "Freddie Mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.",
        *genre = "Drama",
        *runTime = "2:13";
    int year = 2018,
        timesPlayed = -1,
        rating = 6,
        flag = 0;
    
    // START OF CODE
    flag = containsComma(movieTitle);
    containsCommaDisplayResult(movieTitle, flag);
    flag = containsComma(director);
    containsCommaDisplayResult(director, flag);
    flag = containsComma(description);
    containsCommaDisplayResult(description, flag);
    flag = containsComma(genre);
    containsCommaDisplayResult(genre, flag);
    flag = checkRunTime(runTime);
    checkYear(year);
    checkTimesPlayed(timesPlayed);
    checkRating(rating);
}

void deleteTestFunction() {
    
    Node *newNode = NULL;
    newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf("New node not created.\n");
        goto end;
    }
    // We dont care about the contents within node, only that it is freed.
    free(newNode);
    newNode = NULL;
    if (newNode == NULL) {
        printf("Node was freed from memory.\n");
    }
    else {
        printf("Node was not freed from memory.\n");
    }

end:
    return;
}

void shuffleTestFunction() {
    
    srand((unsigned int)time(NULL));
    int numMovies = 10;
    int array[numMovies];
    int flag = 0;
    
    printf("**Testing shuffle. I ran it twice to show the order is randomly generated.**\n");
loop: // generates a random list twice
    shuffleFillArray(array, numMovies);
    printf("**Number of movies: %d**\n", numMovies);
    
    for(int i = 0; i < numMovies; i++) {
        printf("%d -> ", array[i]);
    }
    printf("\n");
    if (++flag != 2) goto loop;
}
