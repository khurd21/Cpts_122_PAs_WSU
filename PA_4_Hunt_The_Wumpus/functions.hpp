//
//  functions.hpp
//  Hunt_The_Wumpus
//
//  Created by Kyle Hurd on 10/5/20.
//

#ifndef functions_hpp
#define functions_hpp

// Libraries
#include <stdlib.h>
#include <iostream>
#include <random>
#include <ctype.h>
#include <fstream>

// Functions
using namespace std;

void    print(string, ostream & = cout);
void    clearScreen(void);
void    askToEnd(bool &);
void    getUserInput(char &);
void    displayGameRules(void);
void    displayInvalidMovement(void);
void    openOutFile(ofstream &);

#endif /* functions_hpp */
