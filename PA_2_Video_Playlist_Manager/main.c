//
//  main.c
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/9/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"
#include "testFunctionsHeader.h"

int main(int argc, const char * argv[]) {
    /*
     Name: Kyle Hurd
     Date: 09/14/2020
     Description: Main driver for the movie playlist. Current functions that
                  work are load, store, display, edit, rate, and play.
     */
    
    srand((unsigned int)time(NULL));
    
    // OPENING FILES
    FILE *recordFile  = fopen("moviePlayList.csv", "r+");
    Bool response;
    
    response = isOpen(recordFile);
    
    // VARIABLE DECLARATIONS
    long answer;
    Node *pRecord = NULL;
    
    // LOADING FROM RECORDFILE
    response = loadRecords(recordFile, &pRecord);
    
    // START OF CODE
    insertTestFunction();
    deleteTestFunction();
    shuffleTestFunction();
    
start:
    displayMainMenu(&answer);
    clearScreen();
    if (driverMainMenuExceedBounds(answer) == TRUE) goto start;
    else {
        switch (answer) {
            case 1: // LOAD
                response = loadRecords(recordFile, &pRecord);
                success(response);
                break;
            case 2: // STORE
                response = storeRecords(recordFile, pRecord);
                success(response);
                break;
            case 3: // DISPLAY
                response = displayRecords(pRecord);
                success(response);
                break;
            case 4: // INSERT
                response = insert(&pRecord);
                success(response);
                break;
            case 5: // DELETE
                response = delete(&pRecord);
                success(response);
                break;
            case 6: // EDIT
                response = editRecords(&pRecord);
                success(response);
                break;
            case 7: // SORT
                printf("Not operable at this time.\n");
                break;
            case 8: // RATE
                response = rate(&pRecord);
                success(response);
                break;
            case 9: // PLAY
                response = playMovies(pRecord);
                break;
            case 10: // SHUFFLE
                response = shuffle(&pRecord);
                success(response);
                break;
            case 11: // EXIT
                response = storeRecords(recordFile, pRecord);
                success(response);
                goto exit;
                break;
            default:
                printf("Could not select option %ld\n", answer);
                   }
    }
    goto start;
    
exit:
    fclose(recordFile);
    return 0;
}
