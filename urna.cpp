#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// CONSTANTES - TAMANHO DE TELA
#define COLS 140
#define ROWS 40

// STRUCTS
typedef struct
{
    char *number;
    char *name;
} Person;

typedef struct
{
    char *number;
    char *name;
    Person president;
    Person governor;
    Person senator;
    Person federal;
    Person state;
} Entourage;

typedef struct
{
    char ra[8];
    char *president;
    char *governor;
    char *senator;
    char *federal;
    char *state;
} Voter;

// FUNCOES
void gotoxy(int x, int y);
void renderBorder(int x, int y, int cols, int rows);
void renderButton(int x, int y, char *text);
void createButtons(int x, int y);
void renderLayout();
Entourage *createCandidates(Entourage *entourages);
void resetCandidateList();
void renderCandidateList(Entourage *candidates, char *type);
char* requestNumbers(int length, char* message);
void resetVoteArea();

int main()
{
    Entourage ent[4];
    Entourage *candidates = createCandidates(ent);
    char ra[8];
    char *number;
    Voter voters[100];

    
    system("color F0");
    system("mode con:cols=140 lines=40");

    renderLayout();
    
    // Contador de eleitores (voters)
	int i = 0;
	int opt = 0;
    while(opt == 0){
    	resetCandidateList();   	
		
		bool existsRa = true;
		do{
			strcpy(ra,requestNumbers(8, "Digite seu RA"));
			resetVoteArea();
			if( i > 0){
				for(int j = 0; j < i; j++){
					if(strcmp(ra, voters[i].ra) == 0 ){
						existsRa = true;
						gotoxy(3,20);			
						printf("RA ja existe no banco de dados, voce ja votou! Digite outro RA.");
						Sleep(1);
					}else{
						existsRa = false;
					}
				}	
			}else{
				existsRa = false;
			}
		}while(existsRa == true);
		existsRa = true;
		// Copiando o valor da variavel temporaria RA para a struct voters.ra (eleitor)
	
		strcpy(voters[0].ra, ra);
		gotoxy(25,25);
		printf("%s", voters[0].ra);
		
		opt = getch();
		
		resetVoteArea();
	}
	

    return 0;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void renderBorder(int x, int y, int rows, int cols)
{
    int finalx = x + cols - 1;
    int finaly = y + rows - 1;

    for (int i = x; i <= finalx; i++)
    {
        for (int j = y; j <= finaly; j++)
        {
            if (i == x || j == y || i == finalx || j == finaly)
            {
                gotoxy(i, j);
                if (i == x && j == y)
                {
                    // Canto superior esquerdo
                    printf("%c", 201);
                }
                else if (i == x && j == finaly)
                {
                    // Canto inferior esquerdo
                    printf("%c", 200);
                }
                else if (i == finalx && j == y)
                {
                    // Canto superior direito
                    printf("%c", 187);
                }
                else if (i == finalx && j == finaly)
                {
                    // Canto inferior direito
                    printf("%c", 188);
                }
                else if (i == x || i == finalx)
                {
                    // Linha vertical
                    printf("%c", 186);
                }
                else
                {
                    // Linha horizontal
                    printf("%c", 205);
                }
            }
        }
    }
}

void renderButton(int x, int y, char *text)
{
    gotoxy(x + 3, y + 2);
    printf("%s", text);
    renderBorder(x, y, 5, strlen(text) + 6);
}
void createButtons(int x, int y)
{
    char *numbers[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

    // Linhas
    for (int i = 0; i < 3; i++)
    {
        // Colunas
        for (int j = 0; j < 3; j++)
        {
            // Posição x + 8*j (Somar 8 a cada iteração do for) -> espaçamento horizontal dos botoes
            // Posição y + 5*i (Somar 5 a cada iteração do for) -> espaçamento vertical dos botoes
            // numbers[(i*3)+j] -> Somando um a cada iteração do for, ex: (0 * 3) + 0 = 0, (0 * 3) + 1 = 1, (0 * 3) + 2 = 2, (1 * 3) + 0 = 3, ...
            renderButton(x + (8 * j), y + (5 * i), numbers[(i * 3) + j]);
        }
    }

    // Criar o botão de número "0"
    renderButton(x + (8 * 1), y + (5 * 3), numbers[9]);
    renderButton(x + (8 * 0) - 7, y + (5 * 4), "BRANCO");
    renderButton(x + (8 * 1) - 3, y + (5 * 4), "CORRIGE");
    renderButton(x + (8 * 2) + 2, y + (5 * 4), "CONFIRMA");
}

void renderLayout()
{
    // Criar borda total
    renderBorder(0, 0, ROWS, COLS);

    // Criar borda da área de voto
    renderBorder(1, 7, 32, 85);

    // Criar borda dos candidatos
    renderBorder(1, 1, 6, 138);

    // Criar borda da área de digitos
    renderBorder(86, 7, 32, 53);

    // Criar borda JUSTICA ELEITORAL
    renderBorder(87, 8, 3, 51);
    gotoxy(103, 9);
    printf("JUSTICA ELEITORAL");

    // Criar botoes
    createButtons(100, 12);
}

Entourage *createCandidates(Entourage *entourages)
{
    entourages[0].number = "11";
    entourages[0].name = "DC";
    entourages[0].president.number = "11";
    entourages[0].president.name = "SUPERMAN";
    entourages[0].governor.number = "11";
    entourages[0].governor.name = "BATMAN";
    entourages[0].senator.number = "111";
    entourages[0].senator.name = "MULHER MARAVILHA";
    entourages[0].federal.number = "1111";
    entourages[0].federal.name = "LANTERNA VERDE";
    entourages[0].state.number = "11111";
    entourages[0].state.name = "FLASH";

    entourages[1].number = "22";
    entourages[1].name = "MARVEL";
    entourages[1].president.number = "22";
    entourages[1].president.name = "CAPITAO AMERICA";
    entourages[1].governor.number = "22";
    entourages[1].governor.name = "HOMEM FERRO";
    entourages[1].senator.number = "222";
    entourages[1].senator.name = "CAPITA MARVEL";
    entourages[1].federal.number = "2222";
    entourages[1].federal.name = "HULK";
    entourages[1].state.number = "22222";
    entourages[1].state.name = "HOMEM ARANHA";

    entourages[2].number = "33";
    entourages[2].name = "THE BOYS";
    entourages[2].president.number = "33";
    entourages[2].president.name = "CAPITAO PATRIA";
    entourages[2].governor.number = "33";
    entourages[2].governor.name = "BRUTO";
    entourages[2].senator.number = "333";
    entourages[2].senator.name = "LUZ ESTRELA";
    entourages[2].federal.number = "3333";
    entourages[2].federal.name = "BLACK NOIR";
    entourages[2].state.number = "3333";
    entourages[2].state.name = "SOLDIER BOY";

    entourages[3].number = "44";
    entourages[3].name = "SIMPSONS";
    entourages[3].president.number = "44";
    entourages[3].president.name = "HOMER";
    entourages[3].governor.number = "44";
    entourages[3].governor.name = "MARGE";
    entourages[3].senator.number = "444";
    entourages[3].senator.name = "BARTH";
    entourages[3].federal.number = "4444";
    entourages[3].federal.name = "LISA";
    entourages[3].state.number = "44444";
    entourages[3].state.name = "MAGGIE";

    return entourages;
}

void resetCandidateList(){
    for(int i = 2; i < 138; i++){
        for(int j = 2; j < 5; j++){
            gotoxy(i,j);
            printf(" ");
        }
    }
}

void renderCandidateList(Entourage *candidates, char *type)
{
    resetCandidateList();
    gotoxy(60, 2);

    if (strcmp(type, "president") == 0)
    {
        printf("CANDIDATOS A PRESIDENTE");
        for (int i = 0; i < 4; i++)
        {
        	gotoxy(2 + (i * 30), 3);
        	printf("%s", candidates[i].name);
            gotoxy(2 + (i * 30), 4);
            printf("%s", candidates[i].president.name);
            gotoxy(2 + (i * 30), 5);
            printf("Numero: %s", candidates[i].president.number);
        }
    }
    else if (strcmp(type, "governor") == 0)
    {
        printf("CANDIDATOS A GOVERNADOR");
        for (int i = 0; i < 4; i++)
        {
        	gotoxy(2 + (i * 30), 3);
        	printf("%s", candidates[i].name);
            gotoxy(2 + (i * 30), 4);
            printf("%s", candidates[i].governor.name);
            gotoxy(2 + (i * 30), 5);
            printf("Numero: %s", candidates[i].governor.number);
        }
    }
    else if (strcmp(type, "state") == 0)
    {
        printf("CANDIDATOS A DEPUTADO ESTADUAL");
        for (int i = 0; i < 4; i++)
        {
        	gotoxy(2 + (i * 30), 3);
        	printf("%s", candidates[i].name);
            gotoxy(2 + (i * 30), 4);
            printf("%s", candidates[i].state.name);
            gotoxy(2 + (i * 30), 5);
            printf("Numero: %s", candidates[i].state.number);
        }
    }
    else if (strcmp(type, "senator") == 0)
    {
        printf("CANDIDATOS A SENADOR");
        for (int i = 0; i < 4; i++)
        {
        	gotoxy(2 + (i * 30), 3);
        	printf("%s", candidates[i].name);
            gotoxy(2 + (i * 30), 4);
            printf("%s", candidates[i].senator.name);
            gotoxy(2 + (i * 30), 5);
            printf("Numero: %s", candidates[i].senator.number);
        }
    }
    else
    {
        printf("CANDIDATOS A DEPUTADO ESTADUAL");
        for (int i = 0; i < 4; i++)
        {
        	gotoxy(2 + (i * 30), 3);
        	printf("%s", candidates[i].name);
            gotoxy(2 + (i * 30), 4);
            printf("%s", candidates[i].federal.name);
            gotoxy(2 + (i * 30), 5);
            printf("Numero: %s", candidates[i].federal.number);
        }
    }
}

char* requestNumbers(int length, char* message){
	gotoxy(3,13);
	printf("%s: ", message);
	char numbers[length];
	
    for(int i = 0; i < length; i++){
		renderBorder(3 + (7*i),15,5,7);
	}
	for(int i = 0; i < length; i++){
		char let = 0;
		do{
			gotoxy(6 + (i*7),17);
			let = getch();	
			
			if(let == 4){
				// CTRL+D PRESSIONADO, SAI PARA CONTAR OS VOTOS
				gotoxy(6,25);
				printf("CTRL + D PRESSIONADO");
			}		
		}while(let < 48 || let > 57);
		printf("%c", let);
		numbers[i] = let;
	}
	numbers[length] = '\0';
	gotoxy(25,25);
	
	return numbers;
}
void resetVoteArea(){
	for(int i = 2; i < 84; i++){
		for(int j = 8; j < 38; j++){
			gotoxy(i,j);
			printf(" ");
		}
	}
}