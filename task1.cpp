#include <iostream>
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int i, rez;
	int min, max;
	int arr[10] = { 16, 1, 28, 12, 9, 4, 11, 16, 6, 30 };
	min = arr[0];
	max = arr[0];
	printf("Массив: ");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
		if (arr[i] >= max)
			max = arr[i];
		if (arr[i] <= min)
			min = arr[i];
	}	
	rez = max - min;
	printf("\nРазница между максимальным и минимальным элементом массива: %d", rez);
}
