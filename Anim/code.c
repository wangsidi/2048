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
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

extern node_player player;
extern char key;
extern int left_or_right;
extern enemy ENEMY(1);
extern int score;
extern int high_score;

//玩家状态1
char player_image_st1[PLAYER_HEIGHT][PLAYER_WIDTH] = {
    "      ******       ",
    "   *          *    ",
    "--*   O    O   *-- ",
    "  *            *   ",
    "   *          *    ",
    "      ******       ",
};
//玩家状态2
char player_image_st2[PLAYER_HEIGHT][PLAYER_WIDTH] = {
    "      ******       ",
    "   *          *    ",
    " \\*   O    O   */  ",
    "  *            *   ",
    "   *          *    ",
    "      ******       ",
};
//玩家状态3
char player_image_st3[PLAYER_HEIGHT][PLAYER_WIDTH] = {
    "      ******       ",
    "   *          *    ",
    "--*   O    O   *-- ",
    "  *            *   ",
    "   *          *    ",
    "      ******       ",
};
//玩家状态4
char player_image_st4[PLAYER_HEIGHT][PLAYER_WIDTH] = {
    "      ******       ",
    "   *          *    ",
    "  *   O    O   *   ",
    " /*            * \\",
    "   *          *    ",
    "      ******       ",
};

//光标是否可见
void cursor_visible(bool is_true)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    //获取光标信息
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(out, &info);
    //设置光标信息
    info.bVisible = is_true;
    SetConsoleCursorInfo(out, &info);

    return;
}

//光标位置
void cursor_pos(int x, int y)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    //设置光标位置
    COORD pos = {x, y};
    SetConsoleCursorPosition(out, pos);

    return;
}

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

//绘制玩家
void draw_player(const char player_image[][PLAYER_WIDTH], int rows)
{
    int temp_x = player.pos_x;
    int temp_y = player.pos_y;

    for (int i = 0; i < rows; ++i)
    {
        cursor_pos(temp_x, temp_y);
        puts(player_image[i]);
        temp_y++;
    }

    return;
}

//初始化玩家
void init_player(int x, int y)
{
    player.pos_x = x;
    player.pos_y = y;
    player.state = 1;
    player.hp = 100.0f;

    return;
}

//玩家动态片段
void anim_snip(void)
{
    switch (player.state)
    {
    case 1:
        draw_player(player_image_st1, PLAYER_HEIGHT);
        player.state++;
        break;
    case 2:
        draw_player(player_image_st2, PLAYER_HEIGHT);
        player.state++;
        break;
    case 3:
        draw_player(player_image_st3, PLAYER_HEIGHT);
        player.state++;
        break;
    case 4:
        draw_player(player_image_st4, PLAYER_HEIGHT);
        player.state = 1;
        break;
    }

    return;
}

//玩家移动
void control_player(void)
{
    key = '\0';
    if (kbhit())
    {
        key = getch();
        switch (key)
        {
        case 'd':
            //边界限制
            if (player.pos_x + PLAYER_WIDTH >= MAP_LEN_WIDTH + 2)
                break;
            left_or_right = 1;
            player.pos_x++;
            //清除身后
            for (int j = 0; j < PLAYER_HEIGHT; j++)
            {
                cursor_pos(player.pos_x - 1, player.pos_y + j);
                printf("%c", '\0');
            }
            break;
        case 'a':
            //边界限制
            if (player.pos_x <= 2)
                break;
            left_or_right = -1;
            player.pos_x--;
            //清除身后
            for (int j = 0; j < PLAYER_HEIGHT; j++)
            {
                cursor_pos(player.pos_x + PLAYER_WIDTH, player.pos_y + j);
                printf("%c", '\0');
            }
            break;
        case 'w':
            //边界限制
            if (player.pos_y <= 1)
                break;
            player.pos_y--;
            //清除身后
            for (int i = 0; i < PLAYER_WIDTH; i++)
            {
                cursor_pos(player.pos_x + i, player.pos_y + PLAYER_HEIGHT);
                printf("%c", '\0');
            }
            break;
        case 's':
            //边界限制
            if (player.pos_y + PLAYER_HEIGHT >= MAP_LEN_HEIGHT + 1)
                break;
            player.pos_y++;
            //清除身后
            for (int i = 0; i < PLAYER_WIDTH; i++)
            {
                cursor_pos(player.pos_x + i, player.pos_y - 1);
                printf("%c", '\0');
            }
            break;
        case 'j':
            if (fly_ball())
                init_enemy(&ENEMY(1));
            break;
        default:
            break;
        }
        fflush(stdout);
    }

    return;
}

