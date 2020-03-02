/**
 * 项    目: 2048
 * 时    间: 20200204 9:11
 * 编 写 人: 王斯迪
 */

/**
 * 项    目: 2048
 * 时    间: 20200205 9:51 (更新)
 * 编 写 人: 王斯迪
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
//输出
#define PRI(...) printf(__VA_ARGS__)
//数组长、宽
#define LENGTH 4
//退出键
#define QUIT 'q'
//重新开始键
#define CONTINUE 'c'
//文件名
#define FILE_NAME "highestgoal"

//最高得分
static int count_max = 0;

//隐藏光标
void hide_cursor(void)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo); //获取控制台光标信息
    CursorInfo.bVisible = false;               //隐藏控制台光
    SetConsoleCursorInfo(handle, &CursorInfo); //设置控制台光标状态

    return;
}


//读
void _road(void)
{
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");
    fread(&count_max, sizeof(int), 1, fp);

    fclose(fp);

    return;
}

//写
void _write(void)
{
    FILE *fp;

    fp = fopen(FILE_NAME, "wb");
    fwrite(&count_max, sizeof(int), 1, fp);

    fclose(fp);

    return;
}

//分数计算
int _count(int (*map)[LENGTH], int rows)
{
    int count = 0;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < LENGTH; ++j)
            count += *(*(map + i) + j);

    return count;
}

//判断数字溢出
bool is_Over(int (*map)[LENGTH], int rows)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < LENGTH; ++j)
            if (map[i][j] == 0)
                return false;
    return true;
}

//判断是否失败
bool is_Lose(int (*map)[LENGTH], int rows)
{
    if (is_Over(map, rows))
    {
        //相邻数字是否相等
        for (int i = 0; i < rows - 1; ++i)
            for (int j = 0; j < LENGTH - 1; ++j)
                if ((*(*(map + i) + j) == *(*(map + i + 1) + j)) || (*(*(map + i) + j) == *(*(map + i) + j + 1)))
                    return false;
        //特殊位置判定(右下角)
        if (*(*(map + rows) + LENGTH) == *(*(map + rows - 1) + LENGTH) || *(*(map + rows) + LENGTH) == *(*(map + rows) + LENGTH - 1))
            return false;
        return true;
    }
    return false;
}

//生成随机位置随机数
void create_Num(int (*map)[LENGTH], int rows)
{
    int r, c;

    //随机数每次运行随机产生
    srand(time(NULL));

    //判定继续
    if (!is_Over(map, LENGTH))
    {
        //生成数字
        while (1)
        {
            r = rand() % rows;
            c = rand() % LENGTH;
            if (*(*(map + r) + c) == 0)
            {
                map[r][c] = ((rand() % 5 == 0) ? 4 : 2);
                break;
            }
        }
    }
}

//初始化地图
void create_Map(int (*map)[LENGTH], int rows)
{
    create_Num(map, rows);
    create_Num(map, rows);
}

//打印地图
void print_Map(int (*map)[LENGTH], int rows)
{
    PRI(" ____________ ____________ ____________ ____________ \n");
    for (int i = 0; i < rows; ++i)
    {
        PRI("|            |            |            |            |\n");
        for (int j = 0; j < LENGTH; ++j)
        {
            if (*(*(map + i) + j) != 0)
                PRI("|%6d      ", *(*(map + i) + j));
            else
                PRI("|            ");
        }
        PRI("|\n");
        PRI("|____________|____________|____________|____________|\n");
    }
}

//去零
void _delete(int *arr, int len)
{
    for (int i = 0; i < len - 1; ++i)
        for (int j = 0; j < len - i - 1; ++j)
            if (arr[j] == 0)
            {
                arr[j] = arr[j + 1];
                arr[j + 1] = 0;
            }
}

//合并
void _merge(int *arr, int len)
{
    _delete(arr, len);
    for (int i = 0; i < len - 1; ++i)
    {
        if (*(arr + i) == *(arr + i + 1))
        {
            *(arr + i) *= 2;
            *(arr + i + 1) = 0;
        }
    }
    _delete(arr, len);
}

//上移
void _up(int (*map)[LENGTH], int rows)
{
    for (int c = 0; c < LENGTH; ++c)
    {
        int *arr = (int *)malloc(sizeof(int) * rows);
        for (int r = 0; r < rows; ++r)
            *(arr + r) = *(*(map + r) + c);
        _merge(arr, rows);
        for (int index = 0; index < rows; ++index)
            *(*(map + index) + c) = *(arr + index);
    }
}

//下移
void _down(int (*map)[LENGTH], int rows)
{
    for (int c = 0; c < LENGTH; ++c)
    {
        int *arr = (int *)malloc(sizeof(int) * rows);
        for (int r = 0; r < rows; ++r)
            *(arr + r) = *(*(map + rows - 1 - r) + c);
        _merge(arr, rows);
        for (int index = 0; index < rows; ++index)
            *(*(map + index) + c) = *(arr + rows - 1 - index);
    }
}

//左移
void _left(int (*map)[LENGTH], int rows)
{
    for (int r = 0; r < rows; ++r)
    {
        int *arr = (int *)malloc(sizeof(int) * LENGTH);
        for (int c = 0; c < LENGTH; ++c)
            *(arr + c) = *(*(map + r) + c);
        _merge(arr, LENGTH);
        for (int index = 0; index < rows; ++index)
            *(*(map + r) + index) = *(arr + index);
    }
}

//右移
void _right(int (*map)[LENGTH], int rows)
{
    for (int r = 0; r < rows; ++r)
    {
        int *arr = (int *)malloc(sizeof(int) * LENGTH);
        for (int c = 0; c < LENGTH; ++c)
            *(arr + c) = *(*(map + r) + LENGTH - 1 - c);
        _merge(arr, LENGTH);
        for (int index = 0; index < rows; ++index)
            *(*(map + r) + index) = *(arr + LENGTH - 1 - index);
    }
}

//地图前后是否变化
bool is_Change(int (*map)[LENGTH], int (*map_cpy)[LENGTH], int rows)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < LENGTH; ++j)
            if (*(*(map + i) + j) != *(*(map_cpy + i) + j))
                return true;
    return false;
}

//主函数
int main(void)
{
    hide_cursor();
    _road();
    while (1)
    {
        //按键
        char key;

        int map[LENGTH][LENGTH] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        PRI("当前游戏更新于: %-20s%s\n\n", __DATE__, __TIME__);
        //标头
        PRI("                     2048小游戏              (q可退出)\n");
        PRI("-----------------------------------------------------\n");
        //初始化得分
        PRI("得分: 0  最高得分: %d\n", count_max);
        create_Map(map, LENGTH);
        print_Map(map, LENGTH);
        while ((key = getch()) != QUIT && !is_Lose(map, LENGTH))
        {
            //清空控制台
            system("cls");

            PRI("当前游戏更新于: %-20s%s\n\n", __DATE__, __TIME__);
            //标头
            PRI("                     2048小游戏              (q可退出)\n");
            PRI("-----------------------------------------------------\n");
            //刷新最高得分
            if (_count(map, LENGTH) > count_max)
                count_max = _count(map, LENGTH);
            //计算得分
            PRI("得分: %d  最高得分: %d\n", _count(map, LENGTH), count_max);
            switch (key)
            {
                int map_cpy[LENGTH][LENGTH];

            case 'w':
                //二维数组拷贝
                memcpy(map_cpy, map, sizeof(int) * LENGTH * LENGTH);
                _up(map, LENGTH);
                if (is_Change(map, map_cpy, LENGTH))
                    create_Num(map, LENGTH);
                print_Map(map, LENGTH);
                break;

            case 's':
                //二维数组拷贝
                memcpy(map_cpy, map, sizeof(int) * LENGTH * LENGTH);
                _down(map, LENGTH);
                if (is_Change(map, map_cpy, LENGTH))
                    create_Num(map, LENGTH);
                print_Map(map, LENGTH);
                break;

            case 'a':
                //二维数组拷贝
                memcpy(map_cpy, map, sizeof(int) * LENGTH * LENGTH);
                _left(map, LENGTH);
                if (is_Change(map, map_cpy, LENGTH))
                    create_Num(map, LENGTH);
                print_Map(map, LENGTH);
                break;

            case 'd':
                //二维数组拷贝
                memcpy(map_cpy, map, sizeof(int) * LENGTH * LENGTH);
                _right(map, LENGTH);
                if (is_Change(map, map_cpy, LENGTH))
                    create_Num(map, LENGTH);
                print_Map(map, LENGTH);
                break;

            default:
                print_Map(map, LENGTH);
                break;
            }
        }
        PRI("是否重新开始游戏(c+ENTER为继续, 其他键退出): ");
        if (getchar() != CONTINUE)
            break;
        //回收其他字符(q以外其他字符)
        while (getchar() != '\n')
            continue;
        //清除控制台
        system("cls");
    }
    _write();
    system("pause");

    return 0;
}
