#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdbool.h>
#include "poker.h"

extern int Player_HowManyPlayers;

typedef struct {
    int ID;
    bool NoCards;
    int Point;

    Poker* hand;
    int hand_count;
    int hand_capacity;
} Player;

void Player_Init(Player* p);


int  Player_GetID(const Player* p);
bool Player_IfNoCards(Player* p);
int  Player_GetPoint(const Player* p);

void Player_Draw(Player* p);
void Player_Play(Player* p, int index);

Poker* Player_GetHand(const Player* p, int index);
int   Player_HowManyHands(const Player* p);

void Player_ShowHand(const Player* p, int x, int y);


void Player_Destroy(Player* p);

#endif
