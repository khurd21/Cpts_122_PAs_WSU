//
//  linkedListFunctions.c
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/11/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"


// TIME FUNCTIONS

void delay(int seconds) {
    /*
     Borrowed from c-for-dummies.com
     Posted May 25, 2013
     Slightly modified, the original delay was in ms,
     this is in seconds.
     */
    long pause;
    clock_t now, then;
    
    pause = seconds * (CLOCKS_PER_SEC);
    now = then = clock();
    
    while ((now - then) < pause) {
        now = clock();
    }
}

Bool playMovies(Node *pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: "Plays" the movie by displaying the information
                  of each movie in the doubly linked list and waits
                  10 seconds before playing the next movie.
     */
    Node *current = pRecord;
    Bool flag1 = FALSE;
    char selection[5];
    char* ptrSelection = NULL;
    long answer;
    int counter = 0;
    
try_again:
    displayMoviesAndAmount(pRecord, &counter);
    printf("Select which movie to play first: ");
    fgets(selection, 5, stdin);
    strtok(selection, "\n");
    answer = strtol(selection, &ptrSelection, 10);
    if (answer == FALSE || answer < 1 || answer > counter) {
        clearScreen();
        printf("Error. %s is invalid. Try again.\n", ptrSelection);
        goto try_again;
    }
    counter = 1;
loop:
    if ((current != NULL && counter >= answer) || flag1 == TRUE) {
        clearScreen();
        if (counter == answer && flag1 == TRUE) goto end;
        printf("DISPLAYING FOR 10 SECONDS.\nTIME MAY DIFFER DEPENDING ON CLOCK SPEED.\n");
        printf("Film Title:   %s\n"
               "Director:     %s\n"
               "Genre:        %s\n"
               "Run Time:     %d:%02d\n"
               "Year:         %d\n"
               "Times Played: %d\n"
               "Rating:       %d\n"
               "Description:  %s\n\n"
               "*********************\n",
               current->data.filmTitle, current->data.director,
               current->data.genre, current->data.runTime.hours,
               current->data.runTime.minutes,
               current->data.year, current->data.numTimesPlayed,
               current->data.rating, current->data.description
               );
        current = current->next;
        counter++;
        delay(10);
        goto loop;
    }
    else if (counter < answer) {
        current = current->next;
        counter++;
        goto loop;
    }
    else if (current == NULL) {
        flag1 = TRUE;
        counter = 1;
        current = pRecord;
        goto loop;
    }
    
end:
    return TRUE;
}

// DISPLAY MENU AND FILE FUNCTIONS

Bool isOpen(FILE *file) {
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

void success(Bool var) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Takes a bool value and displays to the
                  terminal screen if the variable is
                  true or false.
     */
    if (var == TRUE) {
        printf("Operation successful.\n");
    }
    else {
        printf("Operation failed.\n");
    }
}

Bool driverMainMenuExceedBounds(long answer) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: If answer is between options available from meanu,
                  true is return. If bounds exceeded, FALSE returned.
     */
    Bool response;
    
    if (answer < 1 || answer > 11) {
        clearScreen();
        printf("Your input exceeded the bounds of the menu items.\n"
               "Nothing was computed. Returning to menu....\n");
        response = TRUE;
    }
    else {
        response = FALSE;
    }
    return response;
}

Bool driverRecordsMenuExceedBounds(long answer) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Determines if the answer inputted from user
                  exceeded bounds between 1 and 3. Returns TRUE
                  if yes, or FALSE is no.
     */
    Bool response;
    
    if (answer < 1 || answer > 3) {
        clearScreen();
        printf("Your input exceeded the bounds of the menu items.\n"
               "Nothing was computed. Returning to menu...\n");
        response = TRUE;
    }
    else {
        response = FALSE;
    }
    return response;
}

void clearScreen(void) {
    /*
     Borrowed from StackOverflow to clear the screen depending on OS
     */
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) && defined(__MACH__)
    system("clear");
#else
    printf("OS not supported for clearing screen.\n");
#endif
}


// LINKED LIST FUNCTIONS

Bool isEmpty(Node *pNode) {
    /*
     Name: Kyle Hurd
     Date: 09/12/2020
     Description: If pNode is NULL, returns Bool
                  type TRUE (1), else returns Bool type
                  FALSE (0).
     */
    return (pNode == NULL) ? TRUE : FALSE;
}

void deleteList(Node **headRef) {
    // BORROWED FROM NADRAS LECTURE
    Node *current = *headRef;
    
    while(!isEmpty(current)) {
        *headRef = current->next;
        free(current);
        current = *headRef;
    }
}

