// Задание 5: написать программу, осуществляющую поиск среди структур student структуру с заданными параметрами(фамилией, именем и т.д.).

#include "stdafx.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct student
	{
		char famil[11];
		char name[11], facult[6];
		char Nomzach[6];
	} stud[10];

	char param[22];
	char search[11];
	int searchzach = 0, somebody = 0;
	

	strcpy(stud[0].famil, "Иванов"); strcpy(stud[0].name, "Иван");strcpy(stud[0].facult, "ФВТ");strcpy(stud[0].Nomzach, "12345");
	strcpy(stud[1].famil, "Платонов"); strcpy(stud[1].name, "Герман");strcpy(stud[1].facult, "ФВТ");strcpy(stud[1].Nomzach, "18423");
	strcpy(stud[2].famil, "Семёнов"); strcpy(stud[2].name, "Владимир");strcpy(stud[2].facult, "ФПТЭТ");strcpy(stud[2].Nomzach, "18324");
	strcpy(stud[3].famil, "Шарапов"); strcpy(stud[3].name, "Константин");strcpy(stud[3].facult, "ФИТЭ");strcpy(stud[3].Nomzach, "20243");
	strcpy(stud[4].famil, "Иванов"); strcpy(stud[4].name, "Геннадий");strcpy(stud[4].facult, "ИФФ");strcpy(stud[4].Nomzach, "21423");
	strcpy(stud[5].famil, "Никифорова"); strcpy(stud[5].name, "Дарья");strcpy(stud[5].facult, "ИФФ");strcpy(stud[5].Nomzach, "18638");
	strcpy(stud[6].famil, "Елисеева"); strcpy(stud[6].name, "Софья");strcpy(stud[6].facult, "ФВТ");strcpy(stud[6].Nomzach, "19683");
	strcpy(stud[7].famil, "Тихонова"); strcpy(stud[7].name, "Алиса");strcpy(stud[7].facult, "ФВТ");strcpy(stud[7].Nomzach, "19836");
	strcpy(stud[8].famil, "Васильева"); strcpy(stud[8].name, "Октябрина");strcpy(stud[8].facult, "ФИТЭ");strcpy(stud[8].Nomzach, "21863");
	strcpy(stud[9].famil, "Куликова"); strcpy(stud[9].name, "Софья");strcpy(stud[9].facult, "ФИТЭ");strcpy(stud[9].Nomzach, "16345");
	//printf("Доступные параметры: Фамилия, Имя, Факультет, Номер зачетной книжки\n");
	/*printf("Введите параметр, по которому следует выполнить поиск: ");
	gets_s(param);
	
	while ((strcmp(param, "Фамилия") != 0) && (strcmp(param, "Имя") != 0) && (strcmp(param, "Факультет") != 0) && (strcmp(param, "Номер зачетной книжки") != 0))
	{
		printf("\nТакого параметра не существует!\nДоступные параметры: Фамилия, Имя, Факультет, Номер зачетной книжки\n(Вводить с большой буквы без пробела в конце)\n");
		printf("\nВведите параметр, по которому следует выполнить поиск: ");
		gets_s(param);
	}*/

	/*printf("%s студента: ", param);
	if (strcmp(param, "Номер зачетной книжки")==0)
		scanf_s("%d", &searchzach);
	else
		gets_s(search);*/

	printf("Данные студента: ");
	gets_s(search);

	printf("\n\nРезультаты:\n");
	printf("    Фамилия\t\tИмя\tФакультет\tНомер зачетной книжки\n");
	printf("   __________________________________________________________________\n");

	for (int i = 0; i < 10; i++)
			if ((strcmp(search, stud[i].famil) == 0)||(strcmp(search, stud[i].name) == 0)||(strcmp(search, stud[i].facult) == 0)||(strcmp(search, stud[i].Nomzach) == 0))
			{
				somebody = 1;
				printf("%12s\t%12s\t%4s\t\t%s\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			}

	/*if (searchzach != 0)
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
	}*/

	if (somebody == 0)
		printf("\n\t\tСтудента с такими данными не нашлось!\n\n\n");
	Sleep(1000000);
}