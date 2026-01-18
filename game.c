#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "display.h"

// 未使用牌
static Poker* deck = NULL;
static int deck_count = 0;

// 海底
static Poker* sea = NULL;
static int sea_count = 0;

void Game_AddPoint(Player* player, Poker card)
{
    int suit = Poker_GetSuits(&card);
    int num = Poker_GetNumbers(&card);

    if (suit == 1 || suit == 2) {
        if (num > 9)
            player->Point += 10;
        else if (num == 1)
            player->Point += 20;
        else
            player->Point += num;
    }

    if (suit == 3 && num == 1)
        player->Point += 10;
}

void Game_Init(void)
{
    deck_count = 52;
    deck = (Poker*)malloc(sizeof(Poker) * deck_count);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Poker_SetSuits(&deck[i * 13 + j], i);
            Poker_SetNumbers(&deck[i * 13 + j], j + 1);
        }
    }

    Game_shuffle();

    sea = NULL;
    sea_count = 0;

    for (int i = 0; i < 4; i++) {
        Game_PushSea(Game_deal());
    }
}

void Game_shuffle(void)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < deck_count; i++) {
        int r = rand() % deck_count;
        Poker temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

Poker Game_deal(void)
{
    Poker card = deck[deck_count - 1];
    deck_count--;
    return card;
}

void Game_PushSea(Poker poker)
{
    sea = (Poker*)realloc(sea, sizeof(Poker) * (sea_count + 1));
    sea[sea_count++] = poker;
}

void Game_ShowSea(int x, int y)
{
    for (int i = 0; i < sea_count; i++) {
        Display_ShowCard(x + i * 14, y, sea[i]);
        Display_SetColor(7);
        Display_gotoxy(x + i * 14, y + 9);
        printf("第%d張", i + 1);
    }
}

bool Game_check(Player* player)
{
    for (int i = 0; i < Player_HowManyHands(player); i++) {
        for (int j = 0; j < sea_count; j++) {
            int h = Poker_GetNumbers(Player_GetHand(player, i));
            int s = Poker_GetNumbers(&sea[j]);

            if ((h >= 10 && h == s) || (h + s == 10))
                return true;
        }
    }
    return false;
}

bool Game_match(Player* player, int chooseHand, int chooseSea)
{
    Poker hand = *Player_GetHand(player, chooseHand);
    Poker seaCard = sea[chooseSea];

    int h = Poker_GetNumbers(&hand);
    int s = Poker_GetNumbers(&seaCard);

    if ((h >= 10 && h == s) || (h + s == 10)) {

        Game_AddPoint(player, hand);
        Game_AddPoint(player, seaCard);

        Player_Play(player, chooseHand);

        for (int i = chooseSea; i < sea_count - 1; i++) {
            sea[i] = sea[i + 1];
        }
        sea_count--;

        return true;
    }

    printf("配對失敗，請重新出牌");
    return false;
}
