//
//  Deck.cpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/12/20.
//

#include "Deck.hpp"

// Initializer
Deck::Deck() {
    top      = nullptr;
    numItems = 0x00;
}

// Destructor
Deck::~Deck() {

}

void Deck::clear() {
    
    Monster M;
    
    while (!isEmpty()) {
        pop(M);
    }
}

// Instructions
void Deck::setDeck(fstream &infile, int player) {
    
    string  u;
    int     n;
    
get_input:
    cout << "Player " << player << endl;
    print("Would you like to create your own deck [1] or use the default deck [2]?");
    getUserInput(u);
    switch (u[0]) {
        case '1': // create new deck with custom cards.
            n = initNewDeck();
            initDeck(infile, n);
            break;
        case '2': // default deck
            initDeck(infile, 0x00);
            break;
        default:
            goto get_input;
            break;
    }
}

void Deck::initDeck(fstream &file, int j) {
    
    // Declarations
    Monster M;
    string line, token;
    int i;
    
    // Start of Code
    if (file.good()) {
    top:
        while (getline(file, line) && j < 0x1E) {
            i = 0x00;
            stringstream s(line);
            
            while (getline(s, token, ',') && i <= 0x06) {
                switch (i++) {
                    case 0x00:
                        if (token == "Name") goto top;
                        M.name = token;
                        break;
                    case 0x01:
                        M.type = token;
                        break;
                    case 0x02:
                        M.level = stoi(token);
                        break;
                    case 0x03:
                        M.race = token;
                        break;
                    case 0x04:
                        M.attribute = token;
                        break;
                    case 0x05:
                        M.attackPoints = stoi(token);
                        break;
                    case 0x06:
                        M.defensePoints = stoi(token);
                        break;
                    default: // should not happen
                        print("Default case statement in initDeck() accessed.");
                        break;
                }
            }
            // push Type<Monster> to the Deck
            j++;
            push(M);
        }
        if (file.eof()) {
            file.clear();
            file.seekg(0x00, ios::beg);
            goto top;
        }
    }
}

int Deck::initNewDeck() {
    /*
     
     */
    Monster M;
    string n;
    int i, num, bounds;
    
get_input:
    print("How many cards would you like to create?\n"
          "The rest will be filled from the predetermined deck. [0-30]");
    cin >> bounds;
    getchar();
    if (bounds > 0x1E || bounds < 0x00) goto get_input;
    
    for (i = 0x00; i < bounds; i++) {
        clearScreen();
    monster:
        cout << "Enter the name of Monster: " ;
        getline(cin, n);
        if (n.find(',') < n.length()) {
            print("No commas."); goto monster;
        }
        else M.name = n;
    type:
        cout << "Enter the type of Monster: " ;
        getline(cin, n);
        if (n.find(',') < n.length()) {
            print("No commas."); goto type;
        }
        else M.type = n;
    level:
        cout << "Enter the level of Monster [int]: " ;
        cin  >> num;
        getchar();
        if (num < 0x00) {
            print("Value must be positive.");
            goto level;
        }
        else M.level = num;
    race:
        cout << "Enter the race of Monster: " ;
        getline(cin, n);
        if (n.find(',') < n.length()) {
            print("No commas."); goto race;
        }
        else M.race = n;
    attribute:
        cout << "Enter the attribute of Monster: " ;
        getline(cin, n);
        if (n.find(',') < n.length())  {
            print("No commas."); goto attribute;
        }
        else M.attribute = n;
    atk:
        cout << "Enter the ATK of Monster [int]: " ;
        cin  >> num;
        getchar();
        if (num < 0x00) {
            print("Value must be positive.");
            goto atk;
        }
        else M.attackPoints = num;
    def:
        cout << "Enter the DEF of Monster [int]: " ;
        cin  >> num;
        getchar();
        if (num < 0x00) {
            print("Value must be positive.");
            goto def;
        }
        else M.defensePoints = num;
        push(M);
    }
    
    return bounds;
}

bool Deck::isEmpty() {
    return !top;
}

void Deck::push(Monster card) {
    
    Node *newNode = nullptr;
    newNode = new Node;
    newNode->cardData = card;
    numItems++;
    
    if (isEmpty()) { // add node to top
        top = newNode;
        newNode->next = nullptr;
    }
    else { // push
        newNode->next = top;
        top = newNode;
    }
}

void Deck::pop(Monster &card) {
    
    Node *temp = nullptr;
    
    if (!isEmpty()) {
        card = top->cardData;
        temp = top->next;
        delete top;
        top = temp;
        numItems--;
    }
    else print("Deck is empty.");
}

ostream &operator<< (ostream &output, const Deck &G) {
    
    Deck::Node *temp = G.top;
    Monster cd;
    int i = 0x00;
    
    while (temp != nullptr) {
        i++;
        cd = temp->cardData;
        output <<
        i           << "."              << endl <<
        "Name:  "   << cd.name          << endl <<
        "Level: "   << cd.level         << endl <<
        "ATK:   "   << cd.attackPoints  << endl <<
        "DEF:   "   << cd.defensePoints << endl <<
        "***********************"       << endl << endl;
        temp = temp->next;
    }
    return output;
}

ostream &operator<< (ostream &output, const Monster &M) {
    
    output <<
    "Name:  " << M.name  << endl <<
    "Level: " << M.level << endl <<
    "Type:  " << M.type  << endl <<
    "ATK:   " << M.attackPoints  << endl <<
    "DEF:   " << M.defensePoints << endl <<
    "************************"   << endl << endl;
    return output;
}
