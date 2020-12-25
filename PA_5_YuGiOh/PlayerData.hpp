//
//  PlayerData.hpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

#ifndef PlayerData_hpp
#define PlayerData_hpp

#include <iostream>
#include "functions.hpp"
#include "Deck.hpp"
#include "Queue.hpp"

using namespace std;

class PlayerData {
    
private:
    int         lifePoints;
    Monster     hand[0x05];

    Queue       atkQueue;
    Queue       defQueue;
    
public:
    // Default Constructors
    PlayerData();
    
    // Destructors
    ~PlayerData() {};
    void    clear();
    
    // Class Functions
    int     getLifePoints();
    void    incLifePoints(int);
    bool    amIDead();
    // Monster getMonsterData(int);
    
    void    displayHand() const;
    void    fillHand(Deck &);
    void    enqueueAtk(int);
    void    enqueueDef(int);
    void    dequeueAtk(Monster &);
    void    dequeueDef(Monster &);
    void    removeCard(int);
    bool    isFull();
    
    friend ostream &operator<< (ostream &, const PlayerData &P);
};

void timeToDual(Monster &M1, bool mode1, Monster &M2, bool mode2, PlayerData &P1, PlayerData &P2);

#endif /* PlayerData_hpp */
