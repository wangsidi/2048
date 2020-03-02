/**
 * 项    目: 消灭怪兽
 * 时    间: 20200212 17:11
 * 编 写 人: 王斯迪
 */

/**
 * 项    目: 消灭怪兽
 * 时    间: 20200213 9:45 (更新)
 * 编 写 人: 王斯迪
 */


#include "../main.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern node_player player;
extern enemy ENEMY(1);

//开始
void _start(void)
{
    cursor_visible(false);

    for (int i = 3; i >= 0; i--)
    {
        if (i != 0)
        {
            cursor_pos(55, 14);
            printf("%d", i);
        }
        else
        {
            cursor_pos(52, 14);
            printf("游戏开始");
        }
        Sleep(1000);
    }
    system("cls");

    return;
}

//游戏
void _game(void)
{
    draw_map();

    init_player(PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y);

    init_enemy(&ENEMY(1));
    create_enemy(&ENEMY(1));

    while (player.hp > 0)
    {
        create_enemy(&ENEMY(1));
        hurt_player();
        game_info();
        control_player();
        anim_snip();
        Sleep(PLAYER_WAIT_STATE_SPEED);
    }

    system("cls");

    return;
}

//结束
void _end(void)
{
    cursor_pos(50, 14);
    printf("YOU DIE!");
    getchar();

    cursor_pos(50, 14);
    printf("游戏结束!");

    getchar();

    return;
}