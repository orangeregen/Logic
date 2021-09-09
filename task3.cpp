#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <ctime>

int main()
{
	setlocale(LC_ALL, "Rus");
	int i, N;
	int *arr;
	printf("Введите размер массива: ");
	scanf_s("%d", &N);
	arr = (int*)malloc(N * sizeof(int));
	srand(time(NULL));
	for (i = 0; i < N; i++)
	{
		arr[i] = rand() % 100;
	}
	printf("Массив: ");
	for (i = 0; i < N; i++)
		printf("%d ", arr[i]);
}