Bool insertNode(Node **pRecord, Record data) {
    /*
     Name: Kyle Hurd
     Date: 09/12/2020
     Description: Inserts a new node at the FRONT
                  of the linked list. Therefore
                  the previous node will be NULL
                  and next will be the head of
                  *pRecord
     */
    Node* newNode = NULL;
    newNode = (Node*)malloc(sizeof(Node));
    
    
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;
    
    if (*pRecord == NULL) { // new node was created
        *pRecord = newNode;
        return TRUE;
    }
    
    //if ((*pRecord)->next != NULL) {
    //    (*pRecord)->next->previous = newNode;
   // }
    
    newNode->next = *pRecord;
    newNode->next->previous = newNode;
    newNode->previous = NULL;
    *pRecord = newNode;
    
    return TRUE;
}

Bool loadRecords(FILE *recordFile, Node **pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/12/2020
     Description:  Reads all the records from the file and places
                   the information into a doubly linked list (the
                   main playlist). Each record read is inserted
                   at the front of the list.
     
     Precondition: Was told via the assignment on 09/12/2020 that
                   all information within the .csv will NOT be missing
                   and there is no error checking or for NULL characters
                   in this function.
     */
    
    // Bool declarations
    Bool flag = FALSE;
    Record tempData;
    
    // char declarations
    char tempArray[BUFFER_SIZE];
    char* tempToken;
    
    // for the switch case
    int dataLocation = 0;
    int i = 0; // to remove Film Title on .csv,  Should not ever be reinitialized
    int firstItem = 0;
    
    // START OF CODE
    rewind(recordFile);
    deleteList(pRecord);
    
loop:
    dataLocation = -1;
    firstItem = 0;
    
    if (!feof(recordFile) && flag == FALSE) {
        fgets(tempArray, sizeof(tempArray), recordFile);
        
    items:
        
        dataLocation++;
        
        if (dataLocation < DATA_PER_LINE) {
            if (firstItem == 0) {
                firstItem = 1;
                tempToken = strtok(tempArray, SEPARATED_VALUE);
                if (tempToken == NULL) goto end;
            }
            else {
                tempToken = strtok(NULL, SEPARATED_VALUE);
                if (tempToken == NULL) goto end;
            }
        
            switch (dataLocation) {
                case 0: // FILM TITLE
                    strncpy(tempData.filmTitle, tempToken, sizeof(tempData.filmTitle));
                    break;
                case 1: // DIRECTOR
                    strncpy(tempData.director, tempToken, sizeof(tempData.director));
                    break;
                case 2: // DESCRIPTION
                    strncpy(tempData.description, tempToken, sizeof(tempData.description));
                    break;
                case 3: // GENRE
                    strncpy(tempData.genre, tempToken, sizeof(tempData.genre));
                    break;
                case 4: // RUNNING TIME
                    sscanf(tempToken, "%d:%d", &tempData.runTime.hours, &tempData.runTime.minutes);
                    break;
                case 5: // YEAR
                    tempData.year = atoi(tempToken);
                    break;
                case 6: // TIMES PLAYED
                    tempData.numTimesPlayed = atoi(tempToken);
                    break;
                case 7: // RATING
                    tempData.rating = atoi(tempToken);
                    break;
                default:
                    printf("ERROR inside loadRecords() switch case. "
                           "dataLocation exceeded boundary.\n");
                    flag = TRUE;
                    break;
            }
            if (flag == FALSE) {
                goto items;
            }
            else return FALSE;
        }
        else if (flag == FALSE && dataLocation >= DATA_PER_LINE) {
            if (i != 0) {
                flag = !(insertNode(pRecord, tempData)); // WILL BE INITIALIZED IF FLAG IS FALSE
            }
            i++; // might be one off if ever needed.
            goto loop;
        }
        else return FALSE; // flag was TRUE indicating an error.
    }
    else if (flag == TRUE) {
        printf("Error while trying to load records.\n");
        return FALSE;
    }
    else {
    end:
        printf("Loaded records.\n");
        return TRUE;
    }
    
   // return FALSE; // SHOULD NOT HAPPEN
}

