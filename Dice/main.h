/**
 * 项    目: 骰子大作战
 * 时    间: 20200213 14:27
 * 编 写 人: 王斯迪
 */

#include <stdbool.h>

//游戏名
#define GAME_NAME "(无聊版)骰子大作战"

//地图
#define MAP_LEN_WIDTH 100
#define MAP_LEN_HEIGHT 28

//玩家一初始信息
#define PLAYER_IMAG_01 'o'
#define PLAYER_INIT_POS_X_01 6
#define PLAYER_INIT_POS_Y_01 6

//玩家二初始信息
#define PLAYER_IMAG_02 '*'
#define PLAYER_INIT_POS_X_02 95
#define PLAYER_INIT_POS_Y_02 22

//武器
#define GUN_POS_X 52
#define GUN_POS_Y 14
#define GUN_IMAG '-'

//游戏提示信息
#define INFO_POS_X 106
#define INFO_POS_Y 0
#define INFO(n) printf("轮到玩家" #n "")
#define WIN(n) printf("玩家" #n "胜利!")

//胜利条件
#define WIN_CASE 5

//玩家结构体
typedef struct
{
    int pos_x_01;
    int pos_y_01;
    int pos_x_02;
    int pos_y_02;
    bool is_have_gun_01;
    bool is_have_gun_02;
    bool state; //玩家顺序:true为玩家一;false为玩家二 初始为玩家1
} player_info;

void cursor_isvisible(bool);
void cursor_pos(int, int);
void draw_map(void);
void init_player(void);
void init_gun(void);

void move_player(int, int, int, int);
void clear_player(int, int, int, int);
void info_message(void);
void put_dice(void);
void hurt_wall(int, int);
void eat_player(void);
void got_gun(void);
void key_player(void);

void _home(void);
void _start(void);
void _game(void);
void _end(void);
