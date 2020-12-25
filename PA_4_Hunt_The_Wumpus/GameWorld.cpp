//
//  functions.cpp
//  Hunt_The_Wumpus
//
//  Created by Kyle Hurd on 10/5/20.
//

#include "GameWorld.hpp"
#include "functions.hpp"

GameWorld::GameWorld() {
    name = "User";
    reset();
}

void GameWorld::GameDriver(int &state) {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: GameDriver for class GameWorld. Takes an input from the user
                  and executes the action declared to the character (eg. move up,
                  move down, restart, change name, quit, ...). Scores and number of
                  actions are updated in addition to the player's movement in the 2D
                  array.
     */
    
    // Declarations
    char userInput;
    bool flag = true;
    
    // Start of Code
top_of_switch: // 0 - no action, 1 - goto new_game, 2 - goto end
    getUserInput(userInput);
    switch (toupper(userInput)) {
        case 'I': // move up
            if (!moveUp()) {
                displayInvalidMovement();
                goto top_of_switch;
            }
            else addMoves(1);
            if (flag && !didILose()) addPoints(0x05);
            else flag = true;
            clearScreen();
            break;
        case 'K': // move down
            if (!moveDown()) {
                displayInvalidMovement();
                goto top_of_switch;
            }
            else addMoves(1);
            if (flag && !didILose()) addPoints(0x05);
            else flag = true;
            clearScreen();
            break;
        case 'J': // move left
            if (!moveLeft()) {
                displayInvalidMovement();
                goto top_of_switch;
            }
            else addMoves(1);
            if (flag && !didILose()) addPoints(0x05);
            else flag = true;
            clearScreen();
            break;
        case 'L': // move right
            if (!moveRight()) {
                displayInvalidMovement();
                goto top_of_switch;
            }
            else addMoves(1);
            if (flag && !didILose()) addPoints(0x05);
            else flag = true;
            clearScreen();
            break;
        case 'V': // displayVisisbleWorld()
            clearScreen();
            addPoints(-0x02);
            flag = false;
            displayWorld(2);
            goto top_of_switch;
            break;
        case 'C': // displayEntireWorld()
            clearScreen();
            addPoints(-0x05);
            flag = false;
            displayWorld(1);
            goto top_of_switch;
            break;
        case 'R': // reset the game
            state = 0x01;
            break;
        case 'N': // reset the game with new player
            setName();
            state = 0x01;
            break;
        case 'Q':
            state = 0x02;
            break;
        default: // invalid input or error
            print("Invalid input.");
            goto top_of_switch;
            break;
    }
}

void GameWorld::reset() {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: Resets the data within the class GameWorld and randomizes
                  the gameboard for the next iteration of the game. The
                  gameboard contains one Wumpus, one User, one Gold, and
                  5 - 10 Pits all randomly placed on the board.
     */
    
    // initialize game with a random setup
    totalPoints  = 0x00 ;
    totalActions = 0x00 ;
    win          = false;
    lose         = false;
    xLocation    = 0x00 ;
    yLocation    = 0x00 ;
    
    // 1 Gold, 1 Wumpus, 1 User, 5-10 Pits
    // Initialize Board: ' '
    for (int i = 0x00; i < 0x05; i++) {
        for (int j = 0x00; j < 0x05; j++) {
            worldArray[i][j] = ' ';
        }
    }
    
    // Declarations
    int i, x, y;
    const int numPits = (rand() % 0x05) + 0x05;
    char tempArray[0x03 + numPits];
    
    // Initialize Game Piece Array
    // 0 - Wumpus, 1 - User, 2 - Gold, 3+ - Pits
    tempArray[0x00] = 'W'; tempArray[0x01] = 'U'; tempArray[0x02] = 'G';
    for (i = 0x00; i < numPits; i++) {
        tempArray[0x03 + i] = 'P';
    }
    
    // Filling Game Pieces
    for (i = 0x00; i < 0x03 + numPits; i++) {
    new_data_point:
        x = (rand() % 0x05);
        y = (rand() % 0x05);
        if (worldArray[y][x] == ' ') {
            worldArray[y][x] = tempArray[i];
            xLocation = (tempArray[i] == 'U') ? x : xLocation;
            yLocation = (tempArray[i] == 'U') ? y : yLocation;
        }
        else goto new_data_point;
    }
}

