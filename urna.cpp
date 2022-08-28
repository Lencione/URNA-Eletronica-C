#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// STRUCTS
typedef struct{
    int number;
    char *name;
} Person;

typedef struct{
    int number;
    char *name;
    Person president;
    Person governor;
    Person senator;
    Person federal;
    Person state;
} Entourage;

typedef struct{
    int ra;
    int president;
    int governor;
    int senator;
    int federal;
    int state;
} Voter;


// CONSTANTES - TAMANHO DE TELA
#define COLS 140
#define ROWS 40

// FUNCOES
void gotoxy(int x, int y);
void renderBorder(int x, int y, int cols, int rows);
void renderButton(int x, int y, char *text);
void createButtons(int x, int y);
void renderLayout();

int main(){
    
    system("color F0");
    system("mode con:cols=140 lines=45");
    
    renderLayout();
    
    gotoxy(1,42);

    return 0;
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void renderBorder(int x, int y, int rows, int cols){
    int finalx = x + cols-1;
    int finaly = y + rows-1;

    for(int i = x; i <= finalx; i++){
        for(int j = y; j<= finaly; j++){
            if(i == x || j == y || i == finalx || j == finaly){
                gotoxy(i, j);
                if(i == x && j == y){
                    //Canto superior esquerdo
                    printf("%c", 201);
                }else if(i == x && j == finaly){
                    // Canto inferior esquerdo
	                printf("%c", 200);
                }else if(i == finalx && j == y){
                     // Canto superior direito
                    printf("%c", 187);
                }else if(i == finalx && j == finaly){
                    // Canto inferior direito
                    printf("%c", 188);
                }else if(i == x || i == finalx){
                    // Linha vertical
                    printf("%c", 186);	
                }else{
                    // Linha horizontal
                    printf("%c", 205);
                }
            }
        }
    }
}

void renderButton(int x, int y, char *text){
    gotoxy(x+3,y+2);
    printf("%s", text);
    renderBorder(x,y, 5,strlen(text)+6);
}
void createButtons(int x, int y){
    char *numbers[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    
    // Linhas
    for(int i = 0; i < 3; i++){
        // Colunas
        for(int j = 0; j < 3; j++){
            // Posição x + 8*j (Somar 8 a cada iteração do for) -> espaçamento horizontal dos botoes
            // Posição y + 5*i (Somar 5 a cada iteração do for) -> espaçamento vertical dos botoes
            // numbers[(i*3)+j] -> Somando um a cada iteração do for, ex: (0 * 3) + 0 = 0, (0 * 3) + 1 = 1, (0 * 3) + 2 = 2, (1 * 3) + 0 = 3, ...
            renderButton(x + (8*j), y + (5*i), numbers[(i*3)+j]);
        }
    }

    // Criar o botão de número "0"
    renderButton(x + (8*1), y + (5*3), numbers[9]);
    renderButton(x + (8*0)-7, y + (5*4), "BRANCO");
    renderButton(x + (8*1)-3, y + (5*4), "CORRIGE");
    renderButton(x + (8*2)+2, y + (5*4), "CONFIRMA");
}

void renderLayout(){
    //Criar borda total
    renderBorder(0, 0, ROWS, COLS);

    // Criar borda da área de voto
    renderBorder(1, 7, 32, 85);
    
    // Criar borda dos candidatos
    renderBorder(1, 1, 6, 138);

    // Criar borda da área de digitos
    renderBorder(86, 7, 32, 53);

    // Criar borda JUSTICA ELEITORAL    
    renderBorder(87, 8, 3, 51);
    gotoxy(103,9);
    printf("JUSTICA ELEITORAL");
    
    // Criar botoes
    createButtons(100,12);
}


