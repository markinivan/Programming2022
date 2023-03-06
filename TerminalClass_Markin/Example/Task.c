
#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "sys/stat.h"
#pragma warning(disable : 4996)


// управл¤ющие консолью библиотеки
#include <windows.h>
#include <conio.h>

// основные ключи, которые могут пригодитьс¤

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

void draw_table_str(float* d[4]) {
    int count;
    int s = 7;
    int s1 = 4;
    char** headings[7] = { "Сортировка ","Время работы","Замедление","Кол-во перестановок","Увел. перестановок","Кол-во сравнений","Увел. сравнений" };
    char** sorts[4] = { "Пузырьковая","Посл. Шелла","Шейкерная  ","Посл. Кнута" };
    printf("|");
    for (int i = 0; i < s; i++)
    {
        printf("%s |", headings[i]);
    }
    printf("\n|");
    for (int i = 0; i < s1; i++) {
        printf("%s |", sorts[i]);
        for (int j = 0; j < s - 1; j++) {
            //printf("    %d %d   ", j, i);
            if (d[i][j] > 1) {
                count = strlen(headings[j + 1]) - (floor(abs(log10(abs(d[i][j])))) + 1) + 1 - 4;
            }
            else {
                count = strlen(headings[j + 1]) - 4;
            }
            if (d[i][j]!= d[i][j]) {
                printf("-");
                count+=4;
            } else if (d[i][j] - ((int)d[i][j]) * 1.0 == 0)
            {
                printf("%d", (int)d[i][j]);
                count += 4;
            }
            else {
                printf("%.03f", d[i][j]);
            }
            for (int t = 0; t < count; t++) {
                printf(" ");
            }
            printf("|");
        }
        if (s1 - i > 1) {
            printf("\n|");
        }
    }
    printf("\n");
}
void draw_table(float** d, int s1) {
    int count;
    int s = 3;
    char** headings[3] = { "Размер массива","Время работы","Замедление" };
    printf("|");
    for (int i = 0; i < s; i++)
    {
        printf("%s |", headings[i]);
    }
    printf("\n|");
    for (int i = 0; i < s1; i++) {
        for (int j = 0; j < s; j++) {
            if (d[i][j] > 1) {
                count = strlen(headings[j]) - (floor(log10(abs(d[i][j]))) + 1) + 1 - 4;
            }
            else {
                count = strlen(headings[j]) - 4;
            }
            if (d[i][j] != d[i][j] || d[i][j]> MAXINT) {
                printf("-");
                count = strlen(headings[j]);
            }
            else if (d[i][j] - ((int)d[i][j]) * 1.0 == 0)
            {
                printf("%d", (int)d[i][j]);
                count += 4;
            }
            else {
                printf("%.03f", d[i][j]);
            }
            for (int t = 0; t < count; t++) {
                printf(" ");
            }
            printf("|");
        }
        if (s1 - i > 1) {
            printf("\n|");
        }
    }
    printf("\n");
}

void generatemass(int* mass, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        mass[i] = min + rand() % (max - min + 1);
    }
}
void copymass(int* mass, int* mass_, int size) {
    for (int i = 0; i < size; i++) {
        mass_[i] = mass[i];
    }
}
void printmass(int* mass, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", mass[i]);
    }
}
int checksort(int* mass, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (mass[i] > mass[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void bubblesort(int* mass, int size, int* comp, int* swap, float* time) {
    *time = clock();
    int tmp;
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            (*comp)+=1;
            if (mass[j] > mass[j + 1]) {
                tmp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = tmp;
                (*swap)+=1;
            }
        }
    }
    *time = clock() - *time;
}
void shellsort(int* mass, int size, int* comp, int* swap, float* time) {
    *time = clock();
    for (int x = size / 2; x > 0; x /= 2) {
        for (int i = x; i < size; ++i) {
            (*comp)++;
            for (int j = i - x; j >= 0 && mass[j] > mass[j + x]; j -= x) {
                int temp = mass[j];
                mass[j] = mass[j + x];
                mass[j + x] = temp;
                (*swap)++;
                (*comp)++;
            }
        }
    }
    *time = clock() - *time;
}
void shakesort(int* mass, int size, int* comp, int* swap, float* time) {
    int tmp, ind = -1;
    *time = clock();
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            (*comp)++;
            if (mass[j] > mass[j + 1]) {
                (*swap)++;
                tmp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = tmp;
            }
            for (int j = i; ind < j; j--) {
                (*comp)++;
                if (mass[j - 1] > mass[j]) {
                    (*swap)++;
                    tmp = mass[j - 1];
                    mass[j - 1] = mass[j];
                    mass[j] = tmp;
                }
            }
            ind += 1;
        }
    }
    *time = clock() - *time;
}
void shellksort(int* mass, int size, int* comp, int* swap, float* time) {
    int x = 1;
    for (x = 1; (((x * 3) + 1) * 3) + 1 < size; x = (x * 3) + 1) {
        printf("%d ", x);
    }
    *time = clock();
    for (x; x > 0; x = (x - 1) / 3) {
        for (int i = x; i < size; ++i) {
            (*comp)++;
            for (int j = i - x; j >= 0 && mass[j] > mass[j + x]; j -= x) {
                (*comp)++;
                (*swap)++;
                int temp = mass[j];
                mass[j] = mass[j + x];
                mass[j + x] = temp;
            }
        }
    }
    *time = clock() - *time;
}

