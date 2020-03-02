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

#define MAP_HEIGHT 28
#define MAP_WIDTH 80
#define SNAKE_INIT_LEN 4
#define FILE_SAVE_GOAL "hightestgoal"

//定义蛇
typedef struct snake
{
    int pos_x;
    int pos_y;
    struct snake *next;
} node_snake;

//食物位置
struct food
{
    int pos_x;
    int pos_y;
};

void hide_cursor(void);
void set_coord(int, int);
void init_snake(int);
void draw_snake(void);
void move_snake(void);
int case_food(int, int);
void create_food(void);
void draw_map(void);
int touch_wall(void);
int eat_self(void);
int snake_len(void);
void print_count(void);
void _road(void);
void _write(void);
void _start(void);
void _progess(void);
void _end(void);
