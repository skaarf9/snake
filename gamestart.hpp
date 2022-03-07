/*
 * @Description: 开始游戏方法声明
 * @Author: skaarf
 * @Date: 2020-06-24 03:48:36
 * @LastEditTime: 2020-06-30 17:32:43
 * @LastEditors: skaarf
 */
#ifndef _GAMESTART_HPP_
#define _GAMESTART_HPP_
#include "snake.hpp"
void menu();               //菜单
void drawMap();            //画地图
void creatFood(bool eat);  //食物产生
void keyDown();            //按键操作
int snakeStatus();         //蛇的状态:判断是否结束游戏
void gotoxy(Point p);      //辅助函数:光标移动
void gotoxy(int x, int y); //辅助函数:光标移动
bool pointCheck(Point p);  //检测点是否在蛇身上 true: 在蛇身上 false: 不在蛇身上
void startGame();          //开始游戏
void map();                //地图
bool wallCheck(Point p);   //点是否在墙上
#endif
