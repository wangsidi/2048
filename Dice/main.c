/**
 * 项    目: 骰子大作战
 * 时    间: 20200213 14:27
 * 编 写 人: 王斯迪
 */

#include "main.h"
#include <stdio.h>

//玩家结构体
player_info player;
//骰子点数
short dice_point = 0;
//操作次数
short opt_num = 0;
//谁胜利了
short who_win = 0;
//玩家一得分
short count_01 = 0;
//玩家二得分
short count_02 = 0;

int main(void)
{
    _home();
    _start();
    _game();
    _end();

    getchar();
    return 0;
}
