#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "game.h"
#include "display.h"


int Player_HowManyPlayers = 0;

void Player_Init(Player* p)
{
    Player_HowManyPlayers++;
    p->ID = Player_HowManyPlayers;
    p->NoCards = false;
    p->Point = 0;

    p->hand_capacity = 8;
    p->hand_count = 0;
    p->hand = (Poker*)malloc(sizeof(Poker) * p->hand_capacity);
}

int Player_GetID(const Player* p)
{
    return p->ID;
}

bool Player_IfNoCards(Player* p)
{
    if (p->hand_count == 0)
        p->NoCards = true;
    return p->NoCards;
}

int Player_GetPoint(const Player* p)
{
    return p->Point;
}

void Player_Draw(Player* p)
{
    if (p->hand_count >= p->hand_capacity) {
        p->hand_capacity *= 2;
        p->hand = (Poker*)realloc(
            p->hand, sizeof(Poker) * p->hand_capacity);
    }

    p->hand[p->hand_count++] = Game_deal();
}

void Player_Play(Player* p, int index)
{
    if (index < 0 || index >= p->hand_count)
        return;

    for (int i = index; i < p->hand_count - 1; i++) {
        p->hand[i] = p->hand[i + 1];
    }
    p->hand_count--;
}

Poker* Player_GetHand(const Player* p, int index)
{
    return &p->hand[index];
}

int Player_HowManyHands(const Player* p)
{
    return p->hand_count;
}

void Player_ShowHand(const Player* p, int x, int y)
{
    for (int i = 0; i < p->hand_count; i++) {
        Display_ShowCard(x + i * 14, y, p->hand[i]);
        Display_SetColor(7);
        Display_gotoxy(x + i * 14, y + 9);
        printf("²Ä%d±i", i + 1);
    }
}

void Player_Destroy(Player* p)
{
    free(p->hand);
    p->hand = NULL;
}
