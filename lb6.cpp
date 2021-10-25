#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <queue>
using namespace std;

typedef struct Node {
	int vertex;
	struct	Node* next;
} Node;

int** G;
int* visited;
int N;
int num, maxdepth, depth;

void printmatrix(int** source, int size);
void printdistance(int maxdepth);
void AddFirst(Node** head, int data);
void AddNewAfter(Node* head, int m);
Node* FindLast(Node* head);
void AddLast(Node* head, int data);
void CreateList(int** matrix, Node** head, int N);

void DistanceBFS(int num);
void DistanceBFSlist(Node** head, int num);
void DistanceDFS(int num, int depth);
void DistanceDFSlist(Node** list, int num, int depth);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	clock_t start, end;

	/*Поиск расстояний в графе, представленном матрицей смежности*/
	printf("Введите количество вершин графа: ");
	scanf_s("%d", &N);

	G = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		G[i] = (int*)malloc(N * sizeof(int));

	visited = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		visited[i] = -1;

	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (i == j)
				G[i][j] = 0;
			else
			{
				if (rand() % 10 < 4)
					G[i][j] = 1;
				else
					G[i][j] = 0;
				G[j][i] = G[i][j];
			}

	printf("\nМатрица смежности графа G:\n");
	printmatrix(G, N);

	printf("\n\n\nПоиск расстояний на основе обхода в ширину графа, представленного матрицей смежности");
	printf("\nВведите номер вершины, с которой следует начать: ");
	scanf_s("%d", &num);
	printf("\nВершина начала: %d", num);
	num--;
	start = clock();
	DistanceBFS(num);
	end = clock();
	printf("\n\nВремя работы: %f сек", ((float)end - (float)start) / CLOCKS_PER_SEC);

	printdistance(maxdepth);


	/*Обход в ширину графа, представленного списками смежности*/
	Node** listG = (Node**)malloc(N * sizeof(Node*));
	for (int i = 0; i < N; i++)
		listG[i] = NULL;

	CreateList(G, listG, N);

	for (int i = 0; i < N; i++)
		visited[i] = -1;
	maxdepth = 0;

	printf("\n\n\nПоиск расстояний на основе обхода в ширину графа, представленного списками смежности");
	printf("\nВведите номер вершины, с которой следует начать: ");
	scanf_s("%d", &num);
	printf("\nВершина начала: %d", num);
	num--;
	DistanceBFSlist(listG, num);

	/*for (int i = 1; i <= maxdepth; i++)
	{
		printf("\n\nВершины уровня %d: ", i);
		for (int j = 0; j < N; j++)
		{
			if (visited[j] == i)
				printf("%d ", j + 1);
		}
	}*/
	printdistance(maxdepth);

	for (int i = 0; i < N; i++)
		visited[i] = -1;
	maxdepth = 0;
	printf("\n\n\nПоиск расстояний на основе обхода в глубину графа, представленного матрицей смежности");
	printf("\nВведите номер вершины, с которой следует начать: ");
	scanf_s("%d", &num);
	printf("\nВершина начала: %d", num);
	num--;
	start = clock();
	DistanceDFS(num, 0);
	end = clock();
	printf("\n\nВремя работы: %f сек", ((float)end - (float)start) / CLOCKS_PER_SEC);

	printdistance(maxdepth);


	for (int i = 0; i < N; i++)
		visited[i] = -1;
	maxdepth = 0;
	Node** listGRAPH = (Node**)malloc(N * sizeof(Node*));
	for (int i = 0; i < N; i++)
		listGRAPH[i] = NULL;

	CreateList(G, listGRAPH, N);

	printf("\n\n\nПоиск расстояний на основе обхода в ширину графа, представленного списками смежности");
	printf("\nВведите номер вершины, с которой следует начать: ");
	scanf_s("%d", &num);
	printf("\nВершина начала: %d", num);
	num--;
	start = clock();
	DistanceDFSlist(listGRAPH, num, 0);
	end = clock();
	printf("\n\nВремя работы: %f сек", ((float)end - (float)start) / CLOCKS_PER_SEC);

	printdistance(maxdepth);
}

