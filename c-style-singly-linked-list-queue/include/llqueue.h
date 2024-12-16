#ifndef LLQUEUE_H
#define LLQUEUE_H

#include "player.h"

struct LLNode {
    LLNode* next;
    Player* entry;
};

// Allocate a new LLNode
LLNode *newLLNode(Player *p);

void deleteLLNode(LLNode *lln);

struct Queue {
    std::size_t size;
    LLNode *head; 
    LLNode *tail; 
};

Queue *newQueue();

void queuePushPlayerEntry(Queue *q, Player *entry);

void queuePopPlayerEntry(Queue *q);

// front function
Player *queueFront(Queue *q);

// back function
Player *queueBack(Queue *q);

// size function
std::size_t queueSize(const Queue *q);

// print out the queue players in order
void printQueue(const Queue *q);

// deleteQueue only deletes the LLNodes it is the caller's responsibility to delete the players contained within!
void deleteQueue(Queue *q);

#endif