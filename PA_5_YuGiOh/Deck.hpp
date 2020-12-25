//
//  Deck.hpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <iostream>
#include "functions.hpp"

using namespace std;

struct Monster {
    
    string  name;
    string  type;
    int     level;
    string  race;
    string  attribute;
    int     attackPoints;
    int     defensePoints;
};

class Deck {
    
private:
    struct Node {
        Monster cardData;
        Node *next;
    };
    Node *top;
    
    int numItems;
    
public:
    
    // Constructors
    Deck();
    void initDeck(fstream &, int);
    int  initNewDeck();
    void setDeck(fstream &, int);
    
    // Destructors
    ~Deck();
    void clear();
    
    // Functions
    void displayDeck();
    void push(Monster);
    void pop(Monster &);
    bool isEmpty();
    
    // Overload for Deck
    friend ostream &operator<< (ostream &, const Deck &);
};

ostream &operator<< (ostream &, const Monster &);

#endif /* Deck_hpp */