void DistanceBFS(int num)
{
	queue <int> q;

	q.push(num);
	visited[num] = 0;
	while (!q.empty())
	{
		num = q.front();
		q.pop();
		for (int i = 0; i < N; i++)
			if (visited[i] == -1 && G[num][i] == 1)
			{
				q.push(i);
				visited[i] = visited[num] + 1;
				if (visited[num] + 1 > maxdepth)
					maxdepth = visited[num] + 1;
			}
	}
}


void DistanceBFSlist(Node** head, int num)
{
	queue <int> q;

	Node** tmp_node = head;
	q.push(tmp_node[num]->vertex);
	visited[tmp_node[num]->vertex] = 0;

	while (!q.empty())
	{
		num = q.front();
		q.pop();
		while (tmp_node[num])
		{
			if (visited[tmp_node[num]->vertex] == -1)
			{
				q.push(tmp_node[num]->vertex);
				visited[tmp_node[num]->vertex] = visited[num] + 1;
				if (visited[num] + 1 > maxdepth)
					maxdepth = visited[num] + 1;
			}
			tmp_node[num] = tmp_node[num]->next;
		}
	}
}


void DistanceDFS(int num, int depth)
{
	visited[num] = depth;
	if (depth + 1 > maxdepth)
		maxdepth = depth;
	for (int i = 0; i < N; i++)
	{
		if (G[num][i] == 1 && visited[i] == -1)
			DistanceDFS(i, depth + 1);
		if (G[num][i] == 1 && visited[i] > depth)
			DistanceDFS(i, depth + 1);
	}
}


void DistanceDFSlist(Node** list, int num, int depth)
{
	visited[num] = depth;
	if (depth > maxdepth)
		maxdepth = depth;

	Node* tmp_node = list[num];

	while (tmp_node)
	{
		if (visited[tmp_node->vertex] == -1)
			DistanceDFSlist(list, tmp_node->vertex, depth + 1);
		if (visited[tmp_node->vertex] > depth + 1)
			DistanceDFSlist(list, tmp_node->vertex, depth + 1);
		tmp_node = tmp_node->next;
	}
}


void printmatrix(int** source, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%3d ", source[i][j]);
		printf("\n");
	}
}


void printdistance(int maxdepth)
{
	for (int i = 1; i <= maxdepth; i++)
	{
		printf("\n\nВершины уровня %d: ", i);
		for (int j = 0; j < N; j++)
		{
			if (visited[j] == i)
				printf("%d ", j + 1);
		}
	}
}


/*Функция добавляет элемент в начало списка*/
void AddFirst(Node** head, int data)
{
	Node* NewNode = (Node*)malloc(sizeof(Node)); // создаем новый элемент
	NewNode->vertex = data;
	NewNode->next = (*head); //присваиваем адрес следующего элемента
	(*head) = NewNode; //Присваиваем указателю head новое значение
}


/*Функция добавляет в список элемент после полученного на вход*/
void AddNewAfter(Node* elem, int m)
{
	Node* tmp;
	tmp = (Node*)malloc(sizeof(Node));
	tmp->vertex = m;
	tmp->next = elem->next;
	elem->next = tmp;
}


/*Функция ищет адрес последнего элемента*/
Node* FindLast(Node* elem)
{
	if (elem == NULL)
		return NULL;
	while (elem->next != NULL)
		elem = elem->next;
	return elem;
}


/*Функция добавляет новый элемент в конец списка*/
void AddLast(Node* head, int data)
{
	Node* last = FindLast(head); //Получение адреса последнего элемента списка
	Node* NewNode = (Node*)malloc(sizeof(Node)); //Выделение памяти под новый элемент
	NewNode->vertex = data;
	NewNode->next = NULL;
	last->next = NewNode; //Указатель на новый элемент записываеся последним элементом списка
}


/*Функция преобразует матрицу смежности в список cвязности*/
void CreateList(int** matrix, Node** head, int N)
{
	for (int i = 0; i < N; i++)
	{
		AddFirst(&head[i], i); //Создание первых элементов списков
		for (int j = 0; j < N; j++)
			if (matrix[i][j] == 1)
				AddLast(head[i], j); //Добавляем в конец списка вершин, смежных с iой вершиной, вершину j
	}
}
