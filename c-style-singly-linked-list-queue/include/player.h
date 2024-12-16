#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

struct Player {
    std::string name;
    int num_goals;
};
// Allocate a new player record
Player *newPlayer(std::string name, int num_goals);

// Allocate a copy of the player record
Player *copyPlayer(const Player *p);

// Deallocate a player record
void deletePlayer(Player *p);

// Print player record
void printPlayer(const Player *p);

#endif