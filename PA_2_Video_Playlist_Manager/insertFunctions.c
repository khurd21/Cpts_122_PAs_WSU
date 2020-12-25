//
//  insertFunctions.c
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/28/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"

void insertGetDirector(char selection[]) {
   
    clearScreen();
    
get_director:
    printf("Enter director's name: ");
    fgets(selection, 49, stdin);
    strtok(selection, "\n");
    
    if (containsComma(selection) == TRUE) {
        goto get_director;
    }
}

void insertGetFilmTitle(char selection[]) {
    
    clearScreen();
    
get_film_title:
    printf("Enter the film title: ");
    fgets(selection, 49, stdin);
    strtok(selection, "\n");
    
    if (containsComma(selection) == TRUE) {
        goto get_film_title;
    }
}

void insertGetDescription(char selection[]) {
    
    clearScreen();
    
get_description:
    printf("Enter the description [250 characters MAX]:\n");
    fgets(selection, 249, stdin);
    strtok(selection, "\n");
    
    if (containsComma(selection) == TRUE) {
        goto get_description;
    }
}

void insertGetGenre(char selection[]) {
    
    clearScreen();
    
get_genre:
    printf("Enter the genre: ");
    fgets(selection, 14, stdin);
    strtok(selection, "\n");
    
    if (containsComma(selection) == TRUE) {
        goto get_genre;
    }
}

long insertGetHours(char selection[]) {
    
    char* ptrSelection = NULL;
    long hours;
    
    clearScreen();
    
get_hours:
    printf("Enter the run time hours: ");
    fgets(selection, 15, stdin);
    strtok(selection, "\n");
    
    hours = strtol(selection, &ptrSelection, 10);
    
    if (hours == FALSE || hours < 0x00 || hours > 0x18) {
        printf("Invalid input. Try again...\n");
        goto get_hours;
    }
    return hours;
}

long insertGetMinutes(char selection[]) {
    
    char *ptrSelection = NULL;
    long minutes;
    
    clearScreen();
    
get_min:
    printf("Enter the run time minutes: ");
    fgets(selection, 15, stdin);
    strtok(selection, "\n");
    
    minutes = strtol(selection, &ptrSelection, 10);
    
    if (minutes == FALSE || minutes < 0x00 || minutes > 0x3B) {
        printf("Invalid input. Try again...\n");
        goto get_min;
    }
    return minutes;
}

long insertGetYear(char selection[]) {
    
    char *ptrSelection = NULL;
    long year;
    
    clearScreen();
    
get_year:
    printf("Enter the year: ");
    fgets(selection, 15, stdin);
    strtok(selection, "\n");
    
    year = strtol(selection, &ptrSelection, 10);
    
    if (year == FALSE || year > 0x7E4) {
        printf("Improper date. Exceeds 2020. Try again...\n");
        goto get_year;
    }
    return year;
}

long insertGetTimesPlayed(char selection[]) {
    
    char *ptrSelection = NULL;
    long numTimes;
    
    clearScreen();
    
get_times_played:
    printf("Enter how many times it has been played: ");
    fgets(selection, 15, stdin);
    strtok(selection, "\n");
    
    numTimes = strtol(selection, &ptrSelection, 10);
    
    if (numTimes == FALSE || numTimes < 0x00) {
        printf("Error. Try again...\n");
        goto get_times_played;
    }
    return numTimes;
}

long insertGetRating(char selection[]) {
    
    char *ptrSelection = NULL;
    long rating;
    
    clearScreen();
    
get_rating:
    printf("Enter a rating [1-5]: ");
    fgets(selection, 15, stdin);
    strtok(selection, "\n");
    
    rating = strtol(selection, &ptrSelection, 10);
    if (rating == FALSE || rating < 1 || rating > 5) {
        printf("Rating must be between 1 and 5. Try again...\n");
        goto get_rating;
    }
    return rating;
}

Bool insert(Node **pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/25/2020
     Description: Main driver to insert a new record into the node.
                  Does not store the information in the file, must be
                  done by user in the main menu.
     Precondition: Functions insertGet...() must be present, and Record struct
                   passed into function.
     */
    
    Record tempData;
    char selection[250];
    long longVariable;
    
    insertGetFilmTitle(selection);
    strncpy(tempData.filmTitle, selection, sizeof(tempData.filmTitle));
    insertGetDirector(selection);
    strncpy(tempData.director, selection, sizeof(tempData.director));
    insertGetDescription(selection);
    strncpy(tempData.description, selection, sizeof(tempData.description));
    insertGetGenre(selection);
    strncpy(tempData.genre, selection, sizeof(tempData.genre));
    
    longVariable = insertGetHours(selection);
    tempData.runTime.hours = (int)longVariable;
    longVariable = insertGetMinutes(selection);
    tempData.runTime.minutes = (int)longVariable;
    longVariable = insertGetYear(selection);
    tempData.year = (int)longVariable;
    longVariable = insertGetTimesPlayed(selection);
    tempData.numTimesPlayed = (int)longVariable;
    longVariable = insertGetRating(selection);
    tempData.rating = (int)longVariable;
    
    insertNode(pRecord, tempData);
    return TRUE;
}
