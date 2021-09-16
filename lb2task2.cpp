#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <Windows.h>

void qs(int* items, int left, int right);
void shell(int*, int count);
void threesort(int* arraypointer1, int* arraypointer2, int* arraypointer3, int num);
void filesave(int* arraypointer, int num, const char inf[] );

int compare(const void* x1, const void* x2)
{
    return (*(int*)x1 - *(int*)x2);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));
    /*Очищение файла от результатов предыдущего запуска*/
    FILE* source = fopen("sorteddata.txt", "w");
    if (source == NULL)
    {
        printf("Ошибка открытия файла!");
        getchar();
        exit(0);
    }
    fclose(source);

    int count[5] = {3000, 4000, 5000, 6000, 7000};
    int* arr1,* arr2,* arr3;
    for (int k = 0; k < 5; k++)
    {
        FILE* sourcerand = fopen("sorteddata.txt", "a");
        fprintf(source, "\n\nСлучайный массив из %d элементов", count[k]);
        fclose(source);
        arr1 = (int*)malloc(count[k] * sizeof(int));
        arr2 = (int*)malloc(count[k] * sizeof(int));
        arr3 = (int*)malloc(count[k] * sizeof(int));

        /*Генерация массива случайных данных*/       
        printf("\nСлучайный массив из %d элементов\n", count[k]);
            for (int i = 0; i < count[k]; i++)
            {
                arr1[i] = rand() % 1000;
                arr2[i] = rand() % 1000;
                arr3[i] = rand() % 1000;
            }
        /*Сортировки и запись результатов*/
        threesort(arr1, arr2, arr3, count[k]);


        FILE* sourceup = fopen("sorteddata.txt", "a");
        fprintf(source, "\n\nВозрастающий массив из %d элементов", count[k]);
        fclose(source);

        /*Генерация возрастающего массива*/
        printf("\nВозрастающий массив из %d элементов\n", count[k]);
        for (int i = 0; i < count[k]; i++)
        {
            arr1[i] = i;
            arr2[i] = i+10;
            arr3[i] = i+i;
        }
        arr1 = &arr1[0];
        arr2 = &arr2[0];
        arr3 = &arr3[0];
        /*Сортировки и запись результатов*/
        threesort(arr1, arr2, arr3, count[k]);

        FILE* sourcedown = fopen("sorteddata.txt", "a");
        fprintf(source, "\n\nУбывающий массив из %d элементов", count[k]);
        fclose(source);

        /*Генерация убывающего массива*/
        printf("\nУбывающий массив из %d элементов\n", count[k]);
        for (int i = count[k]; i > 0; i--)
        {
            arr1[count[k] - i] = i;
            arr2[count[k] - i] = i + 10;
            arr3[count[k] - i] = i + i;
        }
        arr1 = &arr1[0];
        arr2 = &arr2[0];
        arr3 = &arr3[0];
        /*Сортировки и запись результатов*/
        threesort(arr1, arr2, arr3, count[k]);
        
        FILE* sourceupdown = fopen("sorteddata.txt", "a");
        fprintf(source, "\n\nПилообразный массив из %d элементов", count[k]);
        fclose(source);

        /*Генерация пилообразного массива*/
        printf("\nПилообразный массив из %d элементов\n", count[k]);
        for (int i = 0; i <= count[k] /2; i++)
        {
            arr1[i] = i;
            arr1[count[k] - 1 - i] = i;
            arr2[i] = i;
            arr2[count[k] -1 - i] = i;
            arr3[i] = i;
            arr3[count[k] - 1 - i] = i;
        }
        arr1 = &arr1[0];
        arr2 = &arr2[0];
        arr3 = &arr3[0];
        /*Сортировки и запись результатов*/
        threesort(arr1, arr2, arr3, count[k]);
    }
    getchar();
    return 0;
}


void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left; j = right;
    /* выбор компаранда */
    x = items[(left + right) / 2];
    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j)
        {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j)
        qs(items, left, j);
    if (i < right)
        qs(items, i, right);
}

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}


/*Функция выполняет алгоритм быстрой сортировки, сортировки Шелла и вызов функции qsort
Фиксируется время выполнения каждой сортировки, а результаты заносятся в файл
На вход получает указатели на первые элементы сортируемых массивов и количество элементов*/
void threesort(int* arraypointer1, int* arraypointer2, int* arraypointer3, int num)
{
    clock_t start, end;
    start = clock();
    qs(arraypointer1, 0, num - 1);
    end = clock();
    filesave(arraypointer1, num, "\n\nБыстрая сортировка\n");
    printf("Быстрая сортировка: %f секунд\n", ((float)end - (float)start) / CLOCKS_PER_SEC);
   
    start = clock();
    shell(arraypointer2, num);
    end = clock();
    filesave(arraypointer2, num, "\n\nСортировка Шелла\n");
    printf("Сортировка Шелла: %f секунд\n", ((double)end - (double)start) / CLOCKS_PER_SEC);
    
    start = clock();
    qsort(arraypointer3, num, sizeof(int), compare);
    end = clock();
    filesave(arraypointer3, num, "\n\nБыстрая сортировка qsort\n");
    printf("Функция qsort: %f секунд\n", ((double)end - (double)start) / CLOCKS_PER_SEC);

}


/*Функция выполняет запись элементов массива в файл
На вход получает указатель на первый элемент массива, количество элементов в масииве и строку с доп. информацией*/
void filesave(int* arraypointer, int num, const char inf[] )
{
    FILE* source = fopen("sorteddata.txt", "a");
    if (source == NULL)
    {
        printf("Ошибка открытия файла!");
        getchar();
        exit(0);
    }

    fprintf(source, inf);
    for (int i = 0; i < num; i++)
    {
        fprintf(source, "%d", *arraypointer);
        arraypointer++;
        if (i != num - 1)
            fprintf(source, ", ");
    }
    fclose(source);
}