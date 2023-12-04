#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h> 
#include <windows.h>
#pragma comment(lib, "winmm.lib")

#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int main() {
    char* combo = NULL;
    int maxSize = 10;
    unsigned char input;
    int i = 0;
    int skillMatched = 0;

    char skill_1[4] = { UP, DOWN, 'a', '\0' };
    char skill_2[4] = { RIGHT, DOWN, LEFT, '\0' };
    char skill_3[4] = { LEFT, DOWN, RIGHT, '\0' };

    combo = (char*)malloc(maxSize); 

    ULONGLONG lastKeyPressTime = 0;

    while (1) {
        if (_kbhit() != 0) {

            input = _getch();

            if (input == 224) {
                input = _getch();
                combo[i] = input;
                i++;

                if (i >= maxSize) {
                    maxSize += 10;
                    combo = (char*)realloc(combo, maxSize); 
                }
            }
            else if (input == ESC) {
                free(combo);
                return 0;
            }
            else {
                combo[i] = input;
                i++;

                if (i >= maxSize) {
                    maxSize += 10;
                    combo = (char*)realloc(combo, maxSize); 
                }
            }

            lastKeyPressTime = GetTickCount64();
        }

        ULONGLONG endTime = GetTickCount64();

        if (endTime - lastKeyPressTime >= 300) {
            if (i > 0) {
                printf("잘못된 콤보\n");
                memset(combo, 0, maxSize); 
                i = 0; 
            }
        }
        else {
            if (strcmp(combo, skill_1) == 0) { 
                printf("아도겐!= o\n");
                memset(combo, 0, maxSize);
                i = 0; 
            }
            else if (strcmp(combo, skill_2) == 0) { 
                printf("주먹!!= o\n");
                memset(combo, 0, maxSize);
                i = 0; 
            }

            else if (strcmp(combo, skill_3) == 0) { 
                printf("발!!!= o\n");
                memset(combo, 0, maxSize);
                i = 0; 
            }
        }

    }

    free(combo); 

    return 0;
}

