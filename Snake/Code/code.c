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

#include <windows.h>
#include <stdbool.h>

//隐藏光标
void hide_cursor(void)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo); //获取控制台光标信息
    CursorInfo.bVisible = false;               //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo); //设置控制台光标状态

    return;
}

//设置光标位置
void set_coord(int x, int y)
{
    COORD point = {x, y};                         //光标要设置的位置x,y
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
    SetConsoleCursorPosition(out, point);         //设置光标位置

    return;
}