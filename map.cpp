/*
 * @Description: 地图有关函数
 * @Author: skaarf
 * @Date: 2020-06-24 13:52:40
 * @LastEditTime: 2020-06-30 19:24:43
 * @LastEditors: skaarf
 */
#ifndef _MAP_CPP_
#define _MAP_CPP_
#include "gamestart.hpp"
#include "setup.cpp"
#include "snake.cpp"
#include <conio.h> //按键监控
#include <fstream>
#include <iostream>
#include <time.h>    //食物随机
#include <windows.h> //光标设置API
using namespace std;

//辅助宏定义
#define MAPHEIGHT s.mapHeight //窗口高度
#define MAPWIDTH s.mapWidth   //窗口宽度
#define SNAKESIZE s.snakeSize //蛇的最大节数

//全局变量
int changeFlag = 0;                              //蛇的变化的标记
SetUp s = SetUp();                               //设置类对象s
Point food = Point(MAPWIDTH / 2, MAPHEIGHT / 2); //食物
int wallX = (MAPWIDTH - 4) / 2 - 1;              //墙的x上限
int wallY = MAPHEIGHT - 3;                       //墙的y上限
int *wall = NULL;                                //墙数组
Point p = Point(MAPWIDTH / 2, MAPHEIGHT / 2);    //中间点,便于特殊定位
SnakeHead snake = SnakeHead(p, SNAKESIZE);       //蛇
int speed = s.speed;                             //初始速度(时间间隔)
int score = -100;                                //设置为-100的原因是第一次画食物会加分数