void GameWorld::addPoints(int n) {
    totalPoints += n;
}

void GameWorld::addMoves(int n) {
    totalActions += n;
}

void GameWorld::displayWorld(int n) const {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: Displays the gameboard to the terminal screen.
                  An argument 'n' with default condition 0 can be
                  added to change the state of the gameboard. For example,
                  the default condition 0x00 will display the board with
                  only the User's gamepiece visible, n = 0x01 will display the
                  entire board and n = 0x02 will display the visible world.
     */
    
    // Declarations
    struct XY { // xy coordinates
        unsigned int x : 0x04;
        unsigned int y : 0x04;
    } ;
    struct XY xy;
    
    // Start of Code
    cout <<
    "Name: " << name <<
    "\nNumber of Moves: " << totalActions <<
    "\nCurrent Points: " << totalPoints <<
    "\n\n" ;
    
    // Display Board
    switch (n) {
        case 0: // display hidden board
            cout << "_____________________" << endl;
            for (xy.y = 0x00; xy.y < 0x05; xy.y++) {
                for (xy.x = 0x00; xy.x < 0x05; xy.x++) {
                    cout << "| " << ((worldArray[xy.y][xy.x] == 'U') ? "U" : " ") << " ";
                }
                cout << "|" << endl <<
                "_____________________\n" << endl;
            }
            break;
        case 1: // displayEntireWorld()
            cout << "_____________________" << endl;
            for (xy.y = 0x00; xy.y < 0x05; xy.y++) {
                for (xy.x = 0x00; xy.x < 0x05; xy.x++) {
                    cout << "| " << worldArray[xy.y][xy.x] << " ";
                }
                cout << "|" << endl <<
                "_____________________\n" << endl;
            }
            break;
        case 2: // displayVisibleWorld()
            cout << "_____________________" << endl;
            for (xy.y = 0x00; xy.y < 0x05; xy.y++) {
                for (xy.x = 0x00; xy.x < 0x05; xy.x++) {
                    cout << "| " << ((((xy.x - 0x01) == xLocation || (xy.x + 0x01) == xLocation || xy.x == xLocation)
                                      && ((xy.y - 0x01) == yLocation || (xy.y + 0x01) == yLocation || xy.y == yLocation))
                                      ? worldArray[xy.y][xy.x] : ' ') << " ";
                }
                cout << "|" << endl <<
                "_____________________\n" << endl;
            }
        default:
            break;
    }
    
    // Directory
    cout <<
    "I - Move up      |  K - Move down      |  J - Move left  |  L - Move right\n"
    "V - DVW (-2pts)  |  C - Cheat (-5pts)  |  R - Restart    |  N - Restart new player\n"
    "Q - Quit\n"
    << endl;
}

bool GameWorld::moveUp() {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: Updates the gameboard by moving the User's gamepiece
                  up by one space. If the User's gamepiece future position
                  will overlap with another gamepiece, the 'lose' or 'win'
                  variable is updated to indicate the collision.
     */
    
    // if - check bounds, else - execute if within bounds
    if ((yLocation - 0x01) < 0x00) return false;
    else {
        worldArray[yLocation][xLocation]   = ' ';
        switch (worldArray[--yLocation][xLocation]) {
            case ' ':
                worldArray[yLocation][xLocation] = 'U';
                break;
            case 'P':
            case 'W':
                worldArray[yLocation][xLocation] = 'X';
                lose = true;
                break;
            case 'G':
                worldArray[yLocation][xLocation] = '!';
                win = true;
                break;
            default: // should not happen
                cout << "error: " << worldArray[yLocation][xLocation]
                << " was found." << endl;
                break;
        }
    }
    
    return true;
}

