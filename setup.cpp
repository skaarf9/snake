/*
 * @Description: 设置类
 * @Author: skaarf
 * @Date: 2020-06-24 03:24:55
 * @LastEditTime: 2020-06-30 17:27:58
 * @LastEditors: skaarf
 */
#ifndef _SETUP_CPP_
#define _SETUP_CPP_
#include <iostream>
using namespace std;

class SetUp
{
public:
    SetUp(){};
    int mapHeight = 30; //窗口高度
    int mapWidth = 60;  //窗口宽度
    int snakeSize = 40; //蛇的最大节数
    int speed = 120;    //初始速度(时间间隔)
    char key = 'w';     //初始方向
    void set();         //设置
};
#endif
