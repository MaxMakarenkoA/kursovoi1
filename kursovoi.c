#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define SCREENW 60 
#define SCREENH 40
double F1(double x)
{
    if (x <= 0) 
    {
        return -1;
    }
    else if (x > 0 && x <= 5) {
        double sinys = sin(x);
        if (sinys != 0) {
            return pow(sinys, 3) - sqrt(fabs(log(fabs(sinys))));
        }
        else {
            return -1;
        }
    }
    else if (x > 5 && x < 10) {
        return 3.0 / 4 * exp(x);
    }
    else if (x >= 10) {
        return 3 * sin(3 * x) + cos(x);
    }
    else {
        return -1;
    }
}

double F2(double x)
{
    if (x <= 0) {
        return -1;
    }
    else {
        double sinys2 = sin(x); 
        if (sinys2 != 0) {
            return atan(x) / (1 + pow(sin(x), 2));
        }
        else {
            return -1;
        }
    }
}
typedef double (*TFunc)(double); // указатель на функцию

void TablisaX(double x_na4alo, double x_konec, double shag) 
{
    for (double x1 = x_na4alo; x1 < x_konec; x1 += shag)
    {
        double result_F1 = F1(x1);
        printf("%.2f\t|\t%.4f\n", x1, result_F1);
    }
} 

void TablisaY(double y_na4alo, double y_konec, double shag)
{
    for (double y1 = y_na4alo; y1 < y_konec; y1 += shag)
    {
        double result_F2 = F2(y1);
        printf("%.2f\t|\t%.4f\n", y1, result_F2);
    }
}

void plot(double x1, double x2, TFunc f)

{

    char screen[SCREENW][SCREENH];

    double x, y[SCREENW];

    double ymin = 0, ymax = 0;

    double hx, hy;

    int i, j;

    int xz, yz;

    hx = (x2 - x1) / (SCREENW - 1);

    for (i = 0, x = x1; i < SCREENW; ++i, x += hx)
    {

        y[i] = f(x); //расчет значений функции для каждой точки поля вывода графика

        if (y[i] < ymin) ymin = y[i];

        if (y[i] > ymax) ymax = y[i];

    }

    hy = (ymax - ymin) / (SCREENH - 1);

    yz = (int)floor(ymax / hy + 0.5);

    xz = (int)floor((0. - x1) / hx + 0.5);

    //построение осей и заполнение массива отображения пробелами

    for (j = 0; j < SCREENH; ++j)

        for (i = 0; i < SCREENW; ++i)
        {

            if (j == yz && i == xz) screen[i][j] = '+';

            else if (j == yz) screen[i][j] = '-';

            else if (i == xz) screen[i][j] = '|';

            else screen[i][j] = ' ';

        }

    //определение положения значения функции на поле вывода

    for (i = 0; i < SCREENW; ++i) {

        j = (int)floor((ymax - y[i]) / hy + 0.5);

        screen[i][j] = '*';

    }

    //печать массива символов

    for (j = 0; j < SCREENH; ++j) {

        for (i = 0; i < SCREENW; ++i)  putchar(screen[i][j]);

        putchar('\n');

    }

}


int* insert(int* ptr_arr, int* size, int index, int num) {
    int size_n = (*size) + 1;

    if (ptr_arr == NULL) return NULL;

    int* ptr_arr_n = (int*)realloc(ptr_arr, size_n * sizeof(int));

    if (ptr_arr_n == NULL) return ptr_arr;

    ptr_arr = ptr_arr_n;

    for (int i = size_n - 1; i > index; i--)
        ptr_arr[i] = ptr_arr[i - 1];

    ptr_arr[index] = num;

    *size = size_n;

    return ptr_arr;
}

