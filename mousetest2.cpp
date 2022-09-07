#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winuser.h>
#include <conio.h>

COORD getMousexy()
{
    POINT pt; 
    GetCursorPos(&pt);
    HWND hwnd = GetConsoleWindow();

    RECT rc;
    GetClientRect(hwnd, &rc);
    ScreenToClient(hwnd, &pt);

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO inf;
    GetConsoleScreenBufferInfo(hout, &inf);

    COORD coord = { 0, 0 };
    coord.X = MulDiv(pt.x, inf.srWindow.Right, rc.right);
    coord.Y = MulDiv(pt.y, inf.srWindow.Bottom, rc.bottom);
    return coord;
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main() 
{
    
    while (1)
    {
        system("cls");
        
        COORD coord = getMousexy();
        gotoxy(coord.X, coord.Y);

		printf("x: %d y: %d", coord.X, coord.Y);		 
    }
}