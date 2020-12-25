//
//  PlayerData.cpp
//  Yugioh
//
//  Instructions for the class PlayerData
//
//  Created by Kyle Hurd on 10/12/20.
//

#include "PlayerData.hpp"

PlayerData::PlayerData() {
    
    // Temporary Monster
    Monster temp;
    temp.attackPoints   = -0x01;
    temp.defensePoints  = -0x01;
    temp.attribute      = "EMPTY";
    temp.level          = -0x01;
    temp.name           = "EMPTY";
    temp.race           = "EMPTY";
    temp.type           = "EMPTY";
    
    // Private Variables
    lifePoints          = 0x1F40;
   
    for (int i = 0x00; i < 0x05; i++) {
        hand[i] = temp;
    }
}

void PlayerData::clear() {
    
    // Temporary Monster
    Monster temp;
    temp.attackPoints   = -0x01;
    temp.defensePoints  = -0x01;
    temp.attribute      = "EMPTY";
    temp.level          = -0x01;
    temp.name           = "EMPTY";
    temp.race           = "EMPTY";
    temp.type           = "EMPTY";
    
    // Re-initializing Items in Class
    lifePoints          = 0x1F40;
    atkQueue.clear();
    defQueue.clear();
    
    for (int i = 0x00; i < 0x05; i++) {
        hand[i] = temp;
    }
}

int PlayerData::getLifePoints() {
    return lifePoints;
}

void PlayerData::incLifePoints(int n) {
    lifePoints += n;
}

bool PlayerData::amIDead() {
    return (0x01 * (lifePoints <= 0x00));
}

void PlayerData::displayHand() const {
    
    for (int i = 0x00; i < 0x05; i++) {
        cout <<
        "**Card " << i + 0x01 << "**"      << endl <<
        "Name: "  << hand[i].name          << endl <<
        "Type: "  << hand[i].type          << endl <<
        "ATK: "   << hand[i].attackPoints  << endl <<
        "DEF: "   << hand[i].defensePoints << endl << endl;
    }
}

void PlayerData::fillHand(Deck &D) {

    // Declaring Temp Variables
    Monster M;
    int i = 0x00;
    
    // Start of Code
loop:
    if ((hand[i].attackPoints == -0x01) && (!D.isEmpty())) {
        D.pop(M);
        hand[i] = M;
    }
    if (++i < 0x05) goto loop;
}

bool PlayerData::isFull() {
    
    for (int i = 0x00; i < 0x05; i++) {
        if (hand[i].attackPoints == -0x01) {
            return false;
        }
    }
    return true;
}

void PlayerData::enqueueAtk(int n) {
    atkQueue.enqueue(hand[n]);
}

void PlayerData::enqueueDef(int n) {
    defQueue.enqueue(hand[n]);
}

void PlayerData::dequeueAtk(Monster &M) {
    atkQueue.dequeue(M);
}

void PlayerData::dequeueDef(Monster &M) {
    defQueue.dequeue(M);
}

void PlayerData::removeCard(int n) {
    
    // Declaring Temp Variables
    Monster M;
    
    M.attackPoints  = -0x01;
    M.attribute     = "EMPTY";
    M.defensePoints = -0x01;
    M.level         = -0x01;
    M.name          = "EMPTY";
    M.race          = "EMPTY";
    M.type          = "EMPTY";
    
    // Setting the designated card at n to empty card.
    hand[n] = M;
}

void timeToDual(Monster &M1, bool mode1, Monster &M2, bool mode2, PlayerData &P1, PlayerData &P2) {
    
    // bool mode: true for attack, false for defense
    
    if      (mode1 && mode2) { // both in attack mode
        P1.incLifePoints((M1.attackPoints - M2.attackPoints) * (M1.attackPoints < M2.attackPoints));
        P2.incLifePoints((M2.attackPoints - M1.attackPoints) * (M1.attackPoints > M2.attackPoints));
    }
    else if (mode1 && !mode2) { // p1 in attack, p2 in defense
        P2.incLifePoints((M2.defensePoints - M1.attackPoints) * (M1.attackPoints > M2.defensePoints));
    }
    else if (!mode1 && mode2) { // p1 in defense, p2 in attack
        P1.incLifePoints((M1.defensePoints - M2.attackPoints) * (M1.defensePoints < M2.attackPoints));
    }
    else { // p1 in defense, p2 in attack
        print("No contest.");
    }
}

ostream &operator<< (ostream &output, const PlayerData &P) {

    // Variable Declarations
    Monster M;
    
    // Start of Code
    // Life Points
    cout <<
    "Life Points: " << P.lifePoints << endl <<
    
    // Hand
    "Hand: "        << endl;
    for (int i = 0x00; i < 0x05; i++) {
        M = P.hand[i];
        
        cout <<
        i + 0x01  << ". "            << endl <<
        "Name:  " << M.name          << endl <<
        "Level: " << M.level         << endl <<
        "ATK:   " << M.attackPoints  << endl <<
        "DEF:   " << M.defensePoints << endl << endl;
    }

    // Number of Cards in Each Queue
    cout <<
    "Number of Cards in ATK Queue: " << P.atkQueue << endl <<
    "Number of Cards in DEF Queue: " << P.defQueue << endl;
     
    return output;
}
