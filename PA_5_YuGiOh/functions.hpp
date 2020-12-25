//
//  functions.hpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

#ifndef functions_hpp
#define functions_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

// General Functions
void delay(int);
void clearScreen(void);
void getUserInput(string &c);
void print(string n, ostream &output = cout);
void openInFile(fstream &file);
bool checkBounds(int,int,int);

void getCardSelection(string &, string);
void getQueueSelection(string&);
void displayMenu();
#endif /* functions_hpp */
