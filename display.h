#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "poker.h"
#include "player.h"


void Display_gotoxy(int x, int y);


void Display_SetColor(int color);

//≈„•‹•dµP
void Display_ShowCard(int x, int y, const Poker card);


void Display_InGameUI(const Player* player);

#endif
