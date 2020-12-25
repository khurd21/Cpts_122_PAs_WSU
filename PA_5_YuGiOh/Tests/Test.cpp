//
//  Test.cpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

#include "Test.hpp"

void testDeckPushPop() {
    
    Deck D1;
    Monster M1;
    
    M1.name          = "Test Monster";
    M1.type          = "Test Type";
    M1.level         = 0x04;
    M1.race          = "American";
    M1.attribute     = "What even is an attribute?";
    M1.attackPoints  = 0x5F;
    M1.defensePoints = 0xFF;
    
    print("Pushing type<Monster> onto Deck:");
    D1.push(M1);
    
    print("Displaying type<Deck> all items in Stack:");
    cout << D1;
    
    M1.name         = "Test Monster2";
    print("Pushing type<Monster> onto Deck:");
    D1.push(M1);
    
    print("Displaying type<Deck> all items in Stack:");
    cout << D1;
    
    print("The following card popped from deck:");
    D1.pop(M1);
    cout << M1;
}

void testPlayerData() {
    
    PlayerData P;
    
    print("Following Data should be empty.\n");
    cout << P;
    
    print("Subtracting life points by 500\n");
    P.incLifePoints(-0x1F4);
    cout << P;
}

void testQueue() {
    
    Queue Q;
    Monster M;
    
    M.name          = "Test Monster";
    M.type          = "Test Type";
    M.level         = 0x04;
    M.race          = "American";
    M.attribute     = "What even is an attribute?";
    M.attackPoints  = 0x5F;
    M.defensePoints = 0xFF;
    
    print("Enqueing a monster.");
    Q.enqueue(M);
    
    if (Q.isEmpty()) print("Enque failed. Queue is empty.");
    else print("Enqueue successful. Queue is not empty");
    
    print("Dequeue item.");
    Q.dequeue(M);
    
    if (Q.isEmpty()) print("Success. Queue is now empty.");
    else print("Error. Queue is not empty.");
}


