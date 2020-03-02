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


#include "../main.h"
#include <stdio.h>
#include <stdlib.h>

extern int high_score;

//读取
void _road(void)
{
    FILE *fp;

    //创建文件
    fp = fopen(SAVE_GOAL_FILE_NAME, "ab");

    if (fp == NULL)
    {
        printf("CAN NOT OPEN Goal! ");
        exit(-1);
    }

    fclose(fp);

    //读取文件
    fp = fopen(SAVE_GOAL_FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("CAN NOT OPEN Goal! ");
        exit(-1);
    }

    if (fread(&high_score, sizeof(int), 1, fp) == 0)
        high_score = 0;
    fclose(fp);

    return;
}

//写入
void _write(void)
{
    FILE *fp;

    fp = fopen(SAVE_GOAL_FILE_NAME, "wb");

    if (fp == NULL)
    {
        printf("CAN NOT OPEN Goal! ");
        exit(-1);
    }

    fwrite(&high_score, sizeof(int), 1, fp);
    fclose(fp);

    return;
}