Bool storeRecords(FILE *recordFile, Node *pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Stores the records from the linked list into the
                  outfile. Also changes the file to move in write/read
                  mode.
     */
    fclose(recordFile);
    recordFile = fopen("moviePlayList.csv", "w+");
    fprintf(recordFile, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n");
    
loop:
    if (pRecord != NULL) {
        fprintf(recordFile,"%s,%s,%s,%s,%d:%02d,%d,%d,%d\n",
                pRecord->data.filmTitle, pRecord->data.director,
                pRecord->data.description, pRecord->data.genre,
                pRecord->data.runTime.hours, pRecord->data.runTime.minutes,
                pRecord->data.year, pRecord->data.numTimesPlayed,
                pRecord->data.rating);
        
        pRecord = pRecord->next;
        goto loop;
    }
    fclose(recordFile);
    recordFile = fopen("moviePlayList.csv", "r+");
    printf("Successfully stored records.\n");
    return TRUE;
}

void editRecordAtN (Node **pRecord, int i, char* selection) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Updates any part of information within a struct
                  about a record.
     */
    Node *current = *pRecord;
    Bool flag = FALSE;
    char answerStr[10];
    char *ptrAnswerStr = NULL;
    long answer = 0;
    int j = 0;
   
try_again:
    printf(
           "(1) Film Title\n"
           "(2) Director\n"
           "(3) Description\n"
           "(4) Genre\n"
           "(5) Run Time\n"
           "(6) Year\n"
           "(7) Times played\n"
           "(8) Rating\n"
           "(9) Exit without modifying\n"
           "Select an option to modify: "
           );
    
    fgets(answerStr, sizeof(answerStr), stdin);
    strtok(answerStr, "\n");
    answer = strtol(answerStr, &ptrAnswerStr, 10);
    
    if (answer == FALSE || answer < 1 || answer > 9) {
        clearScreen();
        printf("Error. %s is invalid. Try again.\n", ptrAnswerStr);
        goto try_again;
    }
    
loop:
    if (current != NULL && flag == FALSE) {
        if (strncmp(selection, current->data.director, sizeof(selection) - 1) == 0) {
            flag = (++j == i) ? TRUE : FALSE;
        }
        current = (flag == TRUE) ? current : current->next;
        goto loop;
    }
    else if (current != NULL && flag == TRUE) {
        switch (answer) {
            case 1: // FILM TITLE
            get_film_title:
                printf("Enter new film title: ");
                fgets(current->data.filmTitle, sizeof((*pRecord)->data.filmTitle) - 1, stdin);
                strtok(current->data.filmTitle, "\n");
                if (containsComma(current->data.filmTitle)) goto get_film_title;
                break;
            case 2: // DIRECTOR
            get_director:
                printf("Enter new director name: ");
                fgets(current->data.director, sizeof((*pRecord)->data.director) - 1, stdin);
                strtok(current->data.director, "\n");
                if (containsComma(current->data.director)) goto get_director;
                break;
            case 3: // DESCRIPTION
            get_description:
                printf("Enter new description [250 characters]: ");
                fgets(current->data.description, sizeof(current->data.description) - 1, stdin);
                strtok(current->data.description, "\n");
                if (containsComma(current->data.description)) goto get_description;
                break;
            case 4: // GENRE
            get_genre:
                printf("Enter new genre: ");
                fgets(current->data.genre, sizeof((*pRecord)->data.genre) - 1, stdin);
                strtok(current->data.genre, "\n");
                if (containsComma(current->data.genre)) goto get_genre;
                break;
            case 5: { // RUN TIME
                long hours = 0, min = 0;
                
            try_again_hours:
                printf("Enter hours: ");
                fgets(answerStr, sizeof(answerStr) - 1, stdin);
                strtok(answerStr, "\n");
                hours = strtol(answerStr, &ptrAnswerStr, 10);
                if (hours == FALSE || hours > 24 || hours < 0) {
                    clearScreen();
                    printf("Error. %s is invalid. Try again\n", ptrAnswerStr);
                    goto try_again_hours;
                }
                current->data.runTime.hours = (int)hours;
                
            try_again_min:
                printf("Enter minutes: ");
                fgets(answerStr, sizeof(answerStr) - 1, stdin);
                strtok(answerStr, "\n");
                min = strtol(answerStr, &ptrAnswerStr, 10);
                if (min == FALSE || min > 59 || min < 0) {
                    clearScreen();
                    printf("Error. %s is invalid. Try again\n", ptrAnswerStr);
                    goto try_again_min;
                }
                current->data.runTime.minutes = (int)min;
            }
                break;
            case 6: { // YEAR
                long year;
                
            try_again_year:
                printf("Enter the new year: ");
                fgets(answerStr, sizeof(answerStr) - 1, stdin);
                strtok(answerStr, "\n");
                year = strtol(answerStr, &ptrAnswerStr, 10);
                if (year == FALSE) {
                    clearScreen();
                    printf("Error. %s is not a valid input.\n", ptrAnswerStr);
                    goto try_again_year;
                }
                current->data.year = (int)year;
            }
                break;
            case 7: { // TIMES PLAYED
                long numTimes;
                
            try_again_times_played:
                printf("Enter the number of times played: ");
                fgets(answerStr, sizeof(answerStr) - 1, stdin);
                strtok(answerStr, "\n");
                numTimes = strtol(answerStr, &ptrAnswerStr, 10);
                if (numTimes == FALSE) {
                    clearScreen();
                    printf("Error. %s is not valid. Try again.\n", ptrAnswerStr);
                    goto try_again_times_played;
                }
                current->data.numTimesPlayed = (int)numTimes;
            }
                break;
            case 8: { // RATING
                long rating;
                
            try_again_rating:
                printf("Enter the new rating [1-5]: ");
                fgets(answerStr, sizeof(answerStr) - 1, stdin);
                strtok(answerStr, "\n");
                rating = strtol(answerStr, &ptrAnswerStr, 10);
                if (rating == FALSE || rating < 1 || rating > 5) {
                    clearScreen();
                    printf("Error. %s is not valid. Try again.\n", ptrAnswerStr);
                    goto try_again_rating;
                }
                current->data.rating = (int)rating;
            }
                break;
            default: // Case 9, exit without modifying.
                break;
        }
    }
    
}

Bool editRecords(Node **pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Driver program to edit records.
     */
    Bool flag = FALSE;
    char selection[25];
    char answerStr[25];
    char *ptrAnswerStr = NULL;
    int i = 0;
    long answer;
    
    printf("Enter a director to search [CASE SENSITIVE]: ");
    fgets(selection, sizeof(selection), stdin);
    
    flag = displayMatchAndNumber(&i, pRecord, selection);
    
    if (flag == TRUE) {
        
    try_again:
        
        printf("%d matches found. Select one of the 'Match Numbers' from above: ", i);
        fgets(answerStr, sizeof(answerStr) - 1, stdin);
        strtok(answerStr, "\n");
        
        answer = strtol(answerStr, &ptrAnswerStr, 10);
        
        if (answer == FALSE || answer < 1 || answer > i) {
            printf("Error. %s is invalid, try again.\n", ptrAnswerStr);
            goto try_again;
        }
        else {
            editRecordAtN(pRecord, (int)answer, selection);
        }
    }
    else if (flag == FALSE) {
        printf("No such director found. Returning to main menu....\n");
    }
    else {
        printf("Done with operation.\n");
    }
    return TRUE;
}

Bool rate(Node **pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: driver to update the record data of a struct
     */
    Node *current = *pRecord;
    char selection[5];
    char* ptrSelection = NULL;
    long rate, i = 0;
    int counter = 0, j = 0;
    
try_again_rate:
    displayMoviesToRate(pRecord, &counter);
    printf("Select the number to the movie you wish to rate: ");
    fgets(selection, sizeof(selection) - 1, stdin);
    strtok(selection, "\n");
    
    i = strtol(selection, &ptrSelection, 10);
    if (i == FALSE || i < 0 || i > counter) {
        clearScreen();
        printf("Error. %s is not valid. Try again.\n", ptrSelection);
        goto try_again_rate;
    }
    
loop:
    if (current != NULL) {
        if (++j == i) {
        try_again_rating:
            printf("Give the movie a new rating: ");
            fgets(selection, sizeof(selection) - 1, stdin);
            strtok(selection, "\n");
            
            rate = strtol(selection, &ptrSelection, 10);
            if (rate == FALSE || rate < 1 || rate > 5) {
                clearScreen();
                printf("Error. %s is invalid. Try again.\n", ptrSelection);
                goto try_again_rating;
            }
            printf("Rating %d changed to %d\n", current->data.rating, (int)rate);
            current->data.rating = (int)rate;
        }
        else {
            current = current->next;
            goto loop;
        }
    }
    
    return TRUE;
}

Bool containsComma(char array[]) {
    
    for(int i = 0; i < strlen(array);i++) {
        if (array[i] == ',') {
            printf("Error. Value cannot contain a comma.\n");
            return TRUE;
        }
    }
    return FALSE;
}

Bool delete(Node **pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/25/2020
     Description: Deletes a record by movie title. If movie
                  title is not found, the function exits without
                  deleting any record. If multiple movies with
                  same film title are present, it will delete the
                  first one in the list.
     */
    
    char selection[50];
    Bool flag = 0x00;
    Node *tempRecord = *pRecord;
    
    clearScreen();
    
    printf("Enter a movie title to delete [case sensitive]: ");
    fgets(selection, 49, stdin);
    strtok(selection, "\n");
    
loop:
    if (tempRecord != NULL) {
        if (strncmp(tempRecord->data.filmTitle, selection, sizeof(selection)) == 0) {
            flag = 0x01;
            if (tempRecord->previous != NULL && tempRecord->next != NULL) {
                tempRecord->previous->next = tempRecord->next;  //  1 2 3
                tempRecord->next->previous = tempRecord->previous;
            }
            else if (tempRecord->previous == NULL) {
                *pRecord = (*pRecord)->next;
                (*pRecord)->previous = NULL;
            }
            else {
                tempRecord->previous->next = NULL;
            }
            free(tempRecord); // Fly away Stanley, be free.
            printf("Movie found and deleted.\n");
            return flag;
        }
        tempRecord = tempRecord->next;
        goto loop;
    }
    
    printf("Movie not found. Returning to main menu....\n");
    return flag;
}
