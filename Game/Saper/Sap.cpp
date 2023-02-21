#include <math.h>
#include <locale>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iostream>

#define FIELD_SIZE 4

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

class Game {
    int field[FIELD_SIZE][FIELD_SIZE];
    int id[FIELD_SIZE][FIELD_SIZE];
    public:
    Game(int **F) {
      for (int i = 0;i<4;i++){
          for (int j = 0; j < 4; j++) {
              field[i][j] = F[i][j];
          }
      }
    };
    void Write(){
        std::cout << "------------";
        for (int i = 0; i < 4; i++) {
            if (field[1][i] == -1) {
                std::cout << "[!]";
            }
            else {
            }
    }
};

int main() {

    system("title Application");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    system("cls");

    int choose_posV;
    int choose_posG;
    int iKey;
    int exit_flag;
    int menu_pos;
    COORD cursorPos;
    int F[FIELD_SIZE][FIELD_SIZE] = { {1,1,2,1} ,{ 1,-1,2,-1 },{ 2,2,3,1 }, { 1,-1,1,0 } };
    exit_flag = 0;
    choose_posV = 0;
    choose_posG = 0;
    menu_pos = 0;

    while (!exit_flag) {

        system("cls");
        iKey = 67;
        /*cursorPos = {0, 0};
        SetConsoleCursorPosition(hStdOut, cursorPos);*/

        while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
            switch (iKey) {
            case KEY_ARROW_UP:
                choose_posV--;
                break;
            case KEY_ARROW_DOWN:
                choose_posV++;
                break;
            case KEY_ARROW_RIGHT:
                choose_posG++;
                break;
            case KEY_ARROW_LEFT:
                choose_posG--;
                break;
            }

            system("cls");

            if (choose_posV < 0) { choose_posV = FIELD_SIZE - 1; }
            if (choose_posV > FIELD_SIZE - 1) { choose_posV = 0; }
            if (choose_posG < 0) { choose_posG = FIELD_SIZE - 1; }
            if (choose_posG > FIELD_SIZE - 1) { choose_posG = 0; }

            /*for (int i = 0; i < FIELD_SIZE; i++) {
                cursorPos = { 3, (short)i };
                SetConsoleCursorPosition(hStdOut, cursorPos);
            }*/

            std::cout << choose_posG << " " << choose_posV;
            /*cursorPos = (COORD){ 0, choose_pos };
            SetConsoleCursorPosition(hStdOut, cursorPos);
            printf("<<", iKey);
            cursorPos = (COORD){ strlen(menus[menu_pos][choose_pos]) + 3 + 1, choose_pos };
            SetConsoleCursorPosition(hStdOut, cursorPos);
            printf(">>");*/

            iKey = _getch();
        }
    }
}