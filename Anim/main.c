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

#include "main.h"

//人物变量
node_player player;
//按键
char key = '\0';
//人物转向
int left_or_right = 1;
//敌人
enemy ENEMY(1);
//得分
int score = 0;
//最高得分
int high_score = 0;

int main(void)
{
    _road();
    _start();
    _game();
    _end();
    _write();
    
    return 0;
}