int nsearch(int* mass, int size, int a) {
    int id = -1;
    for (int i = 0; i < size; i++) {
        if (mass[i] == a) {
            id = i;
            break;
        }
    }
    return id;
}
int binsearch(int* mass, int size, int a) {
    int id, b = 0, B = size - 1;
    while (b <= B) {
        int id = (b + B) / 2;
        if (mass[id] == a) {
            return id;
        }
        else if (mass[id] < a) {
            b = id + 1;
        }
        else if (mass[id] > a) {
            B = id - 1;
        }
    }
    return -1;
}

// объ¤вление главной функции
int main() {
    // настройки
    srand(time(0));
    // задаЄм название консольного окна
    system("title Application");

    // устанавливаем взаимодействие с русскими буквами
    SetConsoleCP(1251);         // установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);   // установка кодовой страницы win-cp 1251 в поток вывода

    // получаем дескриптор окна дл¤ обращени¤ к консоли
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // отключение мигани¤ курсора в консоли (в нашем меню курсор лишний)
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    // задаЄм серый фон дл¤ окна консоли
    SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    // очищаем экран, чтобы настройка цвета применилась
    system("cls");

    // объ¤вление переменных
    int choose_pos;                    // переменна¤ дл¤ хранени¤ выбранного пункта меню
    int iKey;                          // переменна¤ дл¤ фиксации нажатой клавиши
    int exit_flag;                     // флаг на завершение программы
    int menu_pos;                      // 
    COORD cursorPos;                   // управление положением курсора, чтобы мен¤ть выводимый текст

    int* menus_sizes[7] = {4, 3, 3, 4, 5, 3, 4};
    char* menu[4] = { "Режим эксперимента","Алгоритмы", "Настройки", "Выход"};
    char* menu1[3] = { "Сравнеине сортировок", "Эффективность", "Назад" };
    char* menu2[3] = { "Сортировка", "Поиск", "Назад" };
    char* menu3[4] = { "Задать массив", "Показать текущий массив", "Изменить путь до рабочей директории", "Назад"};
    char* menu4[5] = { "Пузырьковая сортировка", "Последовательность Шелла", "Шейкерная сортировка", "Последовательность Кнута", "Назад"};
    char* menu5[3] = { "Наивный поиск", "Бинарный поиск", "Назад" };
    char* menu6[4] = { "Задать вручную", "Сгенерировать случайно", "Прочитить из файла", "Назад"};
    char** menus[7] = {menu,menu1,menu2,menu3,menu4,menu5,menu6};

    void (*sorts[4])(int*, int, int*, int*, float*) = { bubblesort,shellsort,shakesort,shellksort };

    float bubble[6];
    float shell[6];
    float shake[6];
    float shellk[6];
    float** res[4][6] = {bubble,shell,shake,shellk};
    float** res1;
    int count_sizes = 3;

    float time = 0;
    int comp = 0;
    int swap = 0;

    float mtime;
    int mcomp;
    int mswap;

    int E_id = 0;
    int a;
    int max;
    int min;

    char dir[100] = "C:\\files\\";
    char input[100] = "input.txt";
    char output[100] = "output.txt";
    char filepath[200];

    FILE* file = NULL;
    errno_t error;


    int size = 30;
    int* mass1;
    mass1 = (int*)malloc(size * sizeof(int));
    generatemass(mass1, size, 0, 100);
    int* mass2;
    mass2 = (int*)malloc(size * sizeof(int));
    copymass(mass1, mass2, size);

    exit_flag = 0;
    choose_pos = 0;
    menu_pos = 0;

    while (!exit_flag) {
        /* 1. вывод меню с переключением */

        // сброс консоли в стартовое положение
        system("cls");
        iKey = 67;
        cursorPos = (COORD){ 0, 0 };
        SetConsoleCursorPosition(hStdOut, cursorPos);

        // контроль нажати¤ клавиш
        while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
            switch (iKey) {
            case KEY_ARROW_UP:
                choose_pos--;
                break;
            case KEY_ARROW_DOWN:
                choose_pos++;
                break;
            }

            system("cls");

            // зацикливание перелистывани¤ меню
            if (choose_pos < 0) { choose_pos = (int)menus_sizes[menu_pos] - 1; }
            if (choose_pos > (int)menus_sizes[menu_pos] - 1) { choose_pos = 0; }

            for (int i = 0; i < menus_sizes[menu_pos]; i++) {
                cursorPos = (COORD){ 3, i };
                SetConsoleCursorPosition(hStdOut, cursorPos);
                printf("%s \n", menus[menu_pos][i]);
            }

            // обозначение выбранной позиции
            cursorPos = (COORD){ 0, choose_pos };
            SetConsoleCursorPosition(hStdOut, cursorPos);
            printf("<<", iKey);
            cursorPos = (COORD){ strlen(menus[menu_pos][choose_pos]) + 3 + 1, choose_pos };
            SetConsoleCursorPosition(hStdOut, cursorPos);
            printf(">>");

            // ожидание нового нажати¤ клавиши
            iKey = _getch();
        }

        /* 2. основна¤ часть программы */
        switch (menu_pos) {
        case 0:
            switch (choose_pos)
            {
            case 0:
                menu_pos = 1;
                choose_pos = 0;
                break;
            case 1:
                menu_pos = 2;
                choose_pos = 0;
                break;
            case 2:
                menu_pos = 3;
                choose_pos = 0;
                break;
            case 3:
                exit_flag = 1;
                choose_pos = 0;
                break;

            default:
                break;
            }
            break;
        case 1:
            switch (choose_pos)
            {
            case 0:
                copymass(mass1, mass2, size);
                bubblesort(mass2, size, &comp, &swap, &time);
                mtime = time;
                mcomp = comp;
                mswap = swap;
                bubble[0] = time;
                bubble[2] = swap;
                bubble[4] = comp;
                comp = 0;
                swap = 0;
                copymass(mass1, mass2, size);
                shellsort(mass2, size, &comp, &swap, &time);
                mtime = (mtime > time ? time : mtime);
                mcomp = (mcomp > comp ? comp : mcomp);
                mswap = (mswap > swap ? swap : mswap);
                shell[0] = time;
                shell[2] = swap;
                shell[4] = comp;
                comp = 0;
                swap = 0;
                copymass(mass1, mass2, size);
                shakesort(mass2, size, &comp, &swap, &time);
                mtime = (mtime > time ? time : mtime);
                mcomp = (mcomp > comp ? comp : mcomp);
                mswap = (mswap > swap ? swap : mswap);
                shake[0] = time;
                shake[2] = swap;
                shake[4] = comp;
                comp = 0;
                swap = 0;
                copymass(mass1, mass2, size);
                shellksort(mass2, size, &comp, &swap, &time);
                mtime = (mtime > time ? time : mtime);
                mcomp = (mcomp > comp ? comp : mcomp);
                mswap = (mswap > swap ? swap : mswap);
                shellk[0] = time;
                shellk[2] = swap;
                shellk[4] = comp;
                bubble[1] = bubble[0] / mtime;
                bubble[3] = bubble[2] / mswap;
                bubble[5] = bubble[4] / mcomp;
                shell[1] = shell[0] / mtime;
                shell[3] = shell[2] / mswap;
                shell[5] = shell[4] / mcomp;
                shake[1] = shake[0] / mtime;
                shake[3] = shake[2] / mswap;
                shake[5] = shake[4] / mcomp;
                shellk[1] = shellk[0] / mtime;
                shellk[3] = shellk[2] / mswap;
                shellk[5] = shellk[4] / mcomp;
                system("pause");
                system("cls");
                draw_table_str(res);
                comp = 0;
                swap = 0;
                time = 0;
                system("pause");
                break;
            case 1:
                system("cls");
                printf("Выберите алгоритм сортировки:\n0.Пузырьковая\n1.Шелла(пос.Шелла)\n2.Шейкеная\n3.Шелла(пос.Кнута)\nВвод:");
                scanf_s("%d", &E_id);
                printf("Введите количество экспериментов:");
                scanf_s("%d", &count_sizes);
                res1 = (float**)malloc(sizeof(float*) * count_sizes);
                mtime = MAXINT;
                for (int i = 0; i < count_sizes; i++) {
                    int ms;
                    comp = 0;
                    swap = 0;
                    time = 0;
                    res1[i] = (float*)malloc(sizeof(float) * 3);
                    printf("Введите размер массива:");
                    scanf_s("%d", &ms);
                    res1[i][0] = ms;
                    free(mass2);
                    mass2 = (int*)malloc(sizeof(int) * ms);
                    generatemass(mass2, ms, 0, 100);
                    sorts[E_id](mass2, ms, &comp, &swap, &time);
                    res1[i][1] = (int)time;
                    mtime = mtime > time ? time : mtime;
                }
                for (int i = 0; i < count_sizes; i++) {
                    res1[i][2] = res1[i][1] / mtime;
                }
                system("cls");
                draw_table(res1, count_sizes);
                free(res1);
                system("pause");
                break;
            case 2:
                menu_pos = 0;
                choose_pos = 0;
                break;

            default:
                break;
            }
            break;
        case 2:
            switch (choose_pos)
            {
            case 0:
                menu_pos = 4;
                choose_pos = 0;
                break;
            case 1:
                menu_pos = 5;
                choose_pos = 0;
                break;
            case 2:
                menu_pos = 0;
                choose_pos = 0;
                break;

            default:
                break;
            }
            break;
        case 3:
            switch (choose_pos)
            {
            case 0:
                menu_pos = 6;
                choose_pos = 0;
                break;
            case 1:
                if (size <= 20) {
                    printmass(mass1, size);
                    printf("\n");
                    system("pause");
                }
                else {
                    system("cls");
                    strcpy_s(filepath, sizeof filepath, dir);
                    strncat_s(filepath, 100, output, 100);
                    error = fopen_s(&file, filepath, "w+");
                    if (file == NULL) {
                        printf("%s\n", filepath);
                        printf("Error in input file. Error %d\n", error);
                        system("pause");
                    }
                    else {
                        for (int i = 0; i < size; i++) {
                            if (fprintf(file, "%d ", mass1[i]) == 0) {
                                printf("Error %d\n", i);
                                system("pause");
                                break;
                            }
                        }
                        fclose(file);
                        printf("Размер массива более 20, массив записан в файл\n");
                        system("pause");
                    }
                }
                    break;
            case 2:
                system("cls");
                printf("Введите путь до файлов:");
                scanf("%s",&dir);
                printf("\nПуть до файлов изменён\n");
                system("pause");
                break;
            case 3:
                menu_pos = 0;
                choose_pos = 0;
                break;

            default:
                menu_pos = 0;
                choose_pos = 0;
                break;
                }
            break;
        case 4:
            switch (choose_pos)
                {
                case 0:
                    system("cls");
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, input, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    printf("\n");
                    comp = 0;
                    swap = 0;
                    time = 0;
                    sorts[choose_pos](mass1, size, &comp, &swap, &time);
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, output, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    if (time == 0) {
                        printf("\nВремя сортировки: менее милисекунды");
                    }
                    else {
                        printf("\nВремя сортировки: %d", (int)time);
                    }
                    printf("\nКол-во сравнений: %d\nКол-во перестановок: %d\n", comp, swap);
                    system("pause");
                    break;
                case 1:
                    system("cls");
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, input, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    printf("\n");
                    comp = 0;
                    swap = 0;
                    time = 0;
                    sorts[choose_pos](mass1, size, &comp, &swap, &time);
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, output, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    if (time == 0) {
                        printf("\nВремя сортировки: менее милисекунды");
                    }
                    else {
                        printf("\nВремя сортировки: %d", (int)time);
                    }
                    printf("\nКол-во сравнений: %d\nКол-во перестановок: %d\n", comp, swap);
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, input, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    printf("\n");
                    comp = 0;
                    swap = 0;
                    time = 0;
                    sorts[choose_pos](mass1, size, &comp, &swap, &time);
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, output, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    if (time == 0) {
                        printf("\nВремя сортировки: менее милисекунды");
                    }
                    else {
                        printf("\nВремя сортировки: %d", (int)time);
                    }
                    printf("\nКол-во сравнений: %d\nКол-во перестановок: %d\n", comp, swap);
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, input, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    printf("\n");
                    comp = 0;
                    swap = 0;
                    time = 0;
                    sorts[choose_pos](mass1, size, &comp, &swap, &time);
                    if (size <= 20) {
                        printmass(mass1, size);
                        printf("\n");
                        system("pause");
                    }
                    else {
                        strcpy_s(filepath, sizeof filepath, dir);
                        strncat_s(filepath, 100, output, 100);
                        error = fopen_s(&file, filepath, "w+");
                        if (file == NULL) {
                            printf("%s\n", filepath);
                            printf("Error in input file. Error %d\n", error);
                            system("pause");
                        }
                        else {
                            for (int i = 0; i < size; i++) {
                                if (fprintf(file, "%d ", mass1[i]) == 0) {
                                    printf("Error %d\n", i);
                                    system("pause");
                                    break;
                                }
                            }
                            fclose(file);
                            printf("Размер массива более 20, массив записан в файл\n");
                            system("pause");
                        }
                    }
                    if (time == 0) {
                        printf("\nВремя сортировки: менее милисекунды");
                    }
                    else {
                        printf("\nВремя сортировки: %d", (int)time);
                    }
                    printf("\nКол-во сравнений: %d\nКол-во перестановок: %d\n", comp, swap);
                    system("pause");
                    break;
                case 4:
                    menu_pos = 2;
                    choose_pos = 0;
                    break;

                default:
                    menu_pos = 2;
                    choose_pos = 0;
                    break;
                }
            break;
        case 5:
            switch (choose_pos)
                {
                case 0:
                    system("cls");
                    printf("Искомый элемент:");
                    scanf_s("%d", &a);
                    a = nsearch(mass1, size, a);
                    if (a >= 0) {
                        printf("\nИндекс искомого элемнта: %d\n", a);
                    }
                    else {
                        printf("\nТакого элемента в массиве нет\n");
                    }
                    system("pause");
                    break;
                case 1:
                    system("cls");
                    if (!checksort(mass1, size)) {
                        printf("Невозможно применить бинарный поиск к неотсортированному массиву\n");
                        system("pause");
                    }
                    else {
                        printf("Искомый элемент:");
                        scanf_s("%d", &a);
                        a = binsearch(mass1, size, a);
                        if (a >= 0) {
                            printf("\nИндекс искомого элемнта: %d\n", a);
                        }
                        else {
                            printf("\nТакого элемента в массиве нет\n");
                        }
                        system("pause");
                    }
                default:
                    menu_pos = 0;
                    choose_pos = 0;
                    break;
                }
            break;
        case 6:
            switch (choose_pos)
                {
                case 0:
                    system("cls");
                    free(mass1);
                    printf("Введите размер массива");
                    scanf_s("%d",&size);
                    printf("Вводите элементы массива");
                    mass1 = (int*)malloc(sizeof(int) * size);
                    for (int i = 0; i < size; i++) {
                        scanf_s("%d", &mass1[i]);
                    }
                    break;
                case 1:
                    system("cls");
                    free(mass1);
                    printf("Введите размер массива");
                    scanf_s("%d", &size);
                    printf("Введите максимальный элемент");
                    scanf_s("%d", &max);
                    printf("Введите минимальный элемент");
                    scanf_s("%d", &min);
                    mass1 = (int*)malloc(sizeof(int) * size);
                    generatemass(mass1, size, min, max);
                    break;
                case 2:
                    system("cls");
                    strcpy_s(filepath, sizeof filepath, dir);
                    strncat_s(filepath, 100, input, 100);
                    error = fopen_s(&file, filepath, "r+");
                    if (file == NULL) {
                        printf("%s\n", filepath);
                        printf("Error in input file. Error %d\n", error);
                        system("pause");
                    }
                    else {

                        if (fscanf_s(file, "%d", &size) != 1) {
                            printf("Error\n");
                            system("pause");
                            break;
                        }
                        mass1 = (int*)malloc(sizeof(int) * size);
                        for (int i = 0; i < size; i++) {
                            if (fscanf_s(file, "%d", &mass1[i]) != 1) {
                                printf("Error\n");
                                system("pause");
                                break;
                            }
                        }
                    }
                        fclose(file);
                        printf("Файл успешно считан\n");
                        system("pause");
                        break;
                case 3:
                    menu_pos = 3;
                    choose_pos = 0;
                    break;

                default:
                    break;
                    }
            break;
                }
            }
    // вывод результата
    system("cls");
    printf("Goodbay!\n");

    // завершение программы
    free(mass1);
    free(mass2);
    system("pause");
    return 0;
}