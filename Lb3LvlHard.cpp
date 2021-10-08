#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct Node {
	int vertex;
	struct	Node* next;
} Node;

int ** M1, ** M2;
int N1, N2 = 0;


void printmatrix(int** source, int size);
void AddFirst(Node** head, int data);
void AddNewAfter(Node* head, int m);
Node* FindLast(Node* head);
void AddLast(Node* head, int data);
void CreateList(int** a, Node** head, int n);
int Delete(Node** elem);
void HeadsClean(Node** head, int n);
void printlist(Node* head);
//void printlist(Node* head);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("Введите количество вершин графа G1: ");
	scanf_s("%d", &N1);

	printf("Введите количество вершин графа G2: ");
	scanf_s("%d", &N2);

	/*Выделение пямати подо всё*/
	M1 = (int**)malloc(N1 * sizeof(int*));
	for (int i = 0; i < N1; i++)
		M1[i] = (int*)malloc(N1 * sizeof(int));

	M2 = (int**)malloc(N2 * sizeof(int*));
	for (int i = 0; i < N2; i++)
		M2[i] = (int*)malloc(N2 * sizeof(int));

	Node** listG1 = (Node**)malloc(N1 * sizeof(Node*));
	for (int i = 0; i < N1; i++)
		listG1[i] = NULL;

	Node** listG2 = (Node**)malloc(N2 * sizeof(Node*));
	for (int i = 0; i < N2; i++)
		listG2[i] = NULL;

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

	/*Преобразование матрицы смежности в списки связности для графа G1*/
	CreateList(M1, listG1, N1);
	/*Вывод списков*/
	printf("\n\nСписок смежности графа G1:\n");
	for (int i = 0; i < N1; i++)
		printlist(listG1[i]);
	printf("\n\n");


	/*Преобразование матрицы смежности в списки связности для графа G2*/
	CreateList(M2, listG2, N2);
	/*Вывод списков*/
	printf("Список смежности графа G2:\n");
	for (int i = 0; i < N2; i++)
		printlist(listG2[i]);
	printf("\n\n");



	///*Отождествление вершин*/
	//int vertexmin, vertexmax;

	////Считывание номеров вершин
	//printf("\n\nНомер первой вершины для отождествления:");
	//scanf_s("%d", &vertexmin);
	//printf("\nНомер второй вершины для отождествления:");
	//scanf_s("%d", &vertexmax);

	//while (vertexmin > N1 || vertexmax > N1)
	//{
	//	printf("\n\nНичего себе какое число! Такого нет!\n Нужно ввести другое!\n");
	//	printf("\n\nНомер первой вершины для отождествления:");
	//	scanf_s("%d", &vertexmin);
	//	printf("\nНомер второй вершины для отождествления:");
	//	scanf_s("%d", &vertexmax);
	//}

	////Определение вершины с меньшим номером
	//if (vertexmin > vertexmax)
	//{
	//	int change = vertexmax;
	//	vertexmax = vertexmin;
	//	vertexmin = change;
	//}

	//vertexmax--; vertexmin--;

	//listG1[vertexmax] = NULL;

	//for (int i = vertexmax + 1; i < N1; i++)
	//	listG1[i]->vertex--;

	//Node* search = listG1[vertexmin];
	//while (search->next->vertex < vertexmin)
	//	search = search->next;
	//AddNewAfter(search, vertexmin);
	//
	//for (int i = 0; i < N1; i++ )
	//{
	//	if (i != vertexmax)
	//	{
	//	
	//		Node* bigger = listG1[i];
	//		while (bigger != FindLast(listG1[i]))
	//		{
	//			if (bigger->vertex == vertexmax)
	//				Delete(&bigger);
	//			else if (bigger->vertex > vertexmax)
	//				bigger->vertex = bigger->vertex - 1;
	//			bigger = bigger->next;
	//		}
	//		/*
	//		if (bigger == NULL)
	//			goto LabelBLYA;
	//		else if (bigger->vertex == vertexmax)
	//		{
	//			Delete(&bigger);
	//			bigger = bigger->next;
	//		}
	//		else if (bigger->vertex > vertexmax)
	//		{
	//			bigger->vertex = bigger->vertex - 1;
	//			bigger = bigger->next;
	//		}
	//		else if (bigger->vertex < vertexmax)
	//			bigger = bigger->next;*/
	//	}
	//}

	///*Вывод списков*/
	//printf("\n\nСписок смежности графа G1:\n");
	//for (int i = 0; i < N1; i++)
	//	if (i != vertexmax)
	//		printlist(listG1[i]);
	//printf("\n\n");
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
	{
		elem = elem->next;
		/*if (elem->next = NULL)
			return NULL;*/
	}
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


/*Функция удаляет узел, адрес на который получает*/
int Delete(Node** elem) 
{
	Node* prev = NULL;
	int val;
	prev = (*elem); //передаем во временную переменную prev адрес
	val = prev->vertex;
	(*elem) = (*elem)->next; //в head кладем адрес следующего узла
	free(prev); //очищаем временную переменную prev
	return val;
}


void HeadsClean(Node** head, int n)
{
	for (int i = 0; i < n; i++)
		head[i] = NULL;
}


void printlist(Node* head)
{
	printf("\n");
	while (head) {
		printf("%2d", head->vertex + 1);
		if (head->next != NULL)
			printf(" ->");
		head = head->next;
	}
	printf("\n");
}
