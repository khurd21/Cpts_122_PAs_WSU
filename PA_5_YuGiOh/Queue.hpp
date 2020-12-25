//
//  Queue.hpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/19/20.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include "functions.hpp"
#include "Deck.hpp"

class Queue {
private:
    
    struct QueueNode {
        Monster     data;
        QueueNode   *next;
    };
    
    QueueNode   *front;
    QueueNode   *rear;
    
    int         numItems;
    
public:
    // Constructors
    Queue();
    
    // Destructors
    ~Queue() {};
    
    // Operations
    void    enqueue(Monster);
    void    dequeue(Monster &);
    bool    isEmpty() const;
    void    clear();
    
    // Getters
    int     getNumItems() const;
    
    friend class PlayerData;
    friend ostream &operator<< (ostream &, const Queue &);
};

#endif /* Queue_hpp */
