#include <math.h>
#include <locale>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>

#define FIELD_SIZE 4
#define BOMB_NUMBER 1 //need exeption

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
    int win_flag;
    int open;
    int field[FIELD_SIZE][FIELD_SIZE];
    int id[FIELD_SIZE][FIELD_SIZE];
public:
    Game() {
        open = 0;
        win_flag = 1;
        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                id[i][j] = 0;
            }
        }
        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                field[i][j] = 0;
            }
        }
        int count = 0;
        while (count < BOMB_NUMBER) {
            int x = rand() % FIELD_SIZE;
            int y = rand() % FIELD_SIZE;
            if (field[x][y] != -1) {
                field[x][y] = -1;
                count += 1;
                if (x - 1 >= 0) {
                    if (field[x - 1][y] != -1) {
                        field[x - 1][y] += 1;
                    }
                    if (y - 1 >= 0) {
                        if (field[x - 1][y - 1] != -1) {
                            field[x - 1][y - 1] += 1;
                        }
                    }
                    if (y + 1 <= FIELD_SIZE - 1) {
                       if (field[x - 1][y + 1] != -1) {
                           field[x - 1][y + 1] += 1;
                       }
                    }
                }
                if (x + 1 <= FIELD_SIZE - 1) {
                    if (field[x + 1][y] != -1) {
                        field[x + 1][y] += 1;
                    }
                    if (y - 1 >= 0) {
                        if (field[x + 1][y - 1] != -1) {
                            field[x + 1][y - 1] += 1;
                        }
                    }
                    if (y + 1 <= FIELD_SIZE - 1) {
                        if (field[x + 1][y + 1] != -1) {
                            field[x + 1][y + 1] += 1;
                        }
                    }
                }
                if (y + 1 <= FIELD_SIZE - 1) {
                    if (field[x][y + 1] != -1) {
                        field[x][y + 1] += 1;
                    }
                }
                if (y - 1 >= 0) {
                    if (field[x][y - 1] != -1) {
                        field[x][y - 1] += 1;
                    }
               }
            }
        }
           };
    void Write(int v, int g) {
        //std::cout << "------------" << "\n";
        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                if (id[i][j] == 0) {
                    std::cout << "[*]";
                }
                else {
                    std::cout << "[" << field[i][j] << "]";
                }
            }
            if (i == v) {
                printf(" +");
            }
            std::cout << "\n";
            //std::cout << "\n" << "------------" << "\n";
        }
        for (int s = 0; s < FIELD_SIZE; s++) {
            printf(" ");
            if (g == s) {
                printf("+");
                break;
            } else {
                printf("  ");
            }
        }
    };
    void Open(int v, int g) {
        if (field[v][g] != -1) {
            if (id[v][g] == 0) {
                id[v][g] = 1;
                open += 1;
                if (open == FIELD_SIZE * FIELD_SIZE - BOMB_NUMBER) {
                    win_flag = 2;
                }
            }
        }
        else {
            win_flag = 0;
        }
    }
    int CheckWin() {
        return win_flag;
    }
};

int main() {
    srand(time(NULL));

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
    exit_flag = 0;
    choose_posV = 0;
    choose_posG = 0;
    menu_pos = 0;

    while (!exit_flag) {

        system("cls");
        iKey = 67;
        Game test;
        /*cursorPos = {0, 0};
        SetConsoleCursorPosition(hStdOut, cursorPos);*/

        while (iKey != KEY_EXIT) {
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
            case KEY_ENTER:
                test.Open(choose_posV, choose_posG);
                if (test.CheckWin() == 0) {
                    exit_flag = 1;
                }
                break;
            }

            if (choose_posV < 0) { choose_posV = FIELD_SIZE - 1; }
            if (choose_posV > FIELD_SIZE - 1) { choose_posV = 0; }
            if (choose_posG < 0) { choose_posG = FIELD_SIZE - 1; }
            if (choose_posG > FIELD_SIZE - 1) { choose_posG = 0; }


            system("cls");

            if (exit_flag == 1 || test.CheckWin() == 2) {
                break;
            } else {
                test.Write(choose_posV, choose_posG);
            }

            iKey = _getch();
        }
        if (test.CheckWin() == 2) {
            std::cout << "Вы победили!\n";
            system("pause");
            exit_flag = 1;
        }
        else {
            std::cout << "Вы проиграли!";
        }
    }
}