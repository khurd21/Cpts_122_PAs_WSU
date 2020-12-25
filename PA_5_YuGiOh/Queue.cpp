//
//  Queue.cpp
//  Yugioh
//
//  Created by Kyle Hurd on 10/19/20.
//

#include "Queue.hpp"

// Initializer
Queue::Queue() {
    front    = nullptr;
    rear     = nullptr;
    
    numItems = 0x00;
}

// Operations
void Queue::enqueue(Monster M) {
    
    // Declaring Variables
    QueueNode *newNode = nullptr;
    newNode = new QueueNode;
    
    newNode->data = M;
    newNode->next = nullptr;
    
    // Adding to Queue
    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    numItems++;
}

void Queue::dequeue(Monster &M) {
    
    // Declaring Variables
    QueueNode *temp = nullptr;
    
    // Dequeuing
    if (isEmpty()) print("The list is empty.");
    else {
        M = front->data;
        temp = front;
        front = front->next;
        delete temp;
        numItems--;
    }
}

bool Queue::isEmpty() const {
    return (0x01 * (numItems <= 0x00));
}

void Queue::clear() {
    
    // Declare Variables
    QueueNode *temp = nullptr;
    
    // Clearing Items in Queue
loop:
    if (isEmpty()) {
        print("Queue has been cleared.");
        return;
    }
    else {
        temp = front;
        front = front->next;
        delete temp;
        numItems--;
    }
    goto loop;
}

int Queue::getNumItems() const {
    return numItems;
}

ostream &operator<< (ostream &output, const Queue &Q) {
    
    cout << Q.getNumItems();
    return output;
}
