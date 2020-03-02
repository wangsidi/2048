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

#include "ku.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//设置头指针
node_snake *p_Head = NULL;
//设置食物位置
struct food food;
//按键
char key_state = 'd';
//记录上一次按键
char key_temp = 'd';
//最高得分
int count = 0;

int main(void)
{
    _start();

    while (touch_wall() && eat_self())
    {
        _progess();
        Sleep(100);
    }
    system("cls");
    _end();

    return 0;
}
