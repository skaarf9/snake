/*
 * @Description: 游戏开始函数实现
 * @Author: skaarf
 * @Date: 2020-06-24 03:15:17
 * @LastEditTime: 2020-06-30 19:38:02
 * @LastEditors: skaarf
 */
#ifndef _GAMESTART_CPP_
#define _GAMESTART_CPP_

#include "gamestart.hpp"
#include "map.cpp"
#include <stdlib.h>

//开始游戏
void startGame()
{
    snake.bodyLength = 0;
    speed = s.speed;//初始速度(时间间隔)
    score = -100;
    drawMap();

    //暂停
    gotoxy(MAPWIDTH + 6, 22);
    cout << "按任意键开始";
    _getch();

    gotoxy(MAPWIDTH + 6, 22);
    cout << "            ";
    while (true)
    {
        creatFood(snake.getPoint() == food);
        Sleep(speed);
        keyDown();
        if (!snakeStatus())
        {
            gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2);
            cout << "GAME OVER";
            gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 1);
            cout << "得分:" << score;
            _getch();
            break;
        }
    }
    menu();
}

/**
 * @description: 判断食物产生
 * @param : eat true为吃到 false为没有吃
 * @return: void
 */
void creatFood(bool eat)
{
    if (eat) //如果吃到食物
    {
        srand((unsigned int)time(NULL));
        bool flag;
        //食物不能在墙和身体上
        while (true)
        {
            food.setPoint(rand() % (MAPWIDTH - 4) + 2, rand() % (MAPHEIGHT - 2) + 1);
            flag = pointCheck(food) || wallCheck(food);
            if (!flag && food.getX() % 2 == 0)
            {
                break;
            }
        }
        gotoxy(food);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); //设置黄色
        cout << "⊙";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
        //如果长度在最大范围内
        if (snake.bodyLength + 1 < snake.maxLength)
        {
            snake.bodyLength++;
            changeFlag = 1;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //设置颜色为绿色
            gotoxy(MAPWIDTH + 24, 9);
            cout << snake.bodyLength + 1;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
        }
        //分数增加并刷新
        gotoxy(MAPWIDTH + 20, 5);
        score += 100;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //设置颜色为绿色
        cout << score;
        //蛇的不断变色
        if (score / 100 % 2)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); //设置红色
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
        }
        //每2000分难度增加
        if (score % 1000 == 0)
        {
            gotoxy(MAPWIDTH + 20, 7);
            speed -= 20;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //设置颜色为绿色
            cout << speed  << " ";//防止未覆盖后一位
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
        }
    }
}

/**
 * @description: 判断点是否在墙上,用于食物产生和蛇头撞墙
 * @param : p 所判断的点
 * @return: true:在墙上 false:不在墙上
 */
bool wallCheck(Point p)
{
    if (wall != NULL)
    {
        int index = (p.getX() / 2 - 1) + (p.getY() - 1) * wallX;
        return wall[index];
    }
    return false;
}

/**
 * @description: 判断点是否在蛇身上,用于食物产生和判断蛇头与蛇身相撞
 * @param : p 所判断的点
 * @return: true: 在蛇身上 false: 不在蛇身上
 */
bool pointCheck(Point p)
{
    bool flag = false;
    SnakeBody *body = snake.next;
    if (snake.getPoint() == p)
    {
        flag = true;
        return flag;
    }
    while (body != NULL)
    {
        if (body->getPoint() == food)
        {
            flag = true;
            break;
        }
        body = body->next;
    }
    return flag;
}
//按键操作,操控蛇
void keyDown()
{
    //如果有按键操作
    if (_kbhit())
    {
        fflush(stdin);
        char key = _getch();
        //按'q'暂停
        if (key == 'q' || key == 'Q')
        {
            //停止等待键盘输入
            gotoxy(MAPWIDTH + 6, 13);
            cout << "游戏暂停中";
            _getch();
            gotoxy(MAPWIDTH + 6, 13);
            cout << "          ";
        }
        if (key == 'w' || key == 'W' || key == 'a' || key == 'A' || key == 's' || key == 'S' || key == 'd' || key == 'D')
        {
            switch (snake.key)
            {
            case 'd':
            case 'D':
                if (key != 'a' && key != 'A')
                {
                    snake.key = key;
                }
                break;
            case 'w':
            case 'W':
                if (key != 's' && key != 'S')
                {
                    snake.key = key;
                }
                break;
            case 's':
            case 'S':
                if (key != 'w' && key != 'W')
                {
                    snake.key = key;
                }
                break;
            case 'a':
            case 'A':
                if (key != 'd' && key != 'D')
                {
                    snake.key = key;
                }
                break;
            default:
                break;
            }
        }
    }
    if (!changeFlag) //没有吃
    {
        gotoxy(snake.getBody(snake.bodyLength)->getPoint());
        cout << "  ";
    }
    snake.move();
    gotoxy(snake.getPoint());
    cout << "██";
    changeFlag = 0;
    gotoxy(MAPWIDTH, 0);
}

//蛇的状态:判断是否结束游戏
int snakeStatus()
{
    if (snake.getPoint().getX() == 0 || snake.getPoint().getX() == MAPWIDTH - 2 || snake.getPoint().getY() == 0 || snake.getPoint().getY() == MAPHEIGHT - 1 || wallCheck(snake.getPoint()))
    {
        return 0;
    }
    SnakeBody *body = snake.next;
    Point p = snake.getPoint();
    while (body != NULL)
    {
        if (p == body->getPoint())
        {
            return 0;
        }
        body = body->next;
    }
    return 1;
}

/**
 * @description: 辅助函数:光标移动
 * @param : p 坐标
 * @return: void
 */
void gotoxy(Point p)
{
    //找到控制台这个窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //光标的结构体
    COORD coord;
    //设置坐标
    coord.X = p.getX();
    coord.Y = p.getY();
    //同步到控制台
    SetConsoleCursorPosition(handle, coord);
}
/**
 * @description: 辅助函数:光标移动
 * @param : x横坐标,y纵坐标
 * @return: void
 */
void gotoxy(int x, int y)
{
    //找到控制台这个窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //光标的结构体
    COORD coord;
    //设置坐标
    coord.X = x;
    coord.Y = y;
    //同步到控制台
    SetConsoleCursorPosition(handle, coord);
}
#endif
