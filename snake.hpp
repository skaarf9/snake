/*
 * @Description: 蛇类声明
 * @Author: skaarf
 * @Date: 2020-06-24 03:38:23
 * @LastEditTime: 2021-12-01 01:34:24
 * @LastEditors: skaarf9
 */
#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_
#include <iostream>

//位置坐标
class Point
{
public:
    Point(){};            //默认构造函数
    Point(int xx, int yy) //有参构造函数
    {
        x = xx;
        y = yy;
    }
    Point(const Point &p) //拷贝构造函数
    {
        x = p.x;
        y = p.y;
    }
    int getX();                     //取x
    int getY();                     //取y
    bool operator==(const Point &p) //重载==
    {
        return this->x == p.x && this->y == p.y;
    };
    void setPoint(Point p);       //设置坐标
    void setPoint(int xx, int yy) //设置坐标
    {
        x = xx;
        y = yy;
    };
    Point getLeft();  //左
    Point getRight(); //右
    Point getUp();    //上
    Point getDown();  //下
    void toString();  //toString

private:
    int x;
    int y;
};
//蛇身类
class SnakeBody
{
public:
    SnakeBody(){};      //无参构造
    SnakeBody(Point pp) //有参构造
    {
        p = pp;
    };
    Point getPoint();       //获取位置
    void setPoint(Point p); //设置坐标
    SnakeBody *next;        //下一节

private:
    friend class SnakeHead; //友元
    Point p;                //坐标
};
//蛇头类
class SnakeHead
{
public:
    SnakeBody *next = NULL;      //下一节
    int bodyLength = 0;          //身体长度(从1开始,0为没有)
    int maxLength = 50;          //最大长度
    char key = 'w';              //方向
    SnakeHead(){};               //无参构造
    SnakeHead(Point pp, int max) //有参构造
    {
        this->p = pp;
        maxLength = max;
    };
    void headMove();             //头部运动
    SnakeBody *getBody(int nth); //获取第nth节
    Point getPoint();            //获取坐标
    void setPoint(Point p);      //设置坐标
    void move();                 //移动

private:
    Point p; //坐标
};

#endif
