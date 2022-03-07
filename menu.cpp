/*
 * @Description: 菜单函数
 * @Author: skaarf
 * @Date: 2020-06-30 17:30:00
 * @LastEditTime: 2020-06-30 19:21:45
 * @LastEditors: skaarf
 */
#include "gamestart.cpp"
#include <iostream>
#include <windows.h> //光标设置API

//显示菜单
void menu()
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); //设置蓝色
    gotoxy(2, 2);
    cout << "****************************************";
    gotoxy(2, 20);
    cout << "****************************************";
    for (int i = 0; i < 18; i++)
    {
        gotoxy(41, i + 3);
        cout << '*';
        gotoxy(2, i + 3);
        cout << '*';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE); //设置青色
    gotoxy(18, 3);
    cout << "贪吃蛇游戏";
    gotoxy(11, 5);
    cout << "1.开始游戏";
    gotoxy(11, 7);
    cout << "2.地图设计";
    gotoxy(11, 9);
    cout << "3.退出游戏";
    gotoxy(11, 22);
    int choose;
    cout << "请选择:";
    cin >> choose;
    system("cls");
    switch (choose)
    {
    case 1:
        startGame();
        break;
    case 2:
        map();
        break;
    case 3:
    default:
        exit(0);
    }
}
