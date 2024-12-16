#include "../include/player.h"
#include <iostream>

Player *newPlayer(std::string name, int num_goals)
{
    return new Player{name, num_goals};
}

Player *copyPlayer(const Player *p)
{
    if (p)
    {
        return new Player{p->name, p->num_goals};
    }
    return NULL;
}

void deletePlayer(Player *p)
{
    if (p)
        delete p;
}

void printPlayer(const Player *p)
{
    if (p)
    {
        std::cout << "Player name: " << p->name << std::endl
                  << "Total goals: " << p->num_goals << std::endl;
    }
    else
    {
        std::cout << "No player found!" << std::endl;
    }
}