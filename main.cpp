/*
 * @Description: 程序入口
 * @Author: skaarf
 * @Date: 2020-06-15 14:30:02
 * @LastEditTime: 2020-06-30 17:46:16
 * @LastEditors: skaarf
 */
#include "menu.cpp" //菜单函数
#include <iostream>
#include <windows.h> //光标设置API
using namespace std;

int main()
{
    menu();
    gotoxy(MAPWIDTH, MAPHEIGHT - 1);
    system("pause");
    return 0;
}