//自定义地图界面
void map()
{
    //圈地
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //设置三色相加
    for (int i = 0; i < MAPHEIGHT; i++)
    {
        gotoxy(0, i);
        cout << "██";
        gotoxy(MAPWIDTH - 2, i);
        cout << "██";
    }
    for (int i = 2; i < MAPWIDTH - 2; i += 2)
    {
        gotoxy(i, 0);
        cout << "██";
        gotoxy(i, MAPHEIGHT - 1);
        cout << "██";
    }
    //画蛇
    snake.key = s.key;
    snake.setPoint(p);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
    //初始三节身体
    for (int k = 0; k < 3; k++)
    {
        gotoxy(snake.getPoint());
        cout << "██";
        snake.headMove();
    }
    gotoxy(snake.getPoint());
    cout << "██";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //设置颜色为绿色
    gotoxy(MAPWIDTH + 8, 10);
    cout << "按下'E'回到坐标栏";
    gotoxy(MAPWIDTH + 8, 11);
    cout << "双击'q'退出";
    gotoxy(MAPWIDTH + 8, 12);
    cout << "'W''A''S''D'控制光标作图";
    gotoxy(MAPWIDTH + 8, 16);
    int x, y;
    printf("请输入坐标,范围:(%d,%d)->(%d,%d)", 0, 0, wallX, wallY);
    gotoxy(MAPWIDTH + 8, 17);
    cin >> x >> y;
    wall = new int[(wallX + 1) * (wallY + 1)];
    for (int i = 0; i < (wallX + 1) * (wallY + 1); i++)
    {
        wall[i] = 0;
    }
    wall[y * wallX + x] = 1;
    gotoxy(x * 2 + 2, y + 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); //设置黄色
    cout << "██";
    gotoxy(MAPWIDTH, 0);
    //gotoxy(0, MAPHEIGHT);
    // for (int i = 0; i <= wallY;i++){
    //     for (int j = 0; j <= wallX;j++){
    //         cout << wall[wallX * i + j] << " ";
    //     }
    //     cout << endl;
    // }
    Point p;
    //如果有按键操作
    while (true)
    {
        if (_kbhit())
        {
            fflush(stdin);
            char key = _getch();
            //双击'q'退出
            if (key == 'q' || key == 'Q')
            {
                key = _getch();
                if (key == 'q' || key == 'Q')
                {
                    gotoxy(MAPWIDTH / 2, MAPHEIGHT / 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); //设置红色
                    cout << "是否保存?Y/N";
                    gotoxy(MAPWIDTH + 8, 17);
                    cout << "      ";
                    gotoxy(MAPWIDTH + 8, 17);
                    fflush(stdin);
                    if (getchar() == 'y')
                    {
                        // 以写模式打开文件
                        ofstream outfile;
                        outfile.open("map.dat");
                        for (int i = 0; i < (wallX + 1) * (wallY + 1); i++)
                        {
                            outfile << wall[i];
                        }
                        outfile.close();
                    }
                    break;
                }
            }
            if (key == 'e' || key == 'E')
            {
                gotoxy(MAPWIDTH + 8, 17);
                cout << "      ";
                gotoxy(MAPWIDTH + 8, 17);
                cin >> x >> y;
                gotoxy(x * 2 + 2, y + 1);
                cout << "██";
                gotoxy(MAPWIDTH, 0);
                wall[y * wallX + x] = 1;
            }
            if (key == 'w' || key == 'W' || key == 'a' || key == 'A' || key == 's' || key == 'S' || key == 'd' || key == 'D')
            {
                switch (key)
                {
                case 'd':
                case 'D':
                    p = Point(x * 2 + 2, y + 1).getRight();
                    break;
                case 'w':
                case 'W':
                    p = Point(x * 2 + 2, y + 1).getUp();
                    break;
                case 's':
                case 'S':
                    p = Point(x * 2 + 2, y + 1).getDown();
                    break;
                case 'a':
                case 'A':
                    p = Point(x * 2 + 2, y + 1).getLeft();
                    break;
                default:
                    break;
                }
                gotoxy(p);
                cout << "██";
                gotoxy(MAPWIDTH, 0);
                y = p.getY() - 1;
                x = p.getX() / 2 - 1;
                wall[y * wallX + x] = 1;
                //测试数据
                // gotoxy(0, MAPHEIGHT);
                // for (int i = 0; i <= wallY;i++){
                //     for (int j = 0; j <= wallX;j++){
                //         cout << wall[wallX * i + j] << " ";
                //     }
                //     cout << endl;
                // }
            }
        }
    }
    fflush(stdin);
    menu();
}
//游戏初始化地图
void drawMap()//⊙: 食物  ██:蛇身
{
    srand((unsigned int)time(NULL)); //随机函数种子

    //圈地
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //设置三色相加 白色
    for (int i = 0; i < MAPHEIGHT; i++)
    {
        gotoxy(0, i);
        cout << "██";
        gotoxy(MAPWIDTH - 2, i);
        cout << "██";
    }
    for (int i = 2; i < MAPWIDTH - 2; i += 2)
    {
        gotoxy(i, 0);
        cout << "██";
        gotoxy(i, MAPHEIGHT - 1);
        cout << "██";
    }
    //读取地图文件
    fstream infile;
    infile.open("map.dat", ios::in);
    //文件不存在则跳过
    //地图文件与配置地图大小不符或者不符合规范,读取地图过程将报错
    if (infile)
    {
        wall = new int[(wallX + 1) * (wallY + 1)];
        char c;
        int i = 0;
        //循环读取文件
        while (!infile.eof())
        {
            infile >> c;
            wall[i++] = c - '0';
        }
        for (int i = 0; i <= wallY; i++)
        {
            for (int j = 0; j <= wallX; j++)
            {
                if (wall[wallX * i + j])
                {
                    gotoxy(j * 2 + 2, i + 1);
                    cout << "██";
                }
            }
        }
    }
    infile.close();

    //画蛇
    snake.key = s.key;
    snake.setPoint(p);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
    //初始三节身体
    for (int k = 0; k < 3; k++)
    {
        gotoxy(snake.getPoint());
        cout << "██";
        snake.headMove();
    }
    gotoxy(snake.getPoint());
    cout << "██";

    //画食物
    creatFood(true);
    //重置因画食物修改的变量
    snake.bodyLength--;
    changeFlag = 0;

    //画提示和分数信息
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //设置颜色为绿色
    gotoxy(MAPWIDTH + 2, 2);
    //横向
    cout << "****************************************";
    gotoxy(MAPWIDTH + 2, 20);
    cout << "****************************************";
    //纵向
    for (int i = 0; i < 18; i++)
    {
        gotoxy(MAPWIDTH + 41, i + 3);
        cout << '*';
        gotoxy(MAPWIDTH + 2, i + 3);
        cout << '*';
    }
    gotoxy(MAPWIDTH + 17, 3);
    cout << "贪吃蛇游戏";
    gotoxy(MAPWIDTH + 11, 5);
    cout << "当前分数:";
    gotoxy(MAPWIDTH + 20, 5);
    cout << 0;
    gotoxy(MAPWIDTH + 11, 7);
    cout << "时间间隔:";
    gotoxy(MAPWIDTH + 20, 7);
    cout << speed;
    gotoxy(MAPWIDTH + 11, 9);
    cout << "当前蛇的长度:";
    gotoxy(MAPWIDTH + 24, 9);
    cout << snake.bodyLength + 1;//身体长度加头
    gotoxy(MAPWIDTH + 11, 11);
    cout << "蛇的最大长度:";
    gotoxy(MAPWIDTH + 24, 11);
    cout << snake.maxLength;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE); //设置青色
    gotoxy(MAPWIDTH + 6, 15);
    cout << "游戏规则:";
    gotoxy(MAPWIDTH + 8, 16);
    cout << "玩家使用'W'操纵蛇转向";
    gotoxy(MAPWIDTH + 13, 17);
    cout << "'A''S''D'";
    gotoxy(MAPWIDTH + 8, 18);
    cout << "按'Q'可以暂停";
    gotoxy(MAPWIDTH + 8, 19);
    cout << "蛇头撞上蛇身或者墙壁游戏结束";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
}
#endif