bool GameWorld::moveDown() {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: Updates the gameboard by moving the User's gamepiece
                  down by one space. If the User's gamepiece future position
                  will overlap with another gamepiece, the 'lose' or 'win'
                  variable is updated to indicate the collision.
     */
    // if - check bounds, else - execute if within bounds
    if ((yLocation + 0x01) > 0x04) return false;
    else {
        worldArray[yLocation][xLocation] = ' ';
        switch (worldArray[++yLocation][xLocation]) {
            case ' ':
                worldArray[yLocation][xLocation] = 'U';
                break;
            case 'P':
            case 'W':
                worldArray[yLocation][xLocation] = 'X';
                lose = true;
                break;
            case 'G':
                worldArray[yLocation][xLocation] = '!';
                win = true;
                break;
            default:
                cout << "error: " << worldArray[yLocation][xLocation]
                << " was found." << endl;
                break;
        }
    }
    return true;
}

bool GameWorld::moveLeft() {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: Updates the gameboard by moving the User's gamepiece
                  left by one space. If the User's gamepiece future position
                  will overlap with another gamepiece, the 'lose' or 'win'
                  variable is updated to indicate the collision.
     */
    // if - check bounds, else - execute if within bounds
    if ((xLocation - 0x01) < 0x00) return false;
    else {
        worldArray[yLocation][xLocation] = ' ';
        switch (worldArray[yLocation][--xLocation]) {
            case ' ':
                worldArray[yLocation][xLocation] = 'U';
                break;
            case 'P':
            case 'W':
                worldArray[yLocation][xLocation] = 'X';
                lose = true;
                break;
            case 'G':
                worldArray[yLocation][xLocation] = '!';
                win = true;
                break;
            default:
                cout << "error: " << worldArray[yLocation][xLocation]
                << " was found." << endl;
                break;
        }
    }
    return true;
}

bool GameWorld::moveRight() {
    /*
     Name: Kyle Hurd
     Date: 10/09/2020
     Description: Updates the gameboard by moving the User's gamepiece
                  right by one space. If the User's gamepiece future position
                  will overlap with another gamepiece, the 'lose' or 'win'
                  variable is updated to indicate the collision.
     */
    
    // if - check bounds, else - execute if within bounds
    if ((xLocation + 0x01) > 0x04) return false;
    else {
        worldArray[yLocation][xLocation] = ' ';
        switch (worldArray[yLocation][++xLocation]) {
            case ' ':
                worldArray[yLocation][xLocation] = 'U';
                break;
            case 'P':
            case 'W':
                worldArray[yLocation][xLocation] = 'X';
                lose = true;
                break;
            case 'G':
                worldArray[yLocation][xLocation] = '!';
                win = true;
                break;
            default:
                cout << "error: " << worldArray[yLocation][xLocation]
                << " was found." << endl;
                break;
        }
    }
    return true;
}

int GameWorld::getTotalPoints() const {
    return totalPoints;
}

void GameWorld::setTotalPoints(int num = 0x00) {
    totalPoints = num;
}

int GameWorld::getTotalActions() const {
    return totalActions;
}

void GameWorld::setTotalActions(int num = 0x00) {
    totalActions = num;
}

string GameWorld::getName() const {
    return name;
}

void GameWorld::setName() {
    string n;
    cout << "Please enter a UserName [no spaces]: ";
    cin >> name;
}

bool GameWorld::didIWin() const {
    return win;
}

bool GameWorld::didILose() const {
    return lose;
}

ostream &operator<< (ostream &output, const GameWorld &G) {
    output <<
    "Player: " << G.getName() << endl <<
    "Total Actions: " << G.getTotalActions() << endl <<
    "Total Points: " << G.getTotalPoints() << endl <<
    "Final Status: " << ((G.didIWin() == true) ? "Win" : "Lose") << endl << endl <<
    "**************************" << endl;
    return output;
}
