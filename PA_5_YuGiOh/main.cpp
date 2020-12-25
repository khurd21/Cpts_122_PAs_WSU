//
//  main.cpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

// #include "Tests/Test.hpp"

#include "functions.hpp"
#include "Deck.hpp"
#include "Queue.hpp"
#include "PlayerData.hpp"

int main(int argc, const char * argv[]) {
    
    // Declarations
    Deck D1, D2;
    PlayerData P1, P2;
    Monster M1, M2;
    
    // atk mode = true, def mode = false
    bool mode1, mode2;
    string input, prevInput;
    
    // Opening Files
    fstream infile;
    openInFile(infile);
    
new_game:
    clearScreen();
    displayMenu();

    // Initializing the Decks
    D1.setDeck(infile, 0x01);
    D2.setDeck(infile, 0x02);
    
    // Start of Game
    do {
        // Update the Hands
        P1.fillHand(D1);
        P2.fillHand(D2);
        
        if (!P1.isFull() || !P2.isFull())
            goto game_determined;
        
    player1: // Possible to condense it down to one call, but would require a temp PlayerData
        clearScreen();
        print("Player 1");
        cout << P1;
        getCardSelection(input, "ATK");
        prevInput = input;
        P1.enqueueAtk((input[0] - '1'));
        P1.removeCard((input[0] - '1'));
    p1_card:
        getCardSelection(input, "DEF");
        if (input == prevInput) {
            print("Select a different card.");
            goto p1_card;
        }
        P1.enqueueDef((input[0] - '1'));
        P1.removeCard((input[0] - '1'));
        getQueueSelection(input);
        if (input[0] == '1') {
            P1.dequeueAtk(M1);
            mode1 = true;
        }
        else {
            P1.dequeueDef(M1);
            mode1 = false;
        }
        
    player2:
        clearScreen();
        print("Player 2");
        cout << P2;
        getCardSelection(input, "ATK");
        prevInput = input;
        P2.enqueueAtk((input[0] - '1'));
        P2.removeCard((input[0] - '1'));
    p2_card:
        getCardSelection(input, "DEF");
        if (input == prevInput) {
            print("Select a different card.");
            goto p2_card;
        }
        P2.enqueueDef((input[0] - '1'));
        P2.removeCard((input[0] - '1'));
        getQueueSelection(input);
        if (input[0] == '1') {
            P2.dequeueAtk(M2);
            mode2 = true;
        }
        else {
            P2.dequeueDef(M2);
            mode2 = false;
        }
        
        timeToDual(M1, mode1, M2, mode2, P1, P2);
        
        clearScreen();
        cout <<
        "Player 1 Life Points: " << P1.getLifePoints() << endl;
        cout << M1;
        cout <<
        "Player 2 Life Points: " << P2.getLifePoints() << endl ;
        cout << M2;
        
        delay(0x08);
        
    } while ((!D1.isEmpty() && !D2.isEmpty()) &&
             ((P1.getLifePoints() > 0x00) &&
              (P2.getLifePoints() > 0x00)));
    
game_determined:
    
    // Declaring a Winner
    if (P1.getLifePoints() > P2.getLifePoints()) {
        print("Congratulations Player One! You have won.");
    }
    else {
        print("Congratulations Player Two! You have won.");
    }
play_again:
    print("Would you like to play again? (Y/N)");
    getUserInput(input);
    if (tolower(input[0]) == 'y') {
        P1.clear();
        D1.clear();
        P2.clear();
        D2.clear();
        goto new_game;
    }
    else if (tolower(input[0]) == 'n') goto end;
    else goto play_again;
    
end:
    print("Thanks for playing.");
    infile.close();
    
    return 0;
}
