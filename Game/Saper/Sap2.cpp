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
    Game(int** F) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                field[i][j] = F[i][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                id[i][j] = 0;
            }
        }
    };
    void Write() {
        std::cout << "------------";
        for (int i = 0; i < 4; i++) {
            if (field[1][i] == -1) {
                std::cout << "[!]";
            }
            else {
            }
        }
    };
};

    int main() {
        int a;
        int d;
        a = 7;
        d = 12;
        d += a;
        std::cout << d;
    }
