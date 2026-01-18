#include "poker.h"

void Poker_Init(Poker* p)
{
    p->Suits = 4;
    p->Numbers = 0;
}


void Poker_Init2(Poker* p, int suit, int number)
{
    p->Suits = suit;
    p->Numbers = number;
}

void Poker_SetSuits(Poker* p, int suit)
{
    p->Suits = suit;
}

void Poker_SetNumbers(Poker* p, int number)
{
    p->Numbers = number;
}

int Poker_GetSuits(const Poker* p)
{
    return p->Suits;
}

int Poker_GetNumbers(const Poker* p)
{
    return p->Numbers;
}
