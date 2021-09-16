#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	clock_t start_mul, start_prog, end; // объявляем переменные для определения времени выполнения перемножения матриц и всей программы

	start_prog = clock();
	int i = 0, j = 0, r, N;
	long elem_c;

	printf("Введите размерность матрицы: \n");
	scanf_s("%d", &N);

	int** a = (int**)malloc(N * sizeof(int*));
	int** b = (int**)malloc(N * sizeof(int*));
	int** c = (int**)malloc(N * sizeof(int*));

	for (i = 0; i < N; i++)
	{
		a[i] = (int*)malloc(N * sizeof(int));
		b[i] = (int*)malloc(N * sizeof(int));
		c[i] = (int*)malloc(N * sizeof(int));
	}
	
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < N)
	{
		while (j < N)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < N)
	{
		while (j < N)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	start_mul = clock();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			elem_c = 0;
			for (r = 0; r < N; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}
	end = clock();

	free(a);
	free(b);
	free(c);

	printf("Время выполнения программы: %f сек\n\n", ((float)end - (float)start_prog) / CLOCKS_PER_SEC);
	printf("Время перемножения матриц: %f сек\n\n", ((float)end - (float)start_mul) / CLOCKS_PER_SEC);
	Sleep(20000);
	getchar;
	return(0);
}
