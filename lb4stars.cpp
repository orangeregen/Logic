#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stack>

using namespace std;

typedef struct Node {
    int vertex;
    struct	Node* next;
} Node;

int N;
int* visit;
int** G;
int* component;


void printmatrix(int** source, int size);
void AddFirst(Node** head, int data);
void AddNewAfter(Node* head, int m);
Node* FindLast(Node* head);
void AddLast(Node* head, int data);
void CreateList(int** matrix, Node** head, int N);

void DFS(int num);
void DFScomp(int num, int comp);
void DFSlist(Node** list, int num);
void DFSstack(int num);

int main()
{
    stack <int> stack;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    /*Обход в глубину графа, представленного матрицей смежности*/
    printf("Введите количество вершин графа: ");
    scanf_s("%d", &N);

    visit = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        visit[i] = 0;

    component = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        component[i] = 0;

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
                if (rand() % 10 < 3)
                    G[i][j] = 1;
                else
                    G[i][j] = 0;
                G[j][i] = G[i][j];
            }

    printf("\nМатрица смежности графа G:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%3d ", G[i][j]);
        printf("\n");
    }
     
    printf("\n\nОбход в глубину графа G, представленного матрицей смежности");
    int num;
    printf("\nВведите номер вершины, с которой следует начать обход: ");
    scanf_s("%d", &num);
    printf("Порядок обхода: ");
    DFS(num - 1);
    for (int i = 0; i < N; i++)
        visit[i] = 0;


    /*Обход в глубину графа, представленного списками смежности*/
    Node** listG = (Node**)malloc(N * sizeof(Node*));
    for (int i = 0; i < N; i++)
        listG[i] = NULL;

    CreateList(G, listG, N);

    printf("\n\nОбход в глубину графа G, представленного списками смежности");
    printf("\nВведите номер вершины, с которой следует начать обход: ");
    scanf_s("%d", &num);
    num--;

    printf("Порядок обхода: ");
    DFSlist(listG, num);

    for (int i = 0; i < N; i++)
        visit[i] = 0;

    /*Обход в глубину графа, представленного матрицей смежности смежности, с помощью нерекурсивной функции*/
    printf("\n\nОбход в глубину графа G, представленного матрицей смежности, с помощью нерекурсивной функции");
    printf("\nВведите номер вершины, с которой следует начать обход: ");
    scanf_s("%d", &num);
    num--;
    printf("Порядок обхода: ");
    DFSstack(num);

    for (int i = 0; i < N; i++)
        visit[i] = 0;

   
    /*Поиск компонент связности в графе, представленном матрицей смежности*/
    printf("\n\nДоработка: поиск компонент связности");
    printf("\nВведите номер вершины, с которой следует начать поиск компонент связности: ");
    scanf_s("%d", &num);
    num--;

    int comp = 1;
    printf("\n\nКомпонента %d: ", comp);
    DFScomp(num, comp);
    for (int i = 0; i < N; i++)
        if (visit[i] == 0)
        {
            comp++;
            printf("\n\nКомпонента %d: ", comp);
            DFScomp(i, comp);
        }

    getchar();
}


void DFS(int num)
{
    printf("%d ", num + 1);
    visit[num] = 1;
    for (int i = 0; i < N; i++)
        if (G[num][i] == 1 && visit[i] == 0)
            DFS(i);
}

void DFSlist(Node** list, int num)
{
    printf("%2d ", num + 1);
    visit[num] = 1;
    Node* tmp_node = list[num];
    while (tmp_node) //Просматриваем текущую вершину
    {
        if (visit[tmp_node->vertex] == 0)
            DFSlist(list, tmp_node->vertex); //Если вершина не посещена, передаем ее адрес и номер, вызовом DFSlist делаем ее текущей
        tmp_node = tmp_node->next;
    }
}

void DFScomp(int num, int comp)
{
    printf("%d ", num+1);
    visit[num] = comp;
    for (int i = 0; i < N; i++)
        if (G[num][i] == 1 && visit[i] == 0)
            DFScomp(i, comp);
}


void DFSstack(int num) 
{
    stack <int> stack;
    stack.push(num);  //Помещаем в стек вершину v
    while (!stack.empty())  //Пока стек не пуст
    {
        if (visit[stack.top()] == 0)    //Если вершина на верхушке стека не посещена
        {
            visit[stack.top()] = 1;
            printf("%d ", stack.top() + 1);
            num = stack.top();
            stack.pop();
            for (int i = N - 1; i >= 0; i--)
                if (G[num][i] == 1 && visit[i] == 0)  //Если найдена смежная непосещенная вершина
                    stack.push(i);                       //Добавление в стек
        }
        else
            stack.pop();
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
    last->next = NewNode; //Указатель на новый элемент записывается последним элементом списка
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
