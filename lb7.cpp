#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <queue>
using namespace std;

int** G, ** ORG;
int* Gvisited, * ORGvisited;
int N, ORGN;
int num;

void DistanceBFS(int num, int** G, int* visited, int N);
void printmatrix(int** source, int size);
void printdistance(int* visited, int N);

int main()

{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		/*Поиск расстояний в неориентированном графе, представленном матрицей смежности, на основе обхода в ширину*/
		printf("Введите количество вершин графа: ");
		scanf_s("%d", &N);

		G = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++)
			G[i] = (int*)malloc(N * sizeof(int));

		Gvisited = (int*)malloc(N * sizeof(int));
		for (int i = 0; i < N; i++)
			Gvisited[i] = MAXINT;

		srand(time(NULL));
		for (int i = 0; i < N; i++)
			for (int j = i; j < N; j++)
				if (i == j)
					G[i][j] = 0;
				else
				{
					if (rand() % 10 < 4)
						G[i][j] = rand() % 9 + 1;
					else
						G[i][j] = 0;
					G[j][i] = G[i][j];
				}

		printf("\nМатрица смежности графа G:\n");
		printmatrix(G, N);

		printf("\n\n\nПоиск расстояний на основе обхода в ширину неориентированного графа, представленного матрицей смежности");
		printf("\nВведите номер вершины, с которой следует начать: ");
		scanf_s("%d", &num);

		while (num > N)
		{
			printf("Такой вершины не существует! Нужно ввести другой номер!\nНомер вершины старта: ");
			scanf_s("%d", &num);
		}

		printf("\n\nВершина старта: %d", num);
		DistanceBFS(num - 1, G, Gvisited, N);
		printdistance(Gvisited, N);


		/*Поиск расстояний в ориентированном графе, представленном матрицей смежности, на основе обхода в ширину*/
		printf("\n\nВведите количество вершин орграфа: ");
		scanf_s("%d", &ORGN);

		ORG = (int**)malloc(ORGN * sizeof(int*));
		for (int i = 0; i < ORGN; i++)
			ORG[i] = (int*)malloc(ORGN * sizeof(int));

		ORGvisited = (int*)malloc(N * sizeof(int));
		for (int i = 0; i < N; i++)
			ORGvisited[i] = MAXINT;

		for (int i = 0; i < ORGN; i++)
			for (int j = 0; j < ORGN; j++)
				if (i == j)
					ORG[i][j] = 0;
				else
				{
					if (rand() % 10 < 2)
						ORG[i][j] = rand() % 9 + 1;
					else
						ORG[i][j] = 0;
				}

		printf("\nМатрица смежности орграфа:\n");
		printmatrix(ORG, ORGN);

		printf("\n\n\nПоиск расстояний на основе обхода в ширину ориентированного графа, представленного матрицей смежности");
		printf("\nВведите номер вершины, с которой следует начать: ");
		scanf_s("%d", &num);
		while (num > ORGN)
		{
			printf("Такой вершины не существует! Нужно ввести другой номер!\nНомер вершины старта: ");
			scanf_s("%d", &num);
		}

		printf("\n\nВершина старта: %d", num);
		DistanceBFS(num - 1, ORG, ORGvisited, ORGN);
		printdistance(ORGvisited, ORGN);
		
		int check = 0;
		while (check != -1)
		{
			for (int i = 0; i < ORGN; i++)
				ORGvisited[i] = MAXINT;

			printf("\n\nДля выхода из программы введите -1");
			printf("\nДля проверки другой вершины введите её номер: ");
			scanf_s("%d", &check);
			while (check > ORGN)
			{
				printf("Такой вершины не существует! Нужно ввести другой номер!\nНомер вершины старта: ");
				scanf_s("%d", &check);
			}

			if (check == -1)
				break;
			else
				DistanceBFS(check - 1, ORG, ORGvisited, ORGN);
				printdistance(ORGvisited, ORGN);
		}
}


/*Поиск расстояний в графе, представленном матрицей смежности, на основе обхода в ширину*/
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

/*Функция выводит на экран квадратную матрицу*/
void printmatrix(int** source, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%3d ", source[i][j]);
		printf("\n");
	}
}

void printdistance(int* visited, int N)
{
	for (int i = 0; i < N; i++)
	{
			if (visited[i] == MAXINT)
				printf("\nПути до вершины %d не существует ;(", i + 1);
			else if (visited[i] != 0)
				printf("\nРасстояние до вершины %d: %d", i + 1, visited[i]);
	}
}
