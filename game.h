#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdbool.h>
#include "poker.h"
#include "player.h"


void Game_Init(void);


void  Game_shuffle(void);
Poker Game_deal(void);


void Game_PushSea(Poker poker);
void Game_ShowSea(int x, int y);

// 遊戲規則
bool Game_check(Player* player);
bool Game_match(Player* player, int chooseHand, int chooseSea);

// 計分
void Game_AddPoint(Player* player, Poker card);

#endif
