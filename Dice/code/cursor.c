/**
 * 项    目: 骰子大作战
 * 时    间: 20200213 14:27
 * 编 写 人: 王斯迪
 */

#include "../main.h"
#include <windows.h>
#include <stdbool.h>

//设置光标是否可见
void cursor_isvisible(bool isvisible)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(out, &info);
    info.bVisible = isvisible;
    SetConsoleCursorInfo(out, &info);

    return;
}

//设置光标位置
void cursor_pos(int x, int y)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos = {x, y};
    SetConsoleCursorPosition(out, pos);

    return;
}