//
//  displayFunctions.c
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/28/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"

void displayMoviesAndAmount (Node *pRecord, int *counter) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays the title of the movie and updates how
                  many movies there are in the doubly linked
                  list located at the head pRecord.
     */
            Node previous;
            
        loop:
            *counter += 1;
            
            if (pRecord != NULL) {
                printf("(%d) %s\n", *counter, pRecord->data.filmTitle);
                
                previous = *pRecord;
                pRecord = pRecord->next;
                goto loop;
            }
}

void displayMainMenu(long *answer) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays the main menu and takes an input
                  from the user and updates the passed in variable
                  via pointer.
     */
    char selection[5];
    char *ptrSelection;
    
try_again:
    printf("**MAIN MENU**\n(1) Load\n(2) Store\n(3) Display\n"
           "(4) Insert\n(5) Delete\n(6) Edit\n(7) Sort\n(8) Rate\n"
           "(9) Play\n(10) Shuffle\n(11) Exit\n");
    
    printf("Please select an option: ");
    fgets(selection, 5, stdin);
    
    *answer = strtol(selection, &ptrSelection, 10);
    if (*answer == FALSE) {
        clearScreen();
        printf("Error. '%s' is invalid. Try again.\n\n", ptrSelection);
        goto try_again;
    }
    else return;
}

void displayRecordsMenu(long *answer) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays the menu for how to display the records.
                  Options are
                  1. Display all movies
                  2. Print all records matching a director
                  3. Print all records matching a year
     */
    char selection[5];
        char *ptrSelection;
        
    try_again:
        printf("In what method would you like to display the records?\n"
               "(1) Print all movies\n"
               "(2) Print all records matching a director\n"
               "(3) Print all records matching a year\n");
        
        printf("Please select an option: ");
        fgets(selection, 5, stdin);
        
        *answer = strtol(selection, &ptrSelection, 10);
        if (*answer == FALSE) {
            clearScreen();
            printf("Error. '%s' is invalid. Try again.\n\n", ptrSelection);
            goto try_again;
        }
        else return;
}

Bool displayRecords(Node *pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: A driver to call other functions to display the
                  records within the linked list.
     */
    long answer;
    
start:
    displayRecordsMenu(&answer);
    clearScreen();
    if (driverRecordsMenuExceedBounds(answer) == TRUE) goto start;
    else {
        switch (answer) {
            case 1: // PRINT ALL MOVIES
                displayAllMovies(pRecord);
                break;
            case 2: // PRINT ALL RECORDS MATCHING A DIRECTOR
                displayRecordsByDirector(pRecord);
                break;
            case 3: // PRINT ALL RECORDS MATCHING A YEAR
                displayRecordsByYear(pRecord);
                break;
            default: // SHOULD NOT HAPPEN
                printf("Error within displayRecords() switchcase.\n");
                break;
        }
    }
    return TRUE;
}

void displayAllMovies (Node *pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays all the movies from linked list.
     */
    int counter = 0;
    Node previous;
    
loop:
    counter += 1;
    
    if (pRecord != NULL) {
        printf("(%d) %s\n", counter, pRecord->data.filmTitle);
        
        previous = *pRecord;
        pRecord = pRecord->next;
        goto loop;
    }
}

void displayRecordsByDirector (Node *pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays the records that match the director
                  name entered by user. If no directors match search,
                  program exits without printing to screen.
     */
    Node previous;
    char selection[25];
    Bool flag = FALSE;
    
    printf("Enter a director to search [CASE SENSITIVE]: ");
    fgets(selection, sizeof(selection), stdin);
    
loop:
    if (pRecord != NULL) {
        if (strncmp(selection, pRecord->data.director, strlen(selection) - 1) == 0) {
            flag = TRUE;
            printf("Film Title:   %s\n"
                   "Director:     %s\n"
                   "Genre:        %s\n"
                   "Run Time:     %d:%02d\n"
                   "Year:         %d\n"
                   "Times Played: %d\n"
                   "Rating:       %d\n"
                   "Description:  %s\n\n"
                   "*********************\n",
                   pRecord->data.filmTitle, pRecord->data.director,
                   pRecord->data.genre, pRecord->data.runTime.hours,
                   pRecord->data.runTime.minutes,
                   pRecord->data.year, pRecord->data.numTimesPlayed,
                   pRecord->data.rating, pRecord->data.description
                   );
        }
        
        previous = *pRecord;
        pRecord = pRecord->next;
        goto loop;
        
    }
    else if (flag == FALSE) {
        printf("No such director found. Returning to main menu....\n");
    }
    else {
        printf("Done with operation.\n");
    }
}

void displayRecordsByYear (Node *pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays the records that match a specific year
                  If no records match the search, nothing is outputted
                  to the screen.
     */
    Node previous;
    char selection[10];
    char *ptrSelection = NULL;
    long tempYear;
    Bool flag = FALSE;
  
try_again:
    printf("Enter a year to search: ");
    fgets(selection, 10, stdin);
    strtok(selection, "\n");
    
    tempYear = strtol(selection, &ptrSelection, 10);
    if (tempYear == FALSE) {
        clearScreen();
        printf("Error. %s is invalid. Try again.\n", ptrSelection);
        goto try_again;
    }
    
loop:
    if (pRecord != NULL) {
        if (pRecord->data.year == tempYear) {
            flag = TRUE;
            printf("Film Title:   %s\n"
            "Director:     %s\n"
            "Genre:        %s\n"
            "Run Time:     %d:%02d\n"
            "Year:         %d\n"
            "Times Played: %d\n"
            "Rating:       %d\n"
            "Description:  %s\n\n"
            "*********************\n",
            pRecord->data.filmTitle, pRecord->data.director,
            pRecord->data.genre, pRecord->data.runTime.hours,
            pRecord->data.runTime.minutes,
            pRecord->data.year, pRecord->data.numTimesPlayed,
            pRecord->data.rating, pRecord->data.description
            );
        }
        previous = *pRecord;
        pRecord = pRecord->next;
        goto loop;
    }
    else if (flag == FALSE) {
        printf("No records with such year. Returning to main menu....\n");
    }
    else {
        printf("Operation successful.\n");
    }
}

Bool displayMatchAndNumber (int *i, Node **pRecord, char* selection) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays a record that matches what the user inputted.
                  Also updates how many matches there were and updates
                  the int pointed to by i.
     */
    Bool flag = FALSE;
    Node *current = *pRecord;
    
loop: // make this a function
    if (current != NULL) {
        if (strncmp(selection, current->data.director, sizeof(selection) - 1) == 0) {
            flag = TRUE;
            *i += 1;
            printf("Match number (%d)\n"
                   "Film Title:   %s\n"
                   "Director:     %s\n"
                   "Genre:        %s\n"
                   "Run Time:     %d:%02d\n"
                   "Year:         %d\n"
                   "Times Played: %d\n"
                   "Rating:       %d\n"
                   "Description:  %s\n\n"
                   "*********************\n",
            *i, current->data.filmTitle, current->data.director,
            current->data.genre, current->data.runTime.hours,
            current->data.runTime.minutes,
            current->data.year, current->data.numTimesPlayed,
            current->data.rating, current->data.description
            );
        }
        
        current = current->next;
        goto loop;
    }
    return flag;
}

void displayMoviesToRate(Node **pRecord, int *counter) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Displays movies to update the rating and updates
                  the variable counter to update the variable pointed to by
                  counter.
     */
    Node *current = *pRecord;
loop:
    
    if (current != NULL) {
        *counter += 1;
        printf("(%d) %s\n", *counter, current->data.filmTitle);
        
        current = current->next;
        goto loop;
    }
}
