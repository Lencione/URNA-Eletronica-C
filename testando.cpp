#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
    DWORD prev_mode;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS |
                               (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    while (1)
    {
        if (GetKeyState(VK_LBUTTON) < 0)
        {
            Sleep(10);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            printf("cliquei");
        }
    }
}
