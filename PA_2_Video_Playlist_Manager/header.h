//
//  header.h
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/9/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE     250
#define SEPARATED_VALUE ","
#define DATA_PER_LINE 8

// ENUMERATED VALUE BOOLEAN
typedef enum bool {
    FALSE, TRUE
} Bool;

// STRUCT DURATION
typedef struct duration {
    int hours;
    int minutes;
} Duration;

// STRUCT RECORD
typedef struct record {
    
    char filmTitle[50];
    char director[50];
    char description[BUFFER_SIZE];
    char genre[15];
    
    Duration runTime;
    
    int year;
    int numTimesPlayed;
    int rating;
    
    struct record *previous;
    struct record *next;
} Record;

// STRUCT NODE
typedef struct node {
    Record data;
    struct node *previous;
    struct node *next;
} Node;

// FUNCTION DECLARATIONS
// From displayMenuFunctions.c
void delay(int seconds);

Bool isOpen(FILE *file);

void displayMainMenu(long *answer);
Bool driverMainMenuExceedBounds(long answer);
void displayRecordsMenu(long *answer);
Bool driverRecordsMenuExceedBounds(long answer);

void clearScreen(void);
void success(Bool var);

// LINKED LIST FUNCTIONS
Bool isEmpty(Node *pNode);
void deleteList(Node **headRef);
Bool insertNode(Node **pRecord, Record data);

Bool loadRecords(FILE *recordFile, Node **pRecord);
Bool storeRecords(FILE *recordFile, Node *pRecord);
Bool displayRecords(Node *pRecord);

void displayAllMovies (Node *pRecord);
void displayRecordsByDirector (Node *pRecord);
void displayRecordsByYear (Node *pRecord);

Bool displayMatchAndNumber (int *i, Node **pRecord, char* selection);
Bool editRecords(Node **pRecord);
void editRecordAtN (Node **pRecord, int i, char* selection);

Bool rate(Node **pRecord);
void displayMoviesToRate(Node **pRecord, int *counter);
void displayMoviesAndAmount (Node *pRecord, int *counter);
Bool playMovies(Node *pRecord);

// INSERT DECLARATIONS
Bool containsComma(char array[]);
void insertGetDirector(char selection[]);
void insertGetFilmTitle(char selection[]);
void insertGetDescription(char selection[]);
void insertGetGenre(char selection[]);
long insertGetHours(char selection[]);
long insertGetMinutes(char selection[]);
long insertGetYear(char selection[]);
long insertGetTimesPlayed(char selection[]);
long insertGetRating(char selection[]);
Bool insert(Node **pRecord); // DRIVER FOR INSERT

// DELETE DECLARATIONS
Bool delete(Node **pRecord);

// SHUFFLE DECLARATIONS
Bool shuffleMemoryAllocated(int *array);
int shuffleNumMovies(Node *pRecord);
void shuffleFillArray(int array[], int numMovies);
void shuffleIncrementUpToTarget(Node *tempNode, int target, int nodeLocation);
void shufflePlayMovie(Node *pRecord);
Bool shuffle(Node **pRecord); // DRIVER FOR SHUFFLE

#endif /* header_h */
