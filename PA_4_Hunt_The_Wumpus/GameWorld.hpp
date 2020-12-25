//
//  huntTheWumpus.hpp
//  Hunt_The_Wumpus
//
//  Created by Kyle Hurd on 10/5/20.
//

#ifndef GameWorld_hpp
#define GameWorld_hpp

#include <iostream>
#include <random>

using namespace std;

class GameWorld {
    
private:
    std::string name;
    
    char        worldArray[0x05][0x05];
    int         totalPoints;
    int         totalActions;
    int         xLocation;
    int         yLocation;
    bool        win;
    bool        lose;
    
public:
    // Default Constructors
    GameWorld();
    
    // Driver
    void   GameDriver(int &);
    
    // Class Functions
    bool   moveUp();
    bool   moveDown();
    bool   moveLeft();
    bool   moveRight();
    
    void   reset();
    string getName() const;
    void   setName();
    int    getTotalPoints() const;
    void   setTotalPoints(int);
    int    getTotalActions() const;
    void   setTotalActions(int);
    
    void   displayWorld(int = 0) const;
    
    void   addPoints(int);
    void   addMoves(int);
    
    bool   didIWin() const;
    bool   didILose() const;
};

// Overloading
ostream &operator<< (ostream &output, const GameWorld &G);

#endif /* GameWorld_hpp */
