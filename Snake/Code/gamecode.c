/**
 * 项    目: 贪吃蛇
 * 时    间: 20200210 19:11
 * 编 写 人: 王斯迪
 */

/**
 * 项    目: 贪吃蛇
 * 时    间: 20200211 9:58 (更新)
 * 编 写 人: 王斯迪
 */

#include "../ku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

extern node_snake *p_Head;
extern struct food food;
extern char key_state;
extern char key_temp;
extern int count;

//绘制地图
void draw_map(void)
{
    for (int i = 1; i <= MAP_HEIGHT; i++)
    {
        set_coord(0, i);
        printf("□");
        set_coord(MAP_WIDTH + 2, i);
        printf("□");
    }
    for (int j = 0; j <= MAP_WIDTH + 2; j += 2)
    {
        set_coord(j, 0);
        printf("□");
        set_coord(j, MAP_HEIGHT + 1);
        printf("□");
    }

    return;
}

//食物位置条件
int case_food(int x, int y)
{
    node_snake *p_Body = p_Head;

    while (p_Body != NULL)
    {
        if (p_Body->pos_x == x && p_Body->pos_y == y)
            return 0;
        p_Body = p_Body->next;
    }

    return 1;
}

//随机产生食物
void create_food(void)
{
    srand(time(NULL));

    food.pos_x = rand() % MAP_WIDTH + 1;
    food.pos_x = (food.pos_x % 2 == 0) ? food.pos_x : food.pos_x + 1;
    food.pos_y = rand() % MAP_HEIGHT + 1;

    while (!case_food(food.pos_x, food.pos_y))
    {
        food.pos_x = rand() % MAP_WIDTH + 1;
        food.pos_x = (food.pos_x % 2 == 0) ? food.pos_x : food.pos_x + 1;
        food.pos_y = rand() % MAP_HEIGHT + 1;
    }

    set_coord(food.pos_x, food.pos_y);
    printf("%c", '*');
}

//初始化蛇
void init_snake(int len)
{
    node_snake *p_Tail;

    for (int i = 0; i < len; i++)
    {
        node_snake *p_New = (node_snake *)malloc(sizeof(node_snake));

        p_New->pos_x = 2 * len - 2 * i;
        p_New->pos_y = 3;
        p_New->next = NULL;

        if (p_Head == NULL)
            p_Head = p_New;
        else
        {
            p_Tail = p_Head;

            while (p_Tail->next != NULL)
                p_Tail = p_Tail->next;
            p_Tail->next = p_New;
            p_Tail = p_New;
        }
    }

    return;
}

//画蛇
void draw_snake(void)
{
    node_snake *p_Draw = p_Head;

    while (p_Draw != NULL)
    {
        set_coord(p_Draw->pos_x, p_Draw->pos_y);
        printf("■");
        p_Draw = p_Draw->next;
    }

    return;
}

//蛇的移动
void move_snake(void)
{
    node_snake *p_NewHead = (node_snake *)malloc(sizeof(node_snake));

    if (kbhit())
    {
        key_temp = key_state;
        key_state = getch();
    }
    switch (key_state)
    {
    default:
        key_state = key_temp;
    case 'd':
        if (key_temp != 'a')
        {
            p_NewHead->pos_x = p_Head->pos_x + 2;
            p_NewHead->pos_y = p_Head->pos_y;
        }
        else
        {
            key_state = key_temp;
            p_NewHead->pos_x = p_Head->pos_x - 2;
            p_NewHead->pos_y = p_Head->pos_y;
        }
        break;
    case 's':
        if (key_temp != 'w')
        {
            p_NewHead->pos_x = p_Head->pos_x;
            p_NewHead->pos_y = p_Head->pos_y + 1;
        }
        else
        {
            key_state = key_temp;
            p_NewHead->pos_x = p_Head->pos_x;
            p_NewHead->pos_y = p_Head->pos_y - 1;
        }
        break;
    case 'a':
        if (key_temp != 'd')
        {
            p_NewHead->pos_x = p_Head->pos_x - 2;
            p_NewHead->pos_y = p_Head->pos_y;
        }
        else
        {
            key_state = key_temp;
            p_NewHead->pos_x = p_Head->pos_x + 2;
            p_NewHead->pos_y = p_Head->pos_y;
        }

        break;
    case 'w':
        if (key_temp != 's')
        {
            p_NewHead->pos_x = p_Head->pos_x;
            p_NewHead->pos_y = p_Head->pos_y - 1;
        }
        else
        {
            key_state = key_temp;
            p_NewHead->pos_x = p_Head->pos_x;
            p_NewHead->pos_y = p_Head->pos_y + 1;
        }
        break;
    }
    p_NewHead->next = p_Head;
    p_Head = p_NewHead;
    if (p_Head->pos_x == food.pos_x && p_Head->pos_y == food.pos_y)
    {
        create_food();
        return;
    }
    else
    {
        node_snake *p_end = p_Head;

        while (p_end->next->next != NULL)
            p_end = p_end->next;
        //清除蛇尾
        set_coord(p_end->next->pos_x, p_end->next->pos_y);
        printf("%c", '\0');
        //释放蛇尾指针
        free(p_end->next);
        p_end->next = NULL;
    }

    return;
}

//撞墙
int touch_wall(void)
{
    if (p_Head->pos_x > MAP_WIDTH || p_Head->pos_x < 1 || p_Head->pos_y > MAP_HEIGHT || p_Head->pos_y < 1)
        return 0;
    return 1;
}

//吃到自己
int eat_self(void)
{
    node_snake *p_Body;

    p_Body = p_Head->next;

    while (p_Body != NULL)
    {
        if (p_Head->pos_x == p_Body->pos_x && p_Head->pos_y == p_Body->pos_y)
            return 0;
        p_Body = p_Body->next;
    }
    return 1;
}

//计算蛇长
int snake_len(void)
{
    int count = 0;
    node_snake *snake = p_Head;

    while (snake != NULL)
    {
        count++;
        snake = snake->next;
    }

    return count;
}

//读取最高分
void _road(void)
{
    FILE *fp;

    fp = fopen(FILE_SAVE_GOAL, "ab");
    if (fp == NULL)
        exit(-1);
    else
        fclose(fp);

    fp = fopen(FILE_SAVE_GOAL, "rb");
    if (fread(&count, sizeof(int), 1, fp) == 0)
        count = 0;
    fclose(fp);

    return;
}

//打印蛇长
void print_count(void)
{
    int count_now = snake_len();
    count = count_now > count ? count_now : count;

    set_coord(90, 0);
    printf("最高得分：%d  蛇长: %d", count, count_now);

    return;
}

//存入得分
void _write(void)
{
    FILE *fp;

    fp = fopen(FILE_SAVE_GOAL, "wb");
    fwrite(&count, sizeof(int), 1, fp);
    fclose(fp);

    return;
}