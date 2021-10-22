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

void printmatrix(int** source, int size);
void AddFirst(Node** head, int data);
void AddNewAfter(Node* head, int m);
Node* FindLast(Node* head);
void AddLast(Node* head, int data);
void CreateList(int** matrix, Node** head, int N);

void BFS(int num);
void BFSlist(Node** head, int num);
void BFSqueue(int num);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	clock_t start, end;

	/*Обход в ширину графа, представленного матрицей смежности*/
	printf("Введите количество вершин графа: ");
	scanf_s("%d", &N);
	
	G = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		G[i] = (int*)malloc(N * sizeof(int));

	visited = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		visited[i] = 0;

	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (i == j)
				G[i][j] = 0;
			else
			{
				if (rand() % 10 < 3)
					G[i][j] = 0;
				else
					G[i][j] = 1;
				G[j][i] = G[i][j];
			}

	printf("\nМатрица смежности графа G:\n");
	printmatrix(G, N);
	
	printf("\n\nОбход в ширину графа G, представленного матрицей смежности");
	int num;
	printf("\nВведите номер вершины, с которой следует начать обход: ");
	scanf_s("%d", &num);
	printf("Порядок обхода: ");
	start = clock();
	BFS(num - 1);
	end = clock();
	printf("\n\nВремя обхода: %f сек", ((float)end - (float)start) / CLOCKS_PER_SEC);

	/*Обход в ширину графа, представленного списками смежности*/
	Node** listG = (Node**)malloc(N * sizeof(Node*));
	for (int i = 0; i < N; i++)
		listG[i] = NULL;

	CreateList(G, listG, N);

	printf("\n\nОбход в ширину графа G, представленного списками смежности");
	printf("\nВведите номер вершины, с которой следует начать обход: ");
	scanf_s("%d", &num);
	num--;

	for (int i = 0; i < N; i++)
		visited[i] = 0;
	printf("Порядок обхода: ");
	BFSlist(listG, num);


	/*Обход в ширину графа, представленного матрицей смежности, с помощью самостоятельно реализованной очереди*/
	printf("\n\nОбход в ширину графа G, представленного матрицей смежности, с помощью самостоятельно реализованной очереди");
	printf("\nВведите номер вершины, с которой следует начать обход: ");
	scanf_s("%d", &num);
	num--;

	for (int i = 0; i < N; i++)
		visited[i] = 0;

	printf("Порядок обхода: ");
	start = clock();
	BFSqueue(num);
	end = clock();
	printf("\n\nВремя обхода: %f сек", ((float)end - (float)start) / CLOCKS_PER_SEC);
}

void BFS(int num)
{
	queue <int> q;

	q.push(num);
	visited[num] = 1;
	while (!q.empty()) 
	{
		num = q.front();
		q.pop();
		printf("%d ", num+1);
		for (int i = 0; i < N; i++) 
			if (visited[i] == 0 && G[num][i] == 1) 
			{
				q.push(i);
				visited[i] = 1;
			}
	}
}

void BFSlist(Node** head, int num)
{
	queue <int> q;

	Node**  tmp_node = head;
	q.push(tmp_node[num]->vertex);
	visited[tmp_node[num]->vertex] = 1;

	while (!q.empty())
	{		
			num = q.front();
			q.pop();
			printf("%d ", num + 1);
			while (tmp_node[num])
			{
				if (visited[tmp_node[num]->vertex] == 0)
				{
					q.push(tmp_node[num]->vertex);
					visited[tmp_node[num]->vertex] = 1;
				}
				tmp_node[num] = tmp_node[num]->next;
			}
	}
}


void BFSqueue(int num)
{
	Node* QueueHead = NULL;
	AddFirst(&QueueHead, num);
	visited[num] = 1;

	while (QueueHead)
	{
		num = QueueHead->vertex;
		QueueHead = QueueHead->next;

		printf("%d ", num + 1);

		for (int i = 0; i < N; i++)
			if (visited[i] == 0 && G[num][i] == 1)
			{
				if (QueueHead == NULL)
					AddFirst(&QueueHead, i);
				else
					AddLast(QueueHead, i);
				visited[i] = 1;
			}
	}
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
