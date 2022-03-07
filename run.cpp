/*
 * @Description:
 * @Author: skaarf
 * @Date: 2020-07-03 15:37:29
 * @LastEditTime: 2020-08-10 22:54:40
 * @LastEditors: skaarf
 */
#include<stdio.h>
#include <Windows.h>

int nSum = 0;
int NUMBER = 80;

DWORD WINAPI Accumulate(LPVOID lpParam)
{
    for (int i = 0; i < NUMBER; i++)
    {
        int iCopy = nSum;
        nSum = iCopy + 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    HANDLE hThread[3];
    hThread[0] = CreateThread(NULL, 0, Accumulate, NULL, 0, NULL);
    hThread[1] = CreateThread(NULL, 0, Accumulate, NULL, 0, NULL);
    hThread[2] = CreateThread(NULL, 0, Accumulate, NULL, 0, NULL);
    WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
    printf("  nSum = %d", nSum);
    return 0;
}
