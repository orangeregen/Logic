#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int N1, N2;
int** M1, ** M2, ** M1result, ** M2result, ** M3result, ** UnionResult, ** ProductResult, ** SumResult;

int** otozh(int vertexmin, int vertexmax, int** matrix, int size);
void printmatrix(int** source, int size);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Введите количество вершин графа G1: ");
    scanf_s("%d", &N1);

    printf("Введите количество вершин графа G2: ");
    scanf_s("%d", &N2);

    M1 = (int**)malloc(N1 * sizeof(int*));
    for (int i = 0; i < N1; i++)
        M1[i] = (int*)malloc(N1 * sizeof(int));

    M2 = (int**)malloc(N2 * sizeof(int*));
    for (int i = 0; i < N2; i++)
        M2[i] = (int*)malloc(N2 * sizeof(int));

    srand(time(NULL));

    /*Генерация матрицы смежности графа G1*/
    for (int i = 0; i < N1; i++)
        for (int j = i; j < N1; j++)
            if (i == j)
                M1[i][j] = 0;
            else
            {
                int k = rand() % 10;
                if (k > 2)
                    M1[i][j] = 1;
                else 
                    M1[i][j] = 0;
                M1[j][i] = M1[i][j];
            }
    printf("\n\nМатрица смежности графа G1:\n");
    printmatrix(M1, N1);

    /*Генерация матрицы смежности графа G2*/
    for (int i = 0; i < N2; i++)
        for (int j = i; j < N2; j++)
            if (i == j)
                M2[i][j] = 0;
            else
            {
                int k = rand() % 10;
                if (k > 2)
                    M2[i][j] = 1;
                else
                    M2[i][j] = 0;
                M2[j][i] = M2[i][j];
            }
    printf("\n\nМатрица смежности графа G2:\n");
    printmatrix(M2, N2);

    int operation;

    LabelMenu: 
    printf("\n\nВозможные операции:\n");
    printf("\t\t1) - Отождествление вершин (для графа G1)\n");
    printf("\t\t2) - Стягивание ребра (для графа G2)\n");
    printf("\t\t3) - Расщепление вершины (для графа G1)\n");
    printf("\t\t4) - Объединение графов G1 и G2\n");
    printf("\t\t5) - Пересечение графов G1 и G2\n");
    printf("\t\t6) - Кольцевая сумма графов G1 и G2\n");
    printf("\t\t7) - Декартово произведение графов G1 и G2\n");
    printf("\n\t1000 - Завершение программы\n\n");
    printf("Номер операции: ");
    scanf_s("%d", &operation);

    switch (operation)
    {
        /*Отождествление вершин*/
        case 1:
            int vertexmin, vertexmax;

            //Считывание номеров вершин
            printf("\n\nНомер первой вершины для отождествления:");
            scanf_s("%d", &vertexmin);
            printf("\nНомер второй вершины для отождествления:");
            scanf_s("%d", &vertexmax);

            while (vertexmin > N1 || vertexmax > N1)
            {
                printf("\n\nНичего себе какое число! Такого нет!\n Нужно ввести другое!\n");
                printf("\n\nНомер первой вершины для отождествления:");
                scanf_s("%d", &vertexmin);
                printf("\nНомер второй вершины для отождествления:");
                scanf_s("%d", &vertexmax);
            }

            //Создание массива для записи результата
            M1result = (int**)malloc((N1 - 1) * sizeof(int*));
            for (int i = 0; i < N1 - 1; i++)
                M1result[i] = (int*)malloc((N1 - 1) * sizeof(int));

            //Отождествление вершин
            M1result = otozh(vertexmin, vertexmax, M1, N1);
           
            //Вывод результата
            printf("\n\nРезультат:\n");
            printmatrix(M1result, N1-1);

            //Возвращение в меню
            goto LabelMenu;
            break;


        /*Стягивание ребра*/
        case 2:
            int vertexstart, vertexend;

            //Считывание номеров вершин
            printf("\n\nНомер первой вершины инцидентной ребру:");
            scanf_s("%d", &vertexstart);
            printf("\nНомер второй вершины инцидентной ребру:");
            scanf_s("%d", &vertexend);

            while (vertexstart > N2 || vertexend > N2)
            {
                printf("\n\nТаких вершин не существует или ребра между ними нет!\n Нужно указать другие!\n");
                printf("\nНомер первой вершины инцидентной ребру:");
                scanf_s("%d", &vertexstart);
                printf("\nНомер второй вершины инцидентной ребру:");
                scanf_s("%d", &vertexend);
            }

            //Создание масива для записи результата
            M2result = (int**)malloc((N2 - 1) * sizeof(int*));
            for (int i = 0; i < N2 - 1; i++)
                M2result[i] = (int*)malloc((N2 - 1) * sizeof(int));

            //Удаление ребра 
            M2[vertexstart][vertexend] = 0;
            M2[vertexend][vertexstart] = 0;

            //Отождествление вершин, инцидентных ребру
            M2result = otozh(vertexstart, vertexend, M2, N2);
            
            //Удаление петли
            for (int i = 0; i < N2 - 1; i++)
                M2result[i][i] = 0;

            //Вывод результата
            printf("\n\nРезультат:\n");
            printmatrix(M2result, N2-1);
            
            //Возвращение в меню
            goto LabelMenu;
            break;


        /*Расщепление вершины*/
        case 3:
            int vertex;

            //Считывание номеров вершин
            printf("\nНомер вершины для расщепления:");
            scanf_s("%d", &vertex);

            while (vertex > N1)
            {
                printf("\n\nТакой вершины не существует\n Нужно указать другую!\n");
                printf("\nНомер вершины для расщепления:");
                scanf_s("%d", &vertex);
            }

            vertex--;
            //Создание массива для хранения результата
            M3result = (int**)malloc((N1 + 1) * sizeof(int*));
            for (int i = 0; i < N1 + 1; i++)
                M3result[i] = (int*)malloc((N1 + 1) * sizeof(int));

            for (int i = 0; i < N1 + 1; i++)
                for (int j = 0; j < N1 + 1; j++)
                {
                    if (i < vertex && j < vertex)
                        M3result[i][j] = M1[i][j];
                    if (i < vertex && j > vertex + 1)
                    {
                        M3result[i][j] = M1[i][j-1];
                        M3result[j][i] = M1[i][j-1];
                    }
                    if (i > vertex+1 && j > vertex+1)
                    {
                        M3result[i][j] = M1[i-1][j-1];
                        M3result[j][i] = M1[i-1][j-1];
                    }
                }

                for (int i = 0; i < N1 + 1; i++)
                {
                    if (i < vertex)
                    {
                        M3result[vertex][i] = M1[vertex][i];
                        M3result[i][vertex] = M1[vertex][i];

                        M3result[vertex+1][i] = 0;
                        M3result[i][vertex+1] = 0;
                    }
                    if (i > vertex + 1)
                    {
                        M3result[vertex + 1][i] = M1[vertex][i - 1];
                        M3result[i][vertex + 1] = M1[vertex][i - 1];

                        M3result[vertex][i] = 0;
                        M3result[i][vertex] = 0;
                    }
                }
                //Элементы на главной диагонали
                M3result[vertex][vertex] = 0;
                M3result[vertex + 1][vertex + 1] = 0;
                //Ребро между новыми вершинами
                M3result[vertex][vertex + 1] = 1;
                M3result[vertex + 1][vertex] = 1;

            //Вывод результата
            printf("\n\nРезультат:\n");
            printmatrix(M3result, N1+1);

            //Возвращение в меню
            goto LabelMenu;
            break;


        /*Объединение графов*/
        case 4:
            UnionResult = (int**)malloc((N1) * sizeof(int*));
            for (int i = 0; i < N1; i++)
                UnionResult[i] = (int*)malloc((N1) * sizeof(int));

            for (int i = 0; i < N1; i++)
                for (int j = 0; j < N1; j++)
                    if (M1[i][j] == 1 || M2[i][j] == 1)
                        UnionResult[i][j] = 1;
                    else
                        UnionResult[i][j] = 0;

            printmatrix(UnionResult, N1);
            goto LabelMenu;
            break;


        /*Пересечение графов*/
        case 5:
            ProductResult = (int**)malloc((N1) * sizeof(int*));
            for (int i = 0; i < N1; i++)
                ProductResult[i] = (int*)malloc((N1) * sizeof(int));

            for (int i = 0; i < N1; i++)
                for (int j = 0; j < N1; j++)
                    if (M1[i][j] == 1 && M2[i][j] == 1)
                        ProductResult[i][j] = 1;
                    else
                        ProductResult[i][j] = 0;

            //Вывод результата
            printf("\n\nРезультат:\n");
            printmatrix(ProductResult, N1);

            //Возвращение в меню
            goto LabelMenu;
            break;


        /*Кольцевая сумма графов*/
        case 6:
            SumResult = (int**)malloc((N1) * sizeof(int*));
            for (int i = 0; i < N1; i++)
                SumResult[i] = (int*)malloc((N1) * sizeof(int));

            for (int i = 0; i < N1; i++)
                for (int j = 0; j < N1; j++)
                    if (M1[i][j] + M2[i][j] == 1)
                        SumResult[i][j] = 1;
                    else
                        SumResult[i][j] = 0;

            //Вывод результата
            printf("\n\nРезультат:\n");
            printmatrix(SumResult, N1);

            //Возвращение в меню
            goto LabelMenu;
            break;


        /*Декартово произведение графов*/
        case 7:
            
            //Вывод результата
            printf("\n\nРезультат:\n");
            for (int i = 0; i < N1; i++)
                for (int k = 0; k < N2; k++)
                {
                    printf("\n");
                    for (int j = 0; j < N1; j++)
                        for (int l = 0; l < N2; l++)
                        {

                            if (i == j)
                                printf("%3d ", M2[k][l]);
                            else if (k == l)
                                printf("%3d ", M1[i][j]);
                            else if (i != j && k != l)
                                printf("%3d ", 0);
                        }
                }

            //Возвращение в меню
            goto LabelMenu;
            break;


        /*Выход из программы*/
        case 1000:
                exit;
            break;
    }
    
    //Освобождение памяти
    free(M1);
    free(M2);
    free(M1result);
    free(M2result);
    free(M3result);
    free(UnionResult);
    free(ProductResult);
    free(SumResult);
    getchar();
}


/*Функция выполняет отождествление вершин графа*/
/*На вход получает номера отождествляемх вершин, матрицу смежности графа, размерность матрицы смежности*/
int** otozh(int vertexmin, int vertexmax, int** matrix, int size)
{
    //Определение вершины с меньшим номером
    if (vertexmin > vertexmax)
    {
        int change = vertexmax;
        vertexmax = vertexmin;
        vertexmin = change;
    }

    vertexmin--; vertexmax--;

    //Создание массива для результата
    M1result = (int**)malloc((size - 1) * sizeof(int*));
    for (int i = 0; i < size - 1; i++)
        M1result[i] = (int*)malloc((size - 1) * sizeof(int));

    //Отождествление
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (i < vertexmax && j < vertexmax)
                M1result[i][j] = matrix[i][j];
            if (i < vertexmax && j > vertexmax - 1 && j != size - 1)
            {
                M1result[i][j] = matrix[i][j + 1];
                M1result[j][i] = matrix[i][j + 1];
            }
            if (j > vertexmax && i > vertexmax)
                M1result[i - 1][j - 1] = matrix[i][j];
        }
    for (int i = 0; i < size; i++)
        if (i != vertexmax && (matrix[vertexmax][i] == 1 || matrix[vertexmin][i] == 1))
        {
            int j = i;
            if (j > vertexmax)
                j--;
            M1result[vertexmin][j] = 1;
            M1result[j][vertexmin] = 1;
        }
    return M1result;
}

/*Функция выводит элементы квадратной матрицы на экран в виде таблицы*/
/*На вход получает массив и его размер*/
void printmatrix(int** source, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%3d ", source[i][j]);
        printf("\n");
    }
}
