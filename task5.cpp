// Задание 5: написать программу, осуществляющую поиск среди структур student структуру с заданными параметрами(фамилией, именем и т.д.).
#include <stdio.h>
#include <locale>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct student
	{
		char famil[11];
		char name[11], facult[6];
		int Nomzach;
	} stud[10];

	char param[22];
	char search[11];
	int searchzach = 0, somebody = 0;
	
	stud[0] = {"Иванов", "Иван", "ФИТЭ", 19234};
	stud[1] = { "Платонов", "Герман", "ФВТ", 18432};
	stud[2] = { "Семёнов", "Владимир", "ФПТЭТ", 18324};
	stud[3] = { "Шарапов", "Константин", "ФИТЭ", 20243};
	stud[4] = { "Иванов", "Геннадий", "ИФФ", 21423};
	stud[5] = { "Никифорова", "Дарья", "ИФФ", 18638};
	stud[6] = { "Елисеева", "Софья", "ФВТ", 19683};
	stud[7] = { "Тихонова", "Алиса", "ФВТ", 19836};
	stud[8] = { "Васильева", "Октябрина", "ФИТЭ", 21863};
	stud[9] = { "Куликова", "Софья", "ФИТЭ", 20368};
	printf("Доступные параметры: Фамилия, Имя, Факультет, Номер зачетной книжки\n");
	printf("Введите параметр, по которому следует выполнить поиск: ");
	gets_s(param);
	
	while ((strcmp(param, "Фамилия") != 0) && (strcmp(param, "Имя") != 0) && (strcmp(param, "Факультет") != 0) && (strcmp(param, "Номер зачетной книжки") != 0))
	{
		printf("\nТакого параметра не существует!\nДоступные параметры: Фамилия, Имя, Факультет, Номер зачетной книжки\n(Вводить с большой буквы без пробела в конце)\n");
		printf("\nВведите параметр, по которому следует выполнить поиск: ");
		gets_s(param);
	};

	printf("%s студента: ", param);
	if (strcmp(param, "Номер зачетной книжки")==0)
		scanf_s("%d", &searchzach);
	else
		gets_s(search);

	printf("\n\nРезультаты:\n");
	printf("    Фамилия\t\tИмя\tФакультет\tНомер зачетной книжки\n");
	printf("   __________________________________________________________________\n");

	if (searchzach != 0)
	{
		for (int i = 0; i < 10; i++)
			if (stud[i].Nomzach == searchzach)
			{
				somebody = 1;
				printf("%12s\t%12s\t%4s\t\t%d\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			}
	}

	if (strcmp(param, "Фамилия") == 0)
	{
		for (int i = 0; i < 10; i++)
			if (strcmp(search, stud[i].famil) == 0)
			{
				somebody = 1;
				printf("%12s\t%12s\t%4s\t\t%d\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			}
	}

	if (strcmp(param, "Имя") == 0)
	{
		for (int i = 0; i < 10; i++)
			if (strcmp(search, stud[i].name) == 0)
			{
				somebody = 1;
				printf("%12s\t%12s\t%4s\t\t%d\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			}
	}

	if (strcmp(param, "Факультет") == 0)
	{
		for (int i = 0; i < 10; i++)
			if (strcmp(search, stud[i].facult) == 0)
			{
				somebody = 1;
				printf("%12s\t%12s\t%4s\t\t%d\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			}
	}

	if (somebody == 0)
		printf("\n\t\tСтудента с такими данными не нашлось!\n\n\n");
}
