#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#define COLS 200
#define ROWS 45
void gotoxy(int x, int y);
void createBorders(int cols, int rows);

int main(){
    
    system("color 70");
    system("mode con:cols=200 lines=50");
    createBorders(ROWS, COLS);
    // return 0;

    int x = 0;
    do{
        printf("%d", x);
        x++;
    }while(x < 10);
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void createBorders(int rows, int cols){
    printf("%d %d", rows, cols);
    for(int i = 0; i< rows; i++){
        for(int j = 0; j < cols; j++){
            if(i == 0 || j == 0 || i == rows-1 || j == cols -1){
                gotoxy(j,i);
                if(i == 0 && j == 0){
                    printf("%c", 201);
                }else if(i == rows-1 && j == 0){
	                printf("%c", 200);
                }else if(i == 0 && j == cols-1){
                    printf("%c", 187);
                }else if(i == rows -1 && j == cols-1){
                    printf("%c", 188);
                }else if(j == 0 || j == cols-1){
                    printf("%c", 186);	
                }else{
                    printf("%c", 205);
                }
            }
        }
    }
}

