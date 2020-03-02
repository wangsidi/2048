/**
 * 项    目: 骰子大作战
 * 时    间: 20200213 14:27
 * 编 写 人: 王斯迪
 */

#include "../main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern player_info player;
extern short who_win;
extern short count_01;
extern short count_02;

//进入页面
void _home(void)
{
    cursor_isvisible(false);
    SetConsoleTitle(GAME_NAME);
    cursor_pos(50, 14);
    puts(GAME_NAME);
    getchar();
    system("cls");
}

//开始
void _start(void)
{
    draw_map();
    init_player();
    init_gun();

    return;
}

//游戏
void _game(void)
{
    while (count_01 != WIN_CASE && count_02 !=WIN_CASE)
    {
        put_dice();
        info_message();
        key_player();
        player.state == true ? hurt_wall(player.pos_x_01, player.pos_y_01) : hurt_wall(player.pos_x_02, player.pos_y_02);
        if (who_win)
        {
            who_win == 1 ? count_01++ : count_02++;
            who_win = 0;
            system("cls");
            _start();
        }
        player.state = !player.state;
    }
    return;
}

//结束
void _end(void)
{
    system("cls");
    cursor_pos(50, 14);
    count_01 == 10 ? WIN(1) : WIN(2);

    return;
}