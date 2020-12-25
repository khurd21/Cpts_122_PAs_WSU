//
//  shuffleFunctions.c
//  Video_Playlist_Manager
//
//  Created by Kyle Hurd on 9/28/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "header.h"

int shuffleNumMovies(Node *pRecord) {
    
    Node tempNode = *pRecord;
    int i = 1;
    
    while (!isEmpty(tempNode.next)) {
        i++;
        tempNode = *tempNode.next;
    }
    return i;
}

void shuffleFillArray(int array[], int numMovies) {
    
    int num;
    
    for (int i = 0; i < numMovies; i++) {
    pick_another:
        num = rand() % ((numMovies + 1) - 1) + 1;
        if (i == 0) {
            array[i] = num;
        }
        else {
            for (int j = 0; j < i; j++) {
                if (array[j] == num) {
                    goto pick_another;
                }
            }
            array[i] = num;
        }
    }
}

void shuffleIncrementUpToTarget(Node *tempNode, int target, int nodeLocation) {
    
    while (nodeLocation < target) {
        nodeLocation = nodeLocation + 1;
        tempNode = tempNode->next;
    }
    shufflePlayMovie(tempNode);
}

void shufflePlayMovie(Node *pRecord) {
    
    clearScreen();
    
    printf("Playing movie...\n"
           "Title: %s\n"
           "Director: %s\n"
           "Runtime: %d:%02d\n"
           "Genre: %s\n"
           "Description: %s\n",
           pRecord->data.filmTitle, pRecord->data.director,
           pRecord->data.runTime.hours, pRecord->data.runTime.minutes,
           pRecord->data.genre, pRecord->data.description);
}

void shufflePlayMovies(Node *pRecord, int *array, int numMovies) {
    
    Node tempNode = *pRecord;
    int nodeLocation = 1;
    
    for (int i = 0; i < numMovies; i++) {
        if (nodeLocation < array[i]) { // incrememnt up to the target number *(array + i)
            shuffleIncrementUpToTarget(&tempNode, array[i], nodeLocation);
        }
        else {
            shufflePlayMovie(pRecord);
        }
        delay(5);
    }
} // NOT DONE

Bool shuffle(Node **pRecord) {
    /*
     Name: Kyle Hurd
     Date: 09/25/2020
     Description: Provides a random order in which the movies are
                  played. Does not modify the links in the list.
     
     MY NOTES: Must count how many movies are in list, and then
               play the specific movie at that number.
     */
    
    int numMovies = 0;
    
    numMovies = shuffleNumMovies(*pRecord);
    int array[numMovies];
    
    shuffleFillArray(array, numMovies);
    shufflePlayMovies(*pRecord, array, numMovies);
    
    return TRUE;
}
