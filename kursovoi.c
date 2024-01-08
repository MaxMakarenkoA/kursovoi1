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
typedef double (*TFunc)(double); // ��������� �� �������

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

        y[i] = f(x); //������ �������� ������� ��� ������ ����� ���� ������ �������

        if (y[i] < ymin) ymin = y[i];

        if (y[i] > ymax) ymax = y[i];

    }

    hy = (ymax - ymin) / (SCREENH - 1);

    yz = (int)floor(ymax / hy + 0.5);

    xz = (int)floor((0. - x1) / hx + 0.5);

    //���������� ���� � ���������� ������� ����������� ���������

    for (j = 0; j < SCREENH; ++j)

        for (i = 0; i < SCREENW; ++i)
        {

            if (j == yz && i == xz) screen[i][j] = '+';

            else if (j == yz) screen[i][j] = '-';

            else if (i == xz) screen[i][j] = '|';

            else screen[i][j] = ' ';

        }

    //����������� ��������� �������� ������� �� ���� ������

    for (i = 0; i < SCREENW; ++i) {

        j = (int)floor((ymax - y[i]) / hy + 0.5);

        screen[i][j] = '*';

    }

    //������ ������� ��������

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
    printf("������� %d ��������� ��� �������:\n", size);
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
    printf("���������������� ������: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printOriginalMassiv(int* arr, int size) {
    printf("�������� ������: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* VidileniePamyati(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("������ ��������� ������.\n");
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
            "\t\t��������� ���������� ������� ����-233\n"
            "\t\t\t��������� ������\n"
            "���� [�������� �����]:\n"
            "1. V(x) ��������� ��� �������� ��� �������� ��������� x\n"
            "\t���� 0 < x < 5, V(x) = (sinx^3-sqrt(ln(|sinx))\n"
            "\t���� 5 < x < 10, V(x) = 3/4*e^x\n"
            "\t���� x=>10, V(x) = 3sin^3(x)+cos\n"
            "2. Y(x) ��������� ��� �������� ��� �������� ��������� x\n"
            "\t Y(x) = arctgbx/1+sin^2\n"
            "3. V(x) ��������� �� �������� ����������\n"
            "4. Y(x) ��������� �� �������� ����������\n"
            "5. ��������� ������ ������� ��� Y(x) ��� V(x)\n"
            "6. �������� ������� ����� ������ ��������� �������, ������� ������ ��������� �����\n"
            "7. �����\n"
            "***********************************************************************************\n");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            printf("������� �������� x ��� ������� V: ");
            scanf("%lf", &x);


            while (x <= 0)
            {
                printf("������: ����� �� x ����� 0. ��������� �� ���������.\n");
                printf("������� ����� �������� x: ");
                scanf("%lf", &x);
            }

            double resultF1 = F1(x);

            if (resultF1 != -1) {
                printf("��������� F1(%.2f) = %.4f\n", x, resultF1);
            }
            else {
                printf("������: ����� �� x ����� 0. ��������� �� ���������.\n");
            }
            break;


        case 2:
            printf("������� �������� x ��� ������� Y: ");
            scanf("%lf", &x);


            while (x <= 0) {
                printf("������: ����� �� x ����� 0. ��������� �� ���������.\n");
                printf("������� ����� �������� x: ");
                scanf("%lf", &x);
            }


            double resultF2 = F2(x);

            if (resultF2 != -1) {
                printf("��������� F2(%.2f) = %.4f\n", x, resultF2);
            }
            else {
                printf("������: ����� �� x ����� 0. ��������� �� ���������.\n");
            }
            break;


        case 3:
            printf("������� ��������� �������� x: ");
            scanf("%lf", &x_na4alo);

            printf("������� �������� �������� x: ");
            scanf("%lf", &x_konec);

            printf("������� �������� ����: ");
            scanf("%lf", &shag);

            printf("������� �������� ��� ������� F1(x):\n");
            printf("x\t|\tF1(x)\n----------------------\n");
            TablisaX(x_na4alo, x_konec, shag);
            break;

        case 4:
            printf("������� ��������� �������� y: ");
            scanf("%lf", &y_na4alo);

            printf("������� �������� �������� y: ");
            scanf("%lf", &y_konec);

            printf("������� �������� ����: ");
            scanf("%lf", &shag);

            printf("������� �������� ��� ������� F2(x):\n");
            printf("y\t|\tF2(x)\n----------------------\n");
            TablisaY(y_na4alo, y_konec, shag);
            break;

        case 5:

            printf("�������� ������� ��� ���������� �������:\n");
            printf("1. ������ ������� V(x)\n");
            printf("2. ������ ������� Y(x)\n");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("������� ��������� �������� x: ");
                scanf("%lf", &x_na4alo);
                printf("������� �������� �������� x: ");
                scanf("%lf", &x_konec);
                printf("������ ������� V(x):\n");
                plot(x_na4alo, x_konec, F1); // ������ ������ ��� F1
            }
            else if (choice == 2) {
                printf("������� ��������� �������� y: ");
                scanf("%lf", &y_na4alo);
                printf("������� �������� �������� y: ");
                scanf("%lf", &y_konec);
                printf("������ ������� Y(x):\n");
                plot(y_na4alo, y_konec, F2); // ������ ������ ��� F2
            }
            else {
                printf("������: �������� �����. ����������, �������� 1 ��� 2.\n");
                scanf("%lf", &x);
            }
            break;


        case 6:
            printf("������� ������ �������: ");
            scanf("%d", &size);

            int* arr = VidileniePamyati(size);

            ElementiMassiva(arr, size);

            printOriginalMassiv(arr, size);
            printf("\n");

            printf("������� �������� ��� �������: ");
            scanf("%d", &Zna4Vstavka);

            printf("������� ��������� ��� �������: ");
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
            printf("������ ����������? (1 - ��, 0 - ���): ");
            scanf("%d", &returnToMenu);
        }

    } while (returnToMenu == 1);

    printf("�� ��������!\n");
    return 0;
}