//
//  main.cpp
//  Hunt_The_Wumpus
//
//  Created by Kyle Hurd on 10/5/20.
//

#include "GameWorld.hpp"
#include "functions.hpp"

int main(int argc, const char * argv[]) {
    /*
     Name: Kyle Hurd
     Date: 10/05/2020
     Description: Hunt the Wumpus Driver. Initiates a state of class GameWorld and
                  runs the game. Also outputs each game result to an outfile including
                  the score, total actions performed, outcome of game, and the user's
                  name.
     */
    
    // Declarations
    srand((unsigned int)time(NULL));
    int state = 0x00;
    
    // Opening File
    ofstream outfile;
    openOutFile(outfile);
    if (outfile.is_open()) print("HUNT THE WUMPUS RESULTS", outfile);
    
    // Start of Code
    GameWorld G1;
    G1.setName();
    bool flag = true;
    do {
    new_game:
        G1.reset();
        flag = true;
        clearScreen();
        displayGameRules();
        do { // 0 - no action, 1 - goto new_game, 2 - goto end
            
            G1.displayWorld();
            G1.GameDriver(state);
            
            // Reinitialize State
            // Branch Conditions
            switch (state) {
                case 0x00:
                    break;
                case 1:
                    state = 0x00;
                    goto new_game;
                    break;
                case 2:
                    state = 0x00;
                    goto end;
                    break;
                default: // should not happen
                    state = 0x00;
                    print("Error in main() line 53 -- 'state' of type <int>");
                    break;
            }
            
        } while (!G1.didIWin() && !G1.didILose());
        
        // Game Complete
        if (outfile.is_open()) outfile << G1;
        clearScreen();
        G1.displayWorld(1);
        if (G1.didIWin()) print("Congratulations! You win!");
        else print("You lost. Better luck next time.");
        askToEnd(flag);
    } while (flag == true);
    
    // End of Game
end:
    clearScreen();
    if (outfile.is_open()) print("File updated and closed. Thanks for playing!");
    outfile.close();
    print("Exiting program...");
    return 0;
}
