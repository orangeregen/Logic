#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int N;
int* visit;
int** G;

void DFS(int num);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Введите количество вершин графа: ");
    scanf_s("%d", &N);

    visit = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        visit[i] = 0;

    G = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        G[i] = (int*)malloc(N * sizeof(int));
  
    srand(time(NULL));

    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (i == j)
                G[i][j] = 0;
            else
            {
                G[i][j] = rand() % 2;
                G[j][i] = G[i][j];
            }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%3d ", G[i][j]);
        printf("\n");
    }
     
    int num;
    printf("\nВведите номер вершины, с которой следует начать обход: ");
    scanf_s("%d", &num);
    printf("Порядок обхода: ");
    DFS(num-1);
    
    getchar();
}

void DFS(int num)
{
    printf("%d ", num+1);
    visit[num] = 1;
    for (int i = 0; i < N; i++)
        if (G[num][i] == 1 && visit[i] == 0)
            DFS(i);
}
    
