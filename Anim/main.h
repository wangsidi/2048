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

#include <stdbool.h>

#define MAP_LEN_HEIGHT 28
#define MAP_LEN_WIDTH 100
#define PLAYER_HEIGHT 6
#define PLAYER_WIDTH 20
#define PLAYER_INIT_POS_X 3
#define PLAYER_INIT_POS_Y 3
#define PLAYER_WAIT_STATE_SPEED 100
#define GAME_INFO_SCREEN_WIDTH 106
#define GAME_INFO_SCREEN_HEIGHT 0
#define SHOOT_SP 10
#define ENEMY(X) enemy##X
#define SAVE_GOAL_FILE_NAME "Goal"

//玩家信息
typedef struct
{
    int pos_x;
    int pos_y;
    int state;
    float hp;
} node_player;

//敌人信息
typedef struct
{
    int pos_x;
    int pos_y;
    int state;//1 or 2
    bool is_created;
}enemy;

//子弹信息
typedef struct
{
    int pos_x;
    int pos_y;
} node_ball;

void cursor_visible(bool);
void cursor_pos(int, int);
void draw_map(void);
void draw_player(const char[][PLAYER_WIDTH], int);
void init_player(int, int);
void anim_snip(void);
void control_player(void);
void game_info(void);
bool fly_ball(void);
void init_enemy(enemy *);
void create_enemy(enemy *);
bool enemy_ball(void);
void hurt_player(void);
void _start(void);
void _game(void);
void _end(void);
void _road(void);
void _write(void);
