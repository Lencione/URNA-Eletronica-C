#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// CONSTANTES - TAMANHO DE TELA
#define COLS 140
#define ROWS 40

typedef struct
{
    char *number;
    char *name;
    char *entourage;
    char type;
    int votes;
} Candidate;

typedef struct
{
    char ra[8];
} Voter;



// FUNCOES
void gotoxy(int x, int y);

void hideCursorPosition();
void renderBorder(int x, int y, int cols, int rows);
void renderButton(int x, int y, char *text);
void createButtons(int x, int y);
void renderLayout();
Candidate *createCandidates(Candidate *candidates);
void resetCandidateList();
void renderCandidateList(Candidate *candidates, char type);
char* requestNumbers(int length, char* message);
void resetVoteArea();
void renderInformation(char *message);
void renderCandidate(Candidate *candidates, int index);
void renderEnd();
int votesCompare (const void *x, const void *y);
void showRank(Candidate *candidates, int qtt);


int main()
{
    Candidate ent[30];
    Candidate *candidates = createCandidates(ent);
    char ra[8];
    char number[5];
    Voter voters[100];
    int qttNumbers = 0; // Quantidade de numeros para voto
    char voteType = '0'; // Tipo de voto
    int i = 0; // Contador de eleitores
    bool existsRa; // Verifica se RA já foi digitado anteriormente
    char *phrase;  // Frase para Exibição
    char voteConfirmation = 'n';
    int candidateIndex;

    system("color F0");
    system("mode con:cols=140 lines=40");

    renderLayout();
    
    while(1){
    	resetCandidateList();   	
		resetVoteArea();
        // Variavel de verificação para saber se um RA já foi digitado ou não
		existsRa = true;
		do{
			resetVoteArea();
			strcpy(ra,requestNumbers(8, "Digite seu RA"));
            if(strcmp(ra, "exit") == 0){
                break;
            }
			if( i >= 0){
				for(int j = 0; j <=i ; j++){
					if(strcmp(ra, voters[j].ra) == 0 ){
						existsRa = true;
						renderInformation("RA ja existe no banco de dados, voce ja votou! Digite outro RA.");
						Sleep(2000);
                        break;
					}else{
						existsRa = false;
					}
				}	
			}
		}while(existsRa == true);
        // Resetando variavel existsRa para a próxima iteração do loop
		existsRa = true;

        // Saindo para contagem dos votos!
        if(strcmp(ra, "exit") == 0){
            break;
        }

		// Copiando o valor da variavel temporaria RA para a struct voters.ra (eleitor)
		strcpy(voters[i].ra, ra);

        // Criar rotina para computar os votos:
        qttNumbers = 0;
        voteType = '0';
        for(int j = 0; j < 5; j++)
        {
            // Definir parametros para a função de chamar a funcao de voto
            if( j == 0){
                qttNumbers = 4;
                voteType = 'f';
                phrase = "Deputado Federal";
            }else if( j == 1){
                qttNumbers = 5;
                voteType = 'e';
                phrase = "Deputado Estadual";
            }else if( j == 2){
                qttNumbers = 3;
                voteType = 's';
                phrase = "Senador";
            }else if( j == 3){
                qttNumbers = 2;
                voteType = 'g';
                phrase = "Governador";
            }else{
                qttNumbers = 2;
                voteType = 'p';
                phrase = "Presidente";
            }

            // Pedir confirmação do voto
            voteConfirmation = 'n';
            do{
                candidateIndex = -1;
                resetCandidateList();
                renderCandidateList(candidates, voteType);
                resetVoteArea();
                strcpy(number, requestNumbers(qttNumbers, phrase));

                // Pegando o INDEX do candidato
                for(int k = 0; k < 25; k++){
                    if(candidates[k].type == voteType){
                        if(strcmp(number, candidates[k].number) == 0){
                            candidateIndex = k;
                            break;
                        }
                    }
                }
                // Se o candidato for NULO, define o index para o tipo de candidato (Senador, Estadual, Governador...)
                if(candidateIndex == -1){
                    for(int k = 25; k < 30; k++){
                        if(candidates[k].type == voteType){
                            candidateIndex = k;
                        }
                    }
                }

                renderCandidate(candidates, candidateIndex);
                renderInformation("Voce confirma o voto? (s/n)");
                while(1){
                    voteConfirmation = getch();
                    if (voteConfirmation == 's' || voteConfirmation == 'S' || voteConfirmation == 'n' || voteConfirmation == 'N'){
                        break;
                    }
                }
                
            }while(voteConfirmation != 's');
            candidates[candidateIndex].votes++;
        }

        renderEnd();
		
        i++;
	}

    resetCandidateList();
    resetVoteArea();
    qsort(candidates, 30, sizeof(Candidate), votesCompare);
   
    showRank(candidates, 30);
    renderInformation("Digite (s) para sair.");

    while(1){
        voteConfirmation = getch();
        if(voteConfirmation == 's' || voteConfirmation == 'S'){
            break;
        }
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

void hideCursorPosition(){
	HANDLE hOut;
    CONSOLE_CURSOR_INFO cCursorInfo;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cCursorInfo.dwSize = 10;
    cCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cCursorInfo);
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
    hideCursorPosition();
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

Candidate *createCandidates(Candidate *candidates)
{
    candidates[0].number = "11";
    candidates[0].name = "SUPERMAN";
    candidates[0].entourage = "DC";
    candidates[0].type = 'p';
    candidates[0].votes = 0;

    candidates[1].number = "11";
    candidates[1].name = "BATMAN";
    candidates[1].entourage = "DC";
    candidates[1].type = 'g';
    candidates[1].votes = 0;

    candidates[2].number = "111";
    candidates[2].name = "MULHER MARAVILHA";
    candidates[2].entourage = "DC";
    candidates[2].type = 's';
    candidates[2].votes = 0;
    
    candidates[3].number = "1111";
    candidates[3].name = "LANTERNA VERDE";
    candidates[3].entourage = "DC";
    candidates[3].type = 'f';
    candidates[3].votes = 0;
    
    candidates[4].number = "11111";
    candidates[4].name = "FLASH";
    candidates[4].entourage = "DC";
    candidates[4].type = 'e';
    candidates[4].votes = 0;

    // MARVEL
    candidates[5].number = "22";
    candidates[5].name = "CAPITAO AMERICA";
    candidates[5].entourage = "MARVEL";
    candidates[5].type = 'p';
    candidates[5].votes = 0;

    candidates[6].number = "22";
    candidates[6].name = "HOMEM FERRO";
    candidates[6].entourage = "MARVEL";
    candidates[6].type = 'g';
    candidates[6].votes = 0;

    candidates[7].number = "222";
    candidates[7].name = "CAPITA MARVEL";
    candidates[7].entourage = "MARVEL";
    candidates[7].type = 's';
    candidates[7].votes = 0;
    
    candidates[8].number = "2222";
    candidates[8].name = "HULK";
    candidates[8].entourage = "MARVEL";
    candidates[8].type = 'f';
    candidates[8].votes = 0;
    
    candidates[9].number = "22222";
    candidates[9].name = "HOMEM ARANHA";
    candidates[9].entourage = "MARVEL";
    candidates[9].type = 'e';
    candidates[9].votes = 0;

    // THE BOYS
    candidates[10].number = "33";
    candidates[10].name = "CAPITAO PATRIA";
    candidates[10].entourage = "THE BOYS";
    candidates[10].type = 'p';
    candidates[10].votes = 0;

    candidates[11].number = "33";
    candidates[11].name = "BRUTO";
    candidates[11].entourage = "THE BOYS";
    candidates[11].type = 'g';
    candidates[11].votes = 0;

    candidates[12].number = "333";
    candidates[12].name = "LUZ ESTRELA";
    candidates[12].entourage = "THE BOYS";
    candidates[12].type = 's';
    candidates[12].votes = 0;
    
    candidates[13].number = "3333";
    candidates[13].name = "BLACK NOIR";
    candidates[13].entourage = "THE BOYS";
    candidates[13].type = 'f';
    candidates[13].votes = 0;
    
    candidates[14].number = "33333";
    candidates[14].name = "SOLDIER BOY";
    candidates[14].entourage = "THE BOYS";
    candidates[14].type = 'e';
    candidates[14].votes = 0;

    // SIMPSONS
    candidates[15].number = "44";
    candidates[15].name = "HOMER";
    candidates[15].entourage = "SIMPSONS";
    candidates[15].type = 'p';
    candidates[15].votes = 0;

    candidates[16].number = "44";
    candidates[16].name = "MARGE";
    candidates[16].entourage = "SIMPSONS";
    candidates[16].type = 'g';
    candidates[16].votes = 0;

    candidates[17].number = "444";
    candidates[17].name = "BART";
    candidates[17].entourage = "SIMPSONS";
    candidates[17].type = 's';
    candidates[17].votes = 0;
    
    candidates[18].number = "4444";
    candidates[18].name = "LISA";
    candidates[18].entourage = "SIMPSONS";
    candidates[18].type = 'f';
    candidates[18].votes = 0;
    
    candidates[19].number = "44444";
    candidates[19].name = "MAGGIE";
    candidates[19].entourage = "SIMPSONS";
    candidates[19].type = 'e';
    candidates[19].votes = 0;

     // NULO
    candidates[20].number = "00";
    candidates[20].name = "BRANCO";
    candidates[20].entourage = "BRANCO";
    candidates[20].type = 'p';
    candidates[20].votes = 0;

    candidates[21].number = "00";
    candidates[21].name = "BRANCO";
    candidates[21].entourage = "BRANCO";
    candidates[21].type = 'g';
    candidates[21].votes = 0;

    candidates[22].number = "000";
    candidates[22].name = "BRANCO";
    candidates[22].entourage = "BRANCO";
    candidates[22].type = 's';
    candidates[22].votes = 0;
    
    candidates[23].number = "0000";
    candidates[23].name = "BRANCO";
    candidates[23].entourage = "BRANCO";
    candidates[23].type = 'f';
    candidates[23].votes = 0;
    
    candidates[24].number = "00000";
    candidates[24].name = "BRANCO";
    candidates[24].entourage = "BRANCO";
    candidates[24].type = 'e';
    candidates[24].votes = 0;

     // BRANCO
    candidates[25].number = "99";
    candidates[25].name = "NULO";
    candidates[25].entourage = "NULO";
    candidates[25].type = 'p';
    candidates[25].votes = 0;

    candidates[26].number = "99";
    candidates[26].name = "NULO";
    candidates[26].entourage = "NULO";
    candidates[26].type = 'g';
    candidates[26].votes = 0;

    candidates[27].number = "999";
    candidates[27].name = "NULO";
    candidates[27].entourage = "NULO";
    candidates[27].type = 's';
    candidates[27].votes = 0;
    
    candidates[28].number = "9999";
    candidates[28].name = "NULO";
    candidates[28].entourage = "NULO";
    candidates[28].type = 'f';
    candidates[28].votes = 0;
    
    candidates[29].number = "99999";
    candidates[29].name = "NULO";
    candidates[29].entourage = "NULO";
    candidates[29].type = 'e';
    candidates[29].votes = 0;

    return candidates;
}

void resetCandidateList(){
    for(int i = 2; i < 138; i++){
        for(int j = 2; j <= 5; j++){
            gotoxy(i,j);
            printf(" ");
        }
    }
}

void renderCandidateList(Candidate *candidates, char type)
{
    resetCandidateList();
    gotoxy(60, 2);


    switch (type)
    {
        case 'p':
            printf("CANDIDATOS A PRESIDENTE");
            break;
        case 'g':
            printf("CANDIDATOS A GOVERNADOR");
            break;
        case 'f':
            printf("CANDIDATOS A DEPUTADO FEDERAL");
            break;
        case 's':
            printf("CANDIDATOS A SENADOR");
            break;
        
        default:
            printf("CANDIDATOS A DEPUTADO ESTADUAL");
            break;
    }
    int j = 0;
    for (int i = 0; i < 20; i++)
    {
        if(candidates[i].type == type){
            gotoxy(2 + (j * 30), 3);
            printf("%s", candidates[i].entourage);
            gotoxy(2 + (j * 30), 4);
            printf("%s", candidates[i].name);
            gotoxy(2 + (j * 30), 5);
            printf("Numero: %s", candidates[i].number);
            j++;
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
			if(length == 8){
                if(let == 4){
                    // CTRL+D PRESSIONADO, SAI PARA CONTAR OS VOTOS
                    return "exit";
                }
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


void renderInformation(char *message){
    gotoxy(3,35);
    printf("%s", message);
}

void renderCandidate(Candidate *candidates, int index){
    gotoxy(3,20);
    if(index == -1){
        printf("Canditado: NULO");
    }else{
        printf("Candidato: %s - Partido: %s", candidates[index].name, candidates[index].entourage);
    }
} 

void renderEnd(){
    resetCandidateList();
    resetVoteArea();
    gotoxy(28,18);
    printf("CARREGANDO");
    for(int i = 0; i < 20; i++){
        gotoxy(28+i,19);
        printf("%c", 219);
        Sleep(400);
    }
    resetVoteArea();
    gotoxy(28,18);
    printf("%c%c%c %c %c%c %c%c",219,223,223,219,219,220,220,219);
    gotoxy(28,19);
    printf("%c%c%c %c %c %c %c",219,223,223,219,219,223,219);
    gotoxy(28,20);
    printf("%c   %c %c   %c",219,219,219,219);
    Sleep(3000);
    resetVoteArea();
}

int votesCompare (const void *x, const void *y) {
    int first = ((Candidate *)x)->votes;
    int second = ((Candidate *)y)->votes;
    return (second - first);
}

void showRank(Candidate *candidates, int qtt){
    gotoxy(3,8);
    printf("Presidente");
    int x = 2;
    for(int i = 0; i < qtt; i++){
        if(candidates[i].type == 'p'){
            gotoxy(3,8+x);
            printf("[%d] - %s", candidates[i].votes, candidates[i].name);
            x++;
        }
    }

    gotoxy(28,8);
    printf("Governador");
    x = 2;
    for(int i = 0; i < qtt; i++){
        if(candidates[i].type == 'g'){
            gotoxy(28,8+x);
            printf("[%d] - %s", candidates[i].votes, candidates[i].name);
            x++;
        }
    }

    gotoxy(53,8);
    printf("Senador");
    x = 2;
    for(int i = 0; i < qtt; i++){
        if(candidates[i].type == 's'){
            gotoxy(53,8+x);
            printf("[%d] - %s", candidates[i].votes, candidates[i].name);
            x++;
        }
    }

    gotoxy(3,20);
    printf("Deputado Federal");
    x = 2;
    for(int i = 0; i < qtt; i++){
        if(candidates[i].type == 'f'){
            gotoxy(3,20+x);
            printf("[%d] - %s", candidates[i].votes, candidates[i].name);
            x++;
        }
    }

    gotoxy(28 ,20);
    printf("Deputado Estadual");
    x = 2;
    for(int i = 0; i < qtt; i++){
        if(candidates[i].type == 'e'){
            gotoxy(28 ,20+x);
            printf("[%d] - %s", candidates[i].votes, candidates[i].name);
            x++;
        }
    }
}