//球飞行 返回是否射中敌人
bool fly_ball(void)
{
    node_ball *ball = (node_ball *)malloc(sizeof(node_ball));

    ball->pos_x = left_or_right == 1 ? player.pos_x + PLAYER_WIDTH + 1 : player.pos_x - 1;
    ball->pos_y = player.pos_y + PLAYER_HEIGHT / 2 - 1;

    cursor_pos(ball->pos_x, ball->pos_y);
    while (ball->pos_x > 2 && ball->pos_x < MAP_LEN_WIDTH + 2)
    {
        printf("o");
        cursor_pos(ball->pos_x, ball->pos_y);
        printf("%c", '\0');
        ball->pos_x += left_or_right;
        cursor_pos(ball->pos_x, ball->pos_y);

        //射击到敌人
        if (ball->pos_x == ENEMY(1).pos_x && ball->pos_y == ENEMY(1).pos_y)
        {
            score++;
            cursor_pos(ball->pos_x, ball->pos_y);
            printf("%c%c", '\0', '\0');
            return true;
        }

        //射击前摇
        Sleep(SHOOT_SP);
    }
    free(ball);

    return false;
}

//玩家及游戏信息
void game_info(void)
{
    cursor_pos(GAME_INFO_SCREEN_WIDTH, GAME_INFO_SCREEN_HEIGHT);
    printf("血量: %.1f\n", player.hp);
    cursor_pos(GAME_INFO_SCREEN_WIDTH, GAME_INFO_SCREEN_HEIGHT + 1);
    printf("得分: %d\n", score);
    cursor_pos(GAME_INFO_SCREEN_WIDTH, GAME_INFO_SCREEN_HEIGHT + 2);
    high_score = score > high_score ? score : high_score;
    printf("最高得分: %d\n", high_score);
    cursor_pos(GAME_INFO_SCREEN_WIDTH, GAME_INFO_SCREEN_HEIGHT + 3);
    printf("W S D E 移动");
    cursor_pos(GAME_INFO_SCREEN_WIDTH, GAME_INFO_SCREEN_HEIGHT + 4);
    printf("J 攻击");

    return;
}

//初始化敌人
void init_enemy(enemy *enemy)
{
    srand(time(NULL));

    enemy->state = rand() % 2 + 1;
    enemy->is_created = false;
    enemy->pos_x = rand() % 40 + 31;
    enemy->pos_y = rand() % 18 + 6;
    //玩家位置限制
    while (enemy->pos_x >= player.pos_x && enemy->pos_x <= player.pos_x + PLAYER_WIDTH + 2 && enemy->pos_y >= player.pos_y && enemy->pos_y <= player.pos_y + PLAYER_HEIGHT)
    {
        enemy->pos_x = rand() % 40 + 31;
        enemy->pos_y = rand() % 18 + 6;
    }

    return;
}

//产生敌人
void create_enemy(enemy *enemy)
{
    if (!enemy->is_created)
    {
        cursor_pos(enemy->pos_x, enemy->pos_y);
        enemy->state == 1 ? printf("o-") : printf("-o");
        enemy->is_created = true;
    }

    return;
}

//产生敌人球 返回是否打到玩家
bool enemy_ball(void)
{
    int leftorright = ENEMY(1).state == 1 ? 1 : -1;
    node_ball *ball = (node_ball *)malloc(sizeof(node_ball));

    ball->pos_x = ENEMY(1).state == 1 ? ENEMY(1).pos_x + 2 : ENEMY(1).pos_x - 1;
    ball->pos_y = ENEMY(1).pos_y;

    cursor_pos(ball->pos_x, ball->pos_y);
    while (ball->pos_x > 2 && ball->pos_x < MAP_LEN_WIDTH + 2)
    {
        printf("%c", '-');
        cursor_pos(ball->pos_x, ball->pos_y);
        printf("%c", '\0');
        ball->pos_x += leftorright;
        cursor_pos(ball->pos_x, ball->pos_y);

        //打到玩家
        if (ball->pos_x >= player.pos_x && ball->pos_x <= player.pos_x + PLAYER_WIDTH && ball->pos_y >= player.pos_y && ball->pos_y <= player.pos_y + PLAYER_HEIGHT)
            return true;
    }

    return false;
}

//射击玩家
void hurt_player(void)
{
    if (enemy_ball())
    {
        srand(time(NULL));

        int digit_01 = rand() % 10;
        int digit_02 = rand() % 10;
        int digit_03 = rand() % 10;

        float hurt = digit_01 + digit_02 / 10.0f + digit_03 / 100.0f;
        player.hp -= hurt;
    }

    return;
}