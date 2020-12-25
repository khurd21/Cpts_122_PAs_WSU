//
//  functions.cpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

#include "functions.hpp"

void delay(int s) {
    cout << "Screen will refresh in " << s << " seconds." << endl;
    std::this_thread::sleep_for(chrono::seconds(s));
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
    cout << "OS not supported for clearing screen." << endl;
#endif
}

void getUserInput(string &c) {
loop:
    cout << "Provide an input: ";
    getline(cin, c);
    if (c.length() > 0x01) goto loop;
}

void print(string n, ostream &output) {
    output << n << endl;
}

void openInFile(fstream &file) {
    
    file.open("DeckData.csv", ios::in);
    //file.close();
    //file.open("GameScores.txt", ios::out | ios::app);
    if (file.is_open()) print("File opened successfully.");
    else                print("File could not be opened. Cannot read data.");
}

bool checkBounds(int start, int end, int target) {
    // checks if a target integer is within prescribed bounds
    return ((target <= end) && (target >= start) ? true : false);
}

void getCardSelection(string &input, string statement) {
    
loop:
    cout << "Select which monster to add to " << statement << " Queue: " << endl;
    getUserInput(input);
    
    if (input.length() > 0x01) goto loop;
    if (!checkBounds(0x01, 0x05, (input[0] - '0'))) goto loop;
}

void getQueueSelection(string &input) {
    
loop:
    cout <<
    "Select which Queue to flip a card: "   << endl <<
    "[1] Attack  Queue"                     << endl <<
    "[2] Defense Queue"                     << endl <<
    "Input: "                               ;
    getline(cin, input);
    
    if (input.length() > 0x01) goto loop;
    if ((input[0] - '0') < 0x01 || (input[0] - '0') > 0x02) goto loop;
}

void displayMenu() {
    
    string input;
    
    cout <<
    "**WELCOME TO YUGIOH**" << endl <<
    "Here are the rules:" << endl <<
    "1. You have an option to make up to 30 unique cards for your deck" << endl <<
    "   The rest will be filled by the prebuilt deck." << endl <<
    "2. Each round, you will add a Monster to the attack queue and another" << endl <<
    "   to the defense queue." << endl <<
    "3. After selecting which cards to add to queue, you will select which monster" << endl <<
    "   to play. Life Points will be removed if the attack damage is higher than the" << endl <<
    "   defense or attack points of the opposing Monster." << endl ;
    
loop:
    print("Select 'Y' to begin or 'N' to quit.");
    getUserInput(input);
    if (tolower(input[0]) == 'y') {
        return;
    }
    else if (tolower(input[0]) == 'n') {
        print("Hope to see you soon.");
        exit(0);
    }
    else {
        goto loop;
    }
}
