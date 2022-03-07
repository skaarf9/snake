/*
 * @Description: 蛇类方法实现
 * @Author: skaarf
 * @Date: 2020-06-23 14:21:38
 * @LastEditTime: 2020-06-30 17:52:06
 * @LastEditors: skaarf
 */
#include "snake.hpp"
#include <iostream>
using namespace std;

//------------------------------方法实现-----------------------------
//设置坐标
void Point::setPoint(Point p)
{
    this->x = p.getX();
    this->y = p.getY();
}
//取x
int Point::getX()
{
    return this->x;
}
//取y
int Point::getY()
{
    return this->y;
}
//打印坐标
void Point::toString()
{
    cout << this->x << "   " << this->y << endl;
}
//下坐标
Point Point::getDown()
{
    return Point(this->x, this->y + 1);
}
//右坐标
Point Point::getRight()
{
    return Point(this->x + 2, this->y);
}
//上坐标
Point Point::getUp()
{
    return Point(this->x, this->y - 1);
}
//左坐标
Point Point::getLeft()
{
    return Point(this->x - 2, this->y);
}
//设置坐标
void SnakeBody::setPoint(Point p)
{
    this->p = p;
}

//获取坐标
Point SnakeBody::getPoint()
{
    return this->p;
}
//头部移动
void SnakeHead::headMove()
{
    SnakeBody *body = new SnakeBody;
    body->setPoint(this->getPoint());
    switch (this->key)
    {
    case 'd':
    case 'D':
        this->setPoint(this->getPoint().getRight());
        break;
    case 'w':
    case 'W':
        this->setPoint(this->getPoint().getUp());
        break;
    case 's':
    case 'S':
        this->setPoint(this->getPoint().getDown());
        break;
    case 'a':
    case 'A':
        this->setPoint(this->getPoint().getLeft());
        break;
    default:
        break;
    }
    body->next = this->next;
    this->next = body;
    this->bodyLength++;
}
//普通移动
void SnakeHead::move()
{
    //头部增长操作
    this->headMove();
    //释放最后一节
    delete (this->getBody(this->bodyLength));
    this->bodyLength--;
    this->getBody(this->bodyLength)->next = NULL;
}
//获取坐标
Point SnakeHead::getPoint()
{
    return this->p;
}
//设置坐标
void SnakeHead::setPoint(Point p)
{
    this->p = p;
}
//获取第nth节
SnakeBody *SnakeHead::getBody(int nth)
{
    SnakeBody *body = NULL;
    if (nth <= this->bodyLength)
    {
        body = this->next;
        while (nth > 1)
        {
            body = body->next;
            nth--;
        }
    }
    return body;
}
//测试程序(不计入代码行数)
// int main()
// {
//     Point p1 = Point(1, 1);
//     Point p2 = Point(1, 2);
//     SnakeHead head = SnakeHead(p1, 50);
//     head.getPoint().toString(); //1 1
//     head.addBody();
//     (head.next)->getPoint().toString();
//     head.getBody(1)->getPoint().toString();
//     head.getPoint().toString();
//     system("pause");
//     return 0;
// }
