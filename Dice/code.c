/**
 * 项    目: 骰子大作战
 * 时    间: 20200213 14:27
 * 编 写 人: 王斯迪
 */

#include "../main.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

extern player_info player;
extern short dice_point;
extern short opt_num;
extern short who_win;
extern short count_01;
extern short count_02;

//绘制地图
void draw_map(void)
{
    for (int x = 0; x <= MAP_LEN_WIDTH + 2; x += 2)
    {
        cursor_pos(x, 0);
        printf("□");
        cursor_pos(x, MAP_LEN_HEIGHT + 1);
        printf("□");
    }
    for (int y = 1; y <= MAP_LEN_HEIGHT; y++)
    {
        cursor_pos(0, y);
        printf("□");
        cursor_pos(MAP_LEN_WIDTH + 2, y);
        printf("□");
    }

    return;
}

//玩家移动
void move_player(int x_01, int y_01, int x_02, int y_02)
{
    if (!player.is_have_gun_01)
    {
        cursor_pos(x_01, y_01);
        printf("%c", PLAYER_IMAG_01);
    }
    else
    {
        cursor_pos(x_01, y_01);
        printf("%c%c", PLAYER_IMAG_01, GUN_IMAG);
    }

    if (!player.is_have_gun_02)
    {
        cursor_pos(x_02, y_02);
        printf("%c", PLAYER_IMAG_02);
    }
    else
    {
        cursor_pos(x_02, y_02);
        printf("%c%c", PLAYER_IMAG_02, GUN_IMAG);
    }

    return;
}

//清空身后
void clear_player(int x_01, int y_01, int x_02, int y_02)
{
    if (!player.is_have_gun_01)
    {
        cursor_pos(x_01, y_01);
        printf("%c", ' ');
    }
    else
    {
        cursor_pos(x_01, y_01);
        printf("%c%c", ' ', ' ');
    }

    if (!player.is_have_gun_02)
    {
        cursor_pos(x_02, y_02);
        printf("%c", ' ');
    }
    else
    {
        cursor_pos(x_02, y_02);
        printf("%c%c", ' ', ' ');
    }

    return;
}

//初始化玩家
void init_player(void)
{
    //(2,1)
    player.pos_x_01 = PLAYER_INIT_POS_X_01;
    player.pos_y_01 = PLAYER_INIT_POS_Y_01;

    //(101,28)
    player.pos_x_02 = PLAYER_INIT_POS_X_02;
    player.pos_y_02 = PLAYER_INIT_POS_Y_02;

    move_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);

    player.is_have_gun_01=false;
    player.is_have_gun_02=false;
    player.state = true;

    return;
}

//初始化武器
void init_gun(void)
{
    //(52,14)
    cursor_pos(GUN_POS_X, GUN_POS_Y);
    printf("%c", GUN_IMAG);

    return;
}

//游戏提示
void info_message(void)
{
    cursor_pos(INFO_POS_X, INFO_POS_Y);
    printf("%d : %d", count_01, count_02);

    cursor_pos(INFO_POS_X, INFO_POS_Y + 2);
    if (player.state)
        INFO(1);
    else
        INFO(2);

    cursor_pos(INFO_POS_X, INFO_POS_Y + 4);
    printf("抛出点数: %d", dice_point);

    cursor_pos(INFO_POS_X, INFO_POS_Y + 5);
    printf("你有%d次操作", opt_num);

    cursor_pos(INFO_POS_X, INFO_POS_Y + 7);
    puts("死亡条件:");

    cursor_pos(INFO_POS_X, INFO_POS_Y + 8);
    puts("1.碰到持有武");
    cursor_pos(INFO_POS_X, INFO_POS_Y + 9);
    puts("器玩家武器");

    cursor_pos(INFO_POS_X, INFO_POS_Y + 11);
    puts("2.在其它玩家");
    cursor_pos(INFO_POS_X, INFO_POS_Y + 12);
    puts("回合被碰到");

    cursor_pos(INFO_POS_X, INFO_POS_Y + 14);
    puts("胜利条件:");

    cursor_pos(INFO_POS_X, INFO_POS_Y + 15);
    puts("击杀玩家得1,");
    cursor_pos(INFO_POS_X, INFO_POS_Y + 16);
    puts("优先得10获胜");

    return;
}

//抛骰子
void put_dice(void)
{
    srand(time(NULL));
    dice_point = rand() % 6 + 1;
    opt_num = dice_point;

    return;
}

//玩家按键
void key_player(void)
{
    int key;
    while (opt_num > 0)
    {
        key = getch();
        switch (key)
        {
        case 'w':
            clear_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            player.state == 1 ? player.pos_y_01-- : player.pos_y_02--;
            move_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            opt_num--;
            break;
        case 's':
            clear_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            player.state == 1 ? player.pos_y_01++ : player.pos_y_02++;
            move_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            opt_num--;
            break;
        case 'd':
            clear_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            player.state == 1 ? player.pos_x_01++ : player.pos_x_02++;
            move_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);

            opt_num--;
            break;
        case 'a':
            clear_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            player.state == 1 ? player.pos_x_01-- : player.pos_x_02--;
            move_player(player.pos_x_01, player.pos_y_01, player.pos_x_02, player.pos_y_02);
            opt_num--;
            break;
        default:
            opt_num--;
            break;
        }
        eat_player();
        got_gun();
        cursor_pos(INFO_POS_X, INFO_POS_Y + 5);
        printf("你有%d次操作", opt_num);
    }
}

//玩家撞墙
void hurt_wall(int x, int y)
{
    if (x >= MAP_LEN_WIDTH + 2 || x <= 1 || y >= MAP_LEN_HEIGHT + 1 || y <= 0)
    {
        if (player.state)
            who_win = 2;
        else
            who_win = 1;
    }

    return;
}

//玩家吃
void eat_player(void)
{
    if (player.is_have_gun_01)
    {
        if (player.pos_x_01 + 1 == player.pos_x_02 && player.pos_y_01 == player.pos_y_02)
            who_win = 1;
    }

    if (player.is_have_gun_02)
    {
        if (player.pos_x_01 == player.pos_x_02 + 1 && player.pos_y_01 == player.pos_y_02)
            who_win = 2;
    }
    
    if (player.pos_x_01 == player.pos_x_02 && player.pos_y_01 == player.pos_y_02)
        who_win = player.state == true ? 1 : 2;

    return;
}

//获得武器
void got_gun(void)
{
    if (player.pos_x_01 == GUN_POS_X && player.pos_y_01 == GUN_POS_Y)
        player.is_have_gun_01 = true;

    if (player.pos_x_02 == GUN_POS_X && player.pos_y_02 == GUN_POS_Y)
        player.is_have_gun_02 = true;

    return;
}