#ifndef POKER_H_INCLUDED
#define POKER_H_INCLUDED

typedef struct {
    int Suits;    // 0=club, 1=diamond, 2=heart, 3=spade
    int Numbers;  // 1~13
} Poker;


void Poker_Init(Poker* p);
void Poker_Init2(Poker* p, int suit, int number);


void  Poker_SetSuits(Poker* p, int suit);
void  Poker_SetNumbers(Poker* p, int number);

int   Poker_GetSuits(const Poker* p);
int   Poker_GetNumbers(const Poker* p);

#endif
