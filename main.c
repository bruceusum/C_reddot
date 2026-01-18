#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "display.h"
#include "poker.h"
#include "game.h"
#include "player.h"

int main(void)
{

    int HowManyPlayer = 0;

    Display_gotoxy(54, 8);
    printf("撿紅點遊戲");
    Display_gotoxy(38, 14);
    printf("(建議將視窗放大再開始遊戲，否則牌面可能跑掉)");

    while (HowManyPlayer > 4 || HowManyPlayer < 2) {
        Display_gotoxy(50, 10);
        printf("玩家數量(2至4人):");
        scanf("%d", &HowManyPlayer);

        if (HowManyPlayer > 4 || HowManyPlayer < 2) {
            Display_gotoxy(50, 12);
            printf("人數錯誤，請重新輸入");
        }
    }

    Player* player = (Player*)malloc(sizeof(Player) * HowManyPlayer);
    for (int i = 0; i < HowManyPlayer; i++) {
        Player_Init(&player[i]);
    }
    Game_Init();
    system("cls");

    for (int i = 0; i < HowManyPlayer; i++) {
        for (int j = 0; j < 24 / HowManyPlayer; j++) {
            Player_Draw(&player[i]);
        }
        printf("\n");
    }

    int GameOver = 0;

    while (GameOver != HowManyPlayer) {
        for (int i = 0; i < HowManyPlayer; i++) {
            system("cls");
            Display_InGameUI(&player[i]);

            if (Game_check(&player[i])) {
                int ChooseHand, ChooseSea;
                do {
                    Display_gotoxy(0, 26);
                    printf("選擇手牌：");
                    scanf("%d", &ChooseHand);
                    printf("選擇海底：");
                    scanf("%d", &ChooseSea);
                } while (!Game_match(&player[i], ChooseHand - 1, ChooseSea - 1));
            }
            else {
                int Choose;
                Display_gotoxy(0, 26);
                printf("沒牌可出，請將一張手牌放入海底：");
                scanf("%d", &Choose);

                Game_PushSea(*Player_GetHand(&player[i], Choose - 1));
                Player_Play(&player[i], Choose - 1);
            }

            if (Player_IfNoCards(&player[i])) {
                GameOver++;
            }
        }
    }
    
    // 玩家依分數排序
    for (int i = 0; i < HowManyPlayer; i++) {
        for (int j = i + 1; j < HowManyPlayer; j++) {
            if (Player_GetPoint(&player[i]) < Player_GetPoint(&player[j])) {
                Player temp = player[i];
                player[i] = player[j];
                player[j] = temp;
            }
        }
    }

    system("cls");

    int ranking = 1;
    for (int i = 0; i < HowManyPlayer; i++) {
        Display_gotoxy(50, 4 + i * 2);

        if (i > 0 &&
            Player_GetPoint(&player[i]) == Player_GetPoint(&player[i - 1])) {
            ranking--;
        }

        printf("第 %d 名 player%d  %d分",
            ranking,
            Player_GetID(&player[i]),
            Player_GetPoint(&player[i]));

        ranking++;
    }

    printf("\n\n遊戲即將結束...");
    Sleep(10000);

    for (int i = 0; i < HowManyPlayer; i++) {
        Player_Destroy(&player[i]);
    }
    free(player);
    return 0;
}