void ElementiMassiva(int* arr, int size) {
    printf("Введите %d элементов для массива:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

void IzmenenieMassiva(int** arr, int* size, int Zna4Vstavka, int Kratnost) {
    int originalSize = *size;
    for (int i = 0; i < originalSize; i++) {
        if ((*arr)[i] % Kratnost == 0) {
            *arr = insert(*arr, size, i, Zna4Vstavka);
            i++; 
            originalSize++; 
        }
    }
}

void PrintPosleMassiv(int* arr, int size) {
    printf("Модифицированный массив: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printOriginalMassiv(int* arr, int size) {
    printf("Исходный массив: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* VidileniePamyati(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти.\n");
        exit(1);
    }
    return arr;
}


int main()
{
    setlocale(LC_ALL, "RUS");
    int choice, returnToMenu, size, Zna4Vstavka, Kratnost;
    double x, b, x_na4alo, x_konec, shag, y_na4alo, y_konec;

    do {

        puts("***********************************************************************************\n"
            "\t\tПрограмму реализовал студент бИСТ-233\n"
            "\t\t\tМакаренко Максим\n"
            "Меню [Выберите число]:\n"
            "1. V(x) посчитать его значение при заданном аргументе x\n"
            "\tесли 0 < x < 5, V(x) = (sinx^3-sqrt(ln(|sinx))\n"
            "\tесли 5 < x < 10, V(x) = 3/4*e^x\n"
            "\tесли x=>10, V(x) = 3sin^3(x)+cos\n"
            "2. Y(x) посчитать его значение при заданном аргументе x\n"
            "\t Y(x) = arctgbx/1+sin^2\n"
            "3. V(x) посчитать на заданных интервалах\n"
            "4. Y(x) посчитать на заданных интервалах\n"
            "5. Построить график функций для Y(x) или V(x)\n"
            "6. Вставить элемент перед каждым элементом массива, который кратен заданному числу\n"
            "7. Выход\n"
            "***********************************************************************************\n");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            printf("Введите значение x для функции V: ");
            scanf("%lf", &x);


            while (x <= 0)
            {
                printf("Ошибка: синус от x равен 0. Результат не определен.\n");
                printf("Введите новое значение x: ");
                scanf("%lf", &x);
            }

            double resultF1 = F1(x);

            if (resultF1 != -1) {
                printf("Результат F1(%.2f) = %.4f\n", x, resultF1);
            }
            else {
                printf("Ошибка: синус от x равен 0. Результат не определен.\n");
            }
            break;


        case 2:
            printf("Введите значение x для функции Y: ");
            scanf("%lf", &x);


            while (x <= 0) {
                printf("Ошибка: синус от x равен 0. Результат не определен.\n");
                printf("Введите новое значение x: ");
                scanf("%lf", &x);
            }


            double resultF2 = F2(x);

            if (resultF2 != -1) {
                printf("Результат F2(%.2f) = %.4f\n", x, resultF2);
            }
            else {
                printf("Ошибка: синус от x равен 0. Результат не определен.\n");
            }
            break;


        case 3:
            printf("Введите начальное значение x: ");
            scanf("%lf", &x_na4alo);

            printf("Введите конечное значение x: ");
            scanf("%lf", &x_konec);

            printf("Введите величину шага: ");
            scanf("%lf", &shag);

            printf("Таблица значений для функции F1(x):\n");
            printf("x\t|\tF1(x)\n----------------------\n");
            TablisaX(x_na4alo, x_konec, shag);
            break;

        case 4:
            printf("Введите начальное значение y: ");
            scanf("%lf", &y_na4alo);

            printf("Введите конечное значение y: ");
            scanf("%lf", &y_konec);

            printf("Введите величину шага: ");
            scanf("%lf", &shag);

            printf("Таблица значений для функции F2(x):\n");
            printf("y\t|\tF2(x)\n----------------------\n");
            TablisaY(y_na4alo, y_konec, shag);
            break;

        case 5:

            printf("Выберите функцию для построения графика:\n");
            printf("1. График функции V(x)\n");
            printf("2. График функции Y(x)\n");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Введите начальное значение x: ");
                scanf("%lf", &x_na4alo);
                printf("Введите конечное значение x: ");
                scanf("%lf", &x_konec);
                printf("График функции V(x):\n");
                plot(x_na4alo, x_konec, F1); // Строим график для F1
            }
            else if (choice == 2) {
                printf("Введите начальное значение y: ");
                scanf("%lf", &y_na4alo);
                printf("Введите конечное значение y: ");
                scanf("%lf", &y_konec);
                printf("График функции Y(x):\n");
                plot(y_na4alo, y_konec, F2); // Строим график для F2
            }
            else {
                printf("Ошибка: Неверный выбор. Пожалуйста, выберите 1 или 2.\n");
                scanf("%lf", &x);
            }
            break;


        case 6:
            printf("Введите размер массива: ");
            scanf("%d", &size);

            int* arr = VidileniePamyati(size);

            ElementiMassiva(arr, size);

            printOriginalMassiv(arr, size);
            printf("\n");

            printf("Введите значение для вставки: ");
            scanf("%d", &Zna4Vstavka);

            printf("Введите кратность для вставки: ");
            scanf("%d", &Kratnost);
            IzmenenieMassiva(&arr, &size, Zna4Vstavka, Kratnost);
            PrintPosleMassiv(arr, size);
            printf("\n");
            arr = NULL;
            break;


        case 7:
            returnToMenu = 0;
            break;
        }


        if (returnToMenu != 0) {
            printf("Хотите продолжить? (1 - Да, 0 - Нет): ");
            scanf("%d", &returnToMenu);
        }

    } while (returnToMenu == 1);

    printf("До свидания!\n");
    return 0;
}