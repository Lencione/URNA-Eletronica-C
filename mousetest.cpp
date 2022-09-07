#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winuser.h>

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
	POINT pt;
	GetCursorPos(&pt);
	HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);
    
	
	
	
	while(1){
		GetCursorPos(&pt);
		ScreenToClient(myconsole, &pt);
		gotoxy(10,10);
		printf("[%d] [%d]      ", pt.x, pt.y);
		// system("cls");

		if(GetAsyncKeyState(0x01)){
			printf("Apertei o mouse!");
		}
		if(GetAsyncKeyState(0x02)){
			printf("Apertei o mouse 2!");
		}
	}
}
