#include "../include/llqueue.h"
#include "../include/player.h"
#include "../include/futsal.h"
#include <string>

int main() {
    // This code should run without errors after you've implemented all the functions.
    // Feel free to modify this main function to help you do your assignment
    // the main function will not be checked by the autograder in HW 3

    Queue *q = newQueue();
    printPlayer(queueFront(q));
    queuePushPlayerEntry(q, newPlayer("A", 5));
    queuePushPlayerEntry(q, newPlayer("B", 10));
    queuePushPlayerEntry(q, newPlayer("C", 3));
    queuePushPlayerEntry(q, newPlayer("D", 4));
    queuePushPlayerEntry(q, newPlayer("E", 2));
    queuePushPlayerEntry(q, newPlayer("F", 7));
    queuePushPlayerEntry(q, newPlayer("G", 1));

    printQueue(q);

    Queue *welcome_q = newQueue();
    teamCreateFromBest(q, welcome_q, 3);
    
    // printQueue(welcome_q);

    deleteQueue(q);
    deleteQueue(welcome_q);
}