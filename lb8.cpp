#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <queue>
using namespace std;

int** GS, ** GI;
int* dist, * ecc, * deg;
int N, M = 0, diam = -1, rad = MAXINT;
int num;

void DistanceBFS(int num, int** G, int* visited, int N);
void printmatrix(int** source, int size1, int size2);
int main()

{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	/*Задание 1: поиск эксцентриситетов, радиуса, диаметра, множеств периферийных и центральных вершин, изолированные, концевых и доминирующих вершин*/
	/*Граф представлен матрицей смежности*/
	printf("Введите количество вершин графа: ");
	scanf_s("%d", &N);

	GS = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		GS[i] = (int*)malloc(N * sizeof(int));

	dist = (int*)malloc(N * sizeof(int));	//Массив расстояний
	ecc = (int*)malloc(N * sizeof(int));	//Массив эксцентриситетов вершин
	deg = (int*)malloc(N * sizeof(int));	//Масиив степеней вершин
	for (int i = 0; i < N; i++)
	{
		dist[i] = MAXINT;
		ecc[i] = 0;
		deg[i] = 0;
	}
		
	/*Генерация матрицы смежности и вывод ее на экран*/
	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (i == j)
				GS[i][j] = 0;
			else
			{
				if (rand() % 10 < 2)
				{
					GS[i][j] = rand() % 9 + 1;
					M++;	//Считаем количество ребер для матрицы инцидентности 
				}
				else
					GS[i][j] = 0;
				GS[j][i] = GS[i][j];
			}

	printf("\nМатрица смежности графа G:\n");
	printmatrix(GS, N, N);
 
	/*Поиск эксцентриситетов, радиуса и диаметра*/
	for (int i = 0; i < N; i++)
	{
		printf("\n\nРасстояния от вершины %d до остальных: ", i + 1);
		DistanceBFS(i, GS, dist, N);
		for (int j = 0; j < N; j++)
		{
			if (dist[j] != MAXINT)
			{
				printf("%d ", dist[j]);
				if (dist[j] > ecc[i])
					ecc[i] = dist[j];
			}
			else
				printf(" - ");
		}

		printf("\nЭксцентриситет вершины %d: %d ", i+1, ecc[i]);

		if (ecc[i] < rad && ecc[i] > 0)
			rad = ecc[i];
		if (ecc[i] > diam)
			diam = ecc[i];

		dist = (int*)malloc(N * sizeof(int));
		for (int i = 0; i < N; i++)
			dist[i] = MAXINT;
	}

	printf("\n\nРадиус: %d", rad);
	printf("\nДиаметр: %d", diam);

	/*Поиск множеств центральных и периферийных вершин*/
	printf("\n\nЦентральные вершины: ");
	for (int i = 0; i < N; i++)
		if (ecc[i] == rad)
			printf("%d ", i + 1);

	printf("\nПериферийные вершины: ");
	for (int i = 0; i < N; i++)
		if (ecc[i] == diam)
			printf("%d ", i + 1);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			if (GS[i][j] != 0)
				deg[i]++;
	}

	/*Поиск изолированных, концевых и доминирующих вершин; вывод результатов на экран*/
	printf("\n\nИзолированные вершины: ");
	for (int i = 0; i < N; i++)
		if (deg[i] == 0)
			printf("%d ", i+1);

	printf("\nКонцевые вершины: ");
	for (int i = 0; i < N; i++)
		if (deg[i] == 1)
			printf("%d ", i + 1);

	printf("\nДоминирующие вершины: ");
	for (int i = 0; i < N; i++)
		if (deg[i] == N - 1)
			printf("%d ", i + 1);



	/*Задание 2: поиск радиуса, диаметра, множеств периферийных и центральных вершин*/
	/*Граф представлен матрицей инцидентности GI[N][M], где N - количество вершин, M - количество ребер*/
	GI = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		GI[i] = (int*)malloc(M * sizeof(int));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			GI[i][j] = 0;

	int m = 0;
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (GS[i][j] != 0)
			{
				GI[i][m] = GS[i][j];
				GI[j][m] = GS[i][j];
				m++;
			}

	printf("\n\nМатрица инцидентности графа G: \n");
	printmatrix(GI, N, M);

}

void DistanceBFS(int num, int** G, int* visited, int N)
{
	queue <int> q;

	q.push(num);
	visited[num] = 0;
	while (!q.empty())
	{
		num = q.front();
		q.pop();
		for (int i = 0; i < N; i++)
			if (visited[i] > visited[num] + G[num][i] && G[num][i] > 0)
			{
				q.push(i);
				visited[i] = visited[num] + G[num][i];
			}
	}
}

/*Функция выводит на экран матрицу*/
void printmatrix(int** source, int size1, int size2)
{
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
			printf("%3d ", source[i][j]);
		printf("\n");
	}
}