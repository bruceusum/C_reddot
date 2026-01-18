#include <stdio.h>
#include <windows.h>
#include "display.h"
#include "game.h"

#define Club 0
#define Diamond 1
#define Heart 2
#define Spade 3

static const char SpaceCard[9][14] = {
    "-------------",
    "|           |",
    "|           |",
    "|           |",
    "|           |",
    "|           |",
    "|           |",
    "|           |",
    "-------------",
};


static const char Suits[4][7][12] = {
    { "     *   梅",
      "    ***    ",
      "  *  *  *  ",
      " ********* ",
      "  ** * **  ",
      "     *     ",
      "梅 *****   ", },
    { "     *   方",
      "    ***    ",
      "  *******  ",
      " ********* ",
      "  *******  ",
      "    ***    ",
      "方   *     ", },
    { "         心",
      "  *** ***  ",
      " ********* ",
      " ********* ",
      "   *****   ",
      "     *     ",
      "心         ", },
    { "    ***  桃",
      "   *****   ",
      "  *******  ",
      " ********* ",
      "  ** * **  ",
      "     *     ",
      "桃 *****   ", },
};



void Display_gotoxy(int x, int y)
{
    COORD point;
    point.X = x;
    point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void Display_SetColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Display_ShowCard(int x, int y, const Poker card)
{
    int suit = Poker_GetSuits(&card);
    int number = Poker_GetNumbers(&card);

    Display_SetColor(7);  //預設白色

    //清空區域
    for (int i = 0; i < 9; i++) {
        Display_gotoxy(x, y + i);
        printf("%s", SpaceCard[i]);
    }


    if (suit == Diamond || suit == Heart)
        Display_SetColor(12);

    //花色圖案
    for (int i = 0; i < 7; i++) {
        Display_gotoxy(x + 1, y + i + 1);
        printf("%s", Suits[suit][i]);
    }

    //數字
    for (int i = 0; i < 2; i++) {
        Display_gotoxy(x + 2 + i * 8, y + 1 + i * 6);

        if (number == 1)
            printf("A");
        else if (number == 11)
            printf("J");
        else if (number == 12)
            printf("Q");
        else if (number == 13)
            printf("K");
        else
            printf("%d", number);
    }
}

void Display_InGameUI(const Player* player)
{
    Display_gotoxy(0, 1);
    printf("海底: \n");
    Game_ShowSea(0, 2);

    Display_gotoxy(0, 13);
    printf("本回合玩家: Player%d  目前分數: %d\n",
        Player_GetID(player),
        Player_GetPoint(player));

    Player_ShowHand(player, 0, 15);
}
