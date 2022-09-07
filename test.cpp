#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void renderBox(int x, int y, int cols, int rows){
    int finalX = x + cols -1;
    int finalY = y + rows -1;
    
    for(int i = x; i <= finalX; i ++){
        for(int j = y; j <= finalY; j++){
            gotoxy(i,j);
            if(i == x && j == y){
                printf("-");
            }else if(i == x && j != y)
            {
                printf("s");
            }else if(i == finalX && j == finalY)
            {
                printf("x");
            }else if(i == finalX && j == y){
                printf("x");
            }else if( i == finalX && j != y){
                printf("9");
            }else if(i !=x && i != finalX && j == y){
                printf("=");
            }else if(i != x && i != finalX && j == finalY){
                printf("*");
            }   
        }
    }
    
}

void renderLayout(){
    renderBox(0,0,140,40);
    renderBox(1,1, 68,38);
    renderBox(70,1, 68,38); 
}

void renderButton(int x, int y, char *message){
    gotoxy(x+2, y+2);
    printf("%s", message);
    
    renderBox(x,y, strlen(message) + 5,5);
}

int main(){
    system("mode con:cols=140 lines=40");
    renderLayout();
    // renderButton(10,10, "Wesley");
    // renderButton(20,10, "Ola");
    // renderButton(30,10, "testando");
    char test;
    renderBox(10,10,6,4);
    gotoxy(12,12);
    test = getch();
    printf("%c", test);

    renderBox(10,20,6,4);
    gotoxy(12,22);
    test = getch();
    printf("%c", test);

    gotoxy(3,3);
    

    getch();

    
    return 0;
}