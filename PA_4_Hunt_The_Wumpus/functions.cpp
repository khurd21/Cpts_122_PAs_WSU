//
//  functions.cpp
//  Hunt_The_Wumpus
//
//  Created by Kyle Hurd on 10/5/20.
//

#include "functions.hpp"

void clearScreen(void) {
    /*
     Borrowed from StackOverflow to clear the screen depending on OS
     */
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) && defined(__MACH__)
    system("clear");
#else
    cout << "OS not supported for clearing screen." << endl;
#endif
}

void askToEnd(bool &n) {
    
    char answer;
loop:
    print("Would you like to play again (Y/N)? ");
    cin >> answer;
    switch (toupper(answer)) {
        case 'Y':
            n = true;
            break;
        case 'N':
            n = false;
            break;
        default:
            print("Enter a valid input.");
            goto loop;
            break;
    }
}

void getUserInput(char &c) {
    cout << "Provide an input: ";
    cin >> c;
}

void displayGameRules() {
    
    print("**Welcome to Hunt the Wumpus**\n"
            "Here are the instructions: \n"
            "You will be located on a 5x5 grid. It is your goal to move around without coming in contact\n"
            "with the Wumpus (W) or falling into any pits (P). If you find the gold (G) before hitting these\n"
            "obsticles you will win the game!\n"
            "-5 points awarded for every successful move\n"
            "-minus 2 points for hints (C)\n"
          "-minus 5 points for seeing the entire world.\n");
}

void displayInvalidMovement() {
    print("Invalid movement. Try another location.");
}

void openOutFile(ofstream &file) {
    
    file.open("GameScores.txt", ios::out | ios::trunc);
    //file.close();
    //file.open("GameScores.txt", ios::out | ios::app);
    if (file.is_open()) {
        print("File opened successfully.");
    }
    else {
        print("File could not be opened. Will not save data.");
    }
}

void print(string n, ostream &output) {
    output << n << endl;
    // print("String")
}
