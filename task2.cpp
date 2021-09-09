#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <ctime>


int main()
{
	setlocale(LC_ALL, "Rus");
	int i;
	int arr[10] = {};
	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}
	printf("Массив: ");
	for (i = 0; i < 10; i++)
		printf("%d ", arr[i]);
}