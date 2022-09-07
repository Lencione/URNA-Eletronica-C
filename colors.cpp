#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

// INCLUIR NO COMPILADOR O COMANDO -lwinmm




int main(){
    // PlaySound(TEXT("cavalo.mp3"),0,0);
    PlaySoundA((LPCSTR) "C:\\Users\\User\\Documents\\Codes\\URNA\\cavalo.wav", NULL, SND_FILENAME | SND_ASYNC);
    getch();
    return 0;
}