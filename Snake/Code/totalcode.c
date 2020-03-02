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

//开始
void _start(void)
{
    _road();
    hide_cursor();
    draw_map();
    init_snake(SNAKE_INIT_LEN);
    draw_snake();
    create_food();

    return;
}

//游戏过程
void _progess(void)
{
    print_count();
    move_snake();
    draw_snake();

    return;
}

//结束
void _end(void)
{
    _write();
    set_coord(50, 14);
    printf("游戏结束!(回车)\n");
    while (getchar() != '\n')
        continue;

    return;
}