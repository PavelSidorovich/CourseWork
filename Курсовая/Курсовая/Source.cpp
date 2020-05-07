#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>

#define ENG 26
#define RUS 32
int num_users;
int num_suppliers;
int num_goods;

struct USER
{
	char name[20];			// Имя пользователя
	char password[20];		// Пароль пользователя
} users[100];

struct locations
{
	char town[20];		// Город
	char street[20];	// Улица
	char number[20];	// Номер здания
};

struct goods
{
	char name[20];		// Название продукта
	char type[20];		// Тип продукта
	char model[20];		// Модель продукта
	char id[10];		// Уникальный номер продукта
	char price[10];		// Цена продукта
	char day[3];		// День
	char month[3];		// Месяц
	char year[5];		// Год
};

struct SUPPLIER
{
	char name[20];				// Название компании
	struct locations location;	// Информация о местоположении
	struct goods good[10];		// Товары компании
	char first_name[20];		// Имя представителя компании
	char second_name[20];		// Фамилия представителя компании
	char last_name[20];			// Отчество представителя компании
	char phone[20];				// Телефон
	char day[3];				// День
	char month[3];				// Месяц
	char year[5];				// Год
} suppliers[100];

void menu();				// Меню входа
void admin();				// Авторизация для администратора
void user();				// Авторизация для пользователя
void user_menu();			// Меню для пользователя
void admin_menu();			// Меню для администратора
void actions_with_users();	// Меню управления пользователями
void delete_user();			// Функция удаления пользователя
void create_user();			// Функция добавления пользователя
void show_users();			// Функция отображения данных пользователей в табличной форме
void count_users();			// Функция подсчёта количества пользователей
void fill_companies();		// Функция заполнения полей структуры, хранящей данные о поставщике
void count_companies();		// Функция подсчёта количества компаний
void edit_supplier();		// Функция редактирования данных поставщика
void show_suppliers();		// Функция отображения данных поставщиков в табличной форме
void show_goods();			// Функция отображения информации о товарах в табличной форме
void add_goods();			// Функция добавления товара для поставщика
void delete_goods();		// Функция удаления товара поставщика
void delete_supplier();		// Функция удаления поставщика
void fill_goods();			// Функция заполнения полей структуры, содержащей информацию о товарах поставщиков
void encrypt(char user_buf_name[20], char user_buf_password[20]); // Функция шифрования логина и пароля пользователя
void decipher();			// Функция дешифрования логинов и паролей
void add_supplier();		// Функция добавления поставщика 
void task();				// Функция выполнения задачи
void find_name();			// Функция поиска товара по имени
void find_id();				// Функция поиска товара по уникальному номеру
void find_type();			// Функция поиска товара по типу
void filter_vozr(int num_goods);	// Фильтрация товара по цене (возрастание)
void filter_ubuv(int num_goods);	// Фильтрация товара по цене (убывание)
void clear_users();			// Функция очистки файла с пользователями
void clear_companies();		// Функция очистки файла с компаниями

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE *users, *company;
	fopen_s(&users, "users.txt", "a");
	fopen_s(&company, "companies.txt", "a");
	fclose(users);
	fclose(company);
	count_companies();
	fill_companies();
	count_users();
	decipher();
	fill_goods();
	menu();
	return 0;
}

void menu()
{
	char choice;
	printf("1 - Вход как администратор\n2 - Вход как пользователь\n3 - Выход\n");
	while (1)
	{
		choice = _getch();
		if (choice == '1')
		{
			system("cls");
			admin();
		}
		else if (choice == '2')
		{
			system("cls");
			user();
		}
		else if (choice == '3')
			exit(1);
		else
		{
			system("cls");
			printf("1 - Войти как администратор\n2 - Войти как пользователь\n3 - Выход\n");
			printf("Введите корректные данные (Вы ввели: %c)\n", choice);
		}
	}
}

void admin()
{
	char login[100], password[100], esc;

	while (1)
	{
		printf("Введите логин: ");
		gets(login);
		if (strlen(login) >= 20)
		{
			system("cls");
			printf("Логин содержит более 20 символов. Нажмите ESC для выхода или любую клавишу для повторного ввода логина: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
			continue;
		}
		if (strcmp(login, "Admin") == 0)
		{
			break;
		}
		else
		{
			system("cls");
			printf("Неверный логин. Нажмите ESC для выхода или любую клавишу для повторного ввода логина: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
		}
	}
	while (1)
	{
		printf("Введите пароль: ");
		gets(password);
		if (strlen(password) >= 20)
		{
			system("cls");
			printf("Пароль содержит более 20 символов. Нажмите ESC для выхода или любую клавишу для повторного ввода пароля: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
			continue;
		}
		if (strcmp(password, "Admin") == 0)
			admin_menu();
		else
		{
			printf("Неверный пароль. Нажмите ESC для выхода или любую клавишу для повторного ввода пароля: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
		}
	}
}

void user_menu()
{
	char choice;
	system("cls");
	while (1)
	{
		printf("[МЕНЮ ПОЛЬЗОВАТЕЛЯ]\n");
		printf("1 - Просмотр всех данных в табличной форме\n2 - Выполнение задачи\n3 - Различные процедуры поиска и фильтрации данных\n4 - Назад\n");
		choice = _getch();
		if (choice == '1')
		{
			system("cls");
			while (1)
			{
				printf("[ПРОСМОТР ВСЕХ ДАННЫХ В ТАБЛИЧНОЙ ФОРМЕ]\n");
				printf("1 - Список поставщиков с информацией\n2 - Список товара\n3 - Назад");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					show_suppliers();
				}
				else if (choice == '2')
				{
					system("cls");
					show_goods();
				}
				else if (choice == '3')
				{
					system("cls");
					user_menu();
				}
				else
				{
					system("cls");
					printf("Введите корректные данные (Вы ввели: %c)\n", choice);
				}
			}
		}
		else if (choice == '2')
		{
			system("cls");
			task();
		}
		else if (choice == '3')
		{
			system("cls");
			while (1)
			{
				printf("[РАЗЛИЧНЫЕ ПРОЦЕДУРЫ ПОИСКА И ФИЛЬТРАЦИИ ДАННЫХ]\n");
				printf("1 - Найти запись по имени\n2 - Найти запись по типу\n3 - Найти запись по ID\n4 - Фильтрация по возрастанию\n5 - Фильтрация по убыванию\n6 - Назад");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					find_name();
				}
				else if (choice == '2')
				{
					system("cls");
					find_type();
				}
				else if (choice == '3')
				{
					system("cls");
					find_id();
				}
				else if (choice == '4')
				{
					system("cls");
					filter_vozr(num_goods);
				}
				else if (choice == '5')
				{
					system("cls");
					filter_ubuv(num_goods);
				}
				else if (choice == '6')
				{
					system("cls");
					user_menu();
				}
				else
				{
					system("cls");
					printf("Введите корректные данные (Вы ввели: %c)\n", choice);
				}
			}
		}
		else if (choice == '4')
		{
			system("cls");
			menu();
		}
		else
		{
			system("cls");
		}
	}
}

void admin_menu()
{
	char choice;
	system("cls");
	while (1)
	{
		printf("[МЕНЮ АДМИНИСТРАТОРА]\n");
		printf("1 - Добавление записи\n2 - Операции с данными поставщика и товарами\n3 - Просмотр всех данных в табличной форме\n4 - Различные процедуры поиска и фильтрации данных\n5 - Управление пользователями\n6 - Работа с файлами\n7 - Назад\n");
		choice = _getch();
		if (choice == '1')
		{
			system("cls");
			while (1)
			{
				printf("[ДОБАВЛЕНИЕ ЗАПИСИ]\n");
				printf("1 - Добавление нового поставщика\n2 - Добавление товара для поставщика\n3 - Назад");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					add_supplier();
				}
				else if (choice == '2')
				{
					system("cls");
					add_goods();
				}
				else if (choice == '3')
				{
					system("cls");
					admin_menu();
				}
				else
				{
					system("cls");
				}
			}
		}
		else if (choice == '2')
		{
			system("cls");
			while (1)
			{
				printf("[ОПЕРАЦИИ С ДАННЫМИ ПОСТАВЩИКА И ТОВАРАМИ]\n");
				printf("1 - Редактирование данных поставщика\n2 - Удаление поставщика\n3 - Удаление товара\n4 - Назад");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					edit_supplier();
				}
				else if (choice == '2')
				{
					system("cls");
					delete_supplier();
				}
				else if (choice == '3')
				{
					system("cls");
					delete_goods();
				}
				else if (choice == '4')
				{
					system("cls");
					admin_menu();
				}
				else
				{
					system("cls");
				}
			}
		}
		else if (choice == '3')
		{
			system("cls");
			while (1)
			{
				printf("[ПРОСМОТР ВСЕХ ДАННЫХ В ТАБЛИЧНОЙ ФОРМЕ]\n");
				printf("1 - Список поставщиков с информацией\n2 - Список товара\n3 - Назад");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					show_suppliers();
				}
				else if (choice == '2')
				{
					system("cls");
					show_goods();
				}
				else if (choice == '3')
				{
					system("cls");
					admin_menu();
				}
				else
				{
					system("cls");
				}
			}
		}
		else if (choice == '4')
		{
			system("cls");
			while (1)
			{
				printf("[РАЗЛИЧНЫЕ ПРОЦЕДУРЫ ПОИСКА И ФИЛЬТРАЦИИ ДАННЫХ]\n");
				printf("1 - Найти запись по имени\n2 - Найти запись по типу\n3 - Найти запись по ID\n4 - Фильтрация по возрастанию\n5 - Фильтрация по убыванию\n6 - Назад");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					find_name();
				}
				else if (choice == '2')
				{
					system("cls");
					find_type();
				}
				else if (choice == '3')
				{
					system("cls");
					find_id();
				}
				else if (choice == '4')
				{
					system("cls");
					filter_vozr(num_goods);
				}
				else if (choice == '5')
				{
					system("cls");
					filter_ubuv(num_goods);
				}
				else if (choice == '6')
				{
					system("cls");
					admin_menu();
				}
				else
				{
					system("cls");
				}
			}
		}
		else if (choice == '5')
		{
			system("cls");
			actions_with_users();
		}
		else if (choice == '6')
		{
			system("cls");
			while (1)
			{
				printf("[РАБОТА С ФАЙЛАМИ]\n");
				printf("1 - Очистка файла с пользователями\n2 - Очистка файла с компаниями\n3 - Назад\n");
				choice = _getch();
				if (choice == '1')
				{
					system("cls");
					clear_users();
				}
				else if (choice == '2')
				{
					system("cls");
					clear_companies();
				}
				else if (choice == '3')
				{
					system("cls");
					admin_menu();
				}
			}
		}
		else if (choice == '7')
		{
			system("cls");
			menu();
		}
		else
		{
			system("cls");
		}
	}
}

void user()
{
	char login[20], password[20], esc;
	int i, was = 0;
	while (1)
	{
		printf("Введите логин: ");
		gets(login);
		if (strlen(login) >= 20)
		{
			system("cls");
			printf("Логин содержит более 20 символов. Нажмите ESC для выхода или любую клавишу для повторного ввода логина: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
			continue;
		}
		for (i = 0; i < num_users; i++)
		{
			if (strcmp(login, users[i].name) == 0)
			{
				was = 1;
				break;
			}
		}
		if (was == 1)
		{
			was = 0;
			break;
		}
		else
		{
			system("cls");
			printf("Неверный логин. Нажмите ESC для выхода или любую клавишу для повторного ввода логина: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
		}
	}
	while (1)
	{
		printf("Введите пароль: ");
		gets(password);
		if (strlen(password) > 20 || strlen(password) < 8)
		{
			system("cls");
			printf("Пароль должен содержать не более 20 и не меньше 8 символов. Нажмите ESC для выхода или любую клавишу для повторного ввода пароля: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
			continue;
		}
		if (strcmp(password, users[i].password) == 0)
			user_menu();
		else
		{
			printf("Неверный пароль. Нажмите ESC для выхода или любую клавишу для повторного ввода пароля: ");
			esc = _getch();
			if (esc == 27)
			{
				system("cls");
				menu();
			}
			system("cls");
		}
	}
}

void actions_with_users()
{
	char choice;
	system("cls");
	while (1)
	{
		printf("[УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ]\n");
		printf("1 - Добавление пользователя\n2 - Удаление пользователя\n3 - Просмотр списка пользователей\n4 - Назад\n");
		choice = _getch();
		if (choice == '1')
		{
			system("cls");
			create_user();
		}
		else if (choice == '2')
		{
			system("cls");
			delete_user();
		}
		else if (choice == '3')
		{
			system("cls");
			count_users();
			decipher();
			show_users();
		}
		else if (choice == '4')
		{
			system("cls");
			admin_menu();
		}
		else
		{
			system("cls");
		}
	}
}

void delete_user()
{
	FILE *file;
	int i, probel = 0, was = 0;
	char name[20];
	fopen_s(&file, "users.txt", "r");
	printf("[УДАЛЕНИЕ ПОЛЬЗОВАТЕЛЯ]");
	printf("\n");
	printf("---------------------------------------------\n");
	printf("|        Логин        |       Пароль        |\n");
	printf("---------------------------------------------\n");
	for (i = 0; i < num_users; i++)
	{
		printf("| %-20s| %-20s|\n", users[i].name, users[i].password);		//вывод логина и пароля пользователя на экран
		printf("---------------------------------------------\n");
	}
	printf("Кол-во пользователей: %d\n", num_users);
	printf("Введите имя пользователя, которого хотите удалить: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 4)
		{
			printf("Имя пользователя должно быть меньше 20, но больше 4 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ')
			{
				probel = 1;
				printf("Имя пользователя не должно содержать пробелов. Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i < num_users; i++)
		{
			if (strcmp(name, users[i].name) == 0)		//сравнение введённого имени с именами в базе данных для удаления конкретного пользователя
			{
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				was = 1;
				printf("Пользователь с именем [%s] удалён. Нажмите любую клавишу для продолжения...", users[i].name);	//вывод имени удалённого пользователя на экран
				fscanf_s(file, "%s", users[i].name, _countof(users[i].name));		//считывание имени следующего пользователя из файла вместо удалённого
				fscanf_s(file, "%s", users[i].password, _countof(users[i].password));		//считывание пароля следующего пользователя из файла вместо удалённого
			}
			else
			{
				fscanf_s(file, "%s", users[i].name, _countof(users[i].name));		//считывание имени пользователя из файла
				fscanf_s(file, "%s", users[i].password, _countof(users[i].password));		//считывание пароля пользователя из файла
			}
		}
		if (was == 0)
		{
			printf("Нет пользователя с таким именем. Нажмите любую клавишу для продолжения...");
			fclose(file);
			count_users();
			decipher();
			break;
		}
		fclose(file);
		fopen_s(&file, "users.txt", "w");
		for (i = 0; i < num_users - 1; i++)
		{
			fprintf(file, "%s ", users[i].name);		//запись имени пользователя в файл
			fprintf(file, "%s\n", users[i].password);		////запись пароля пользователя в файл
		}
		fclose(file);
		count_users();
		decipher();
		break;
	}
	_getch();
	system("cls");
}

void create_user()
{
	FILE *file;
	printf("[ДОБАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯ]\n");
	int i, was = 0, probel = 0;
	char user_buf_name[21];
	char user_buf_password[21];
	fopen_s(&file, "users.txt", "a");
	printf("Введите имя пользователя, которого хотите добавить: ");
	while (1)
	{
		gets(user_buf_name);
		if (strlen(user_buf_name) > 20 || strlen(user_buf_name) < 4)
		{
			printf("Имя пользователя должно быть меньше 20, но больше 4 символов. Повторите попытку: ");
			*user_buf_name = 0;
			continue;
		}
		for (i = 0; i < strlen(user_buf_name); i++)
		{
			if (user_buf_name[i] == ' ')
			{
				probel = 1;
				printf("Имя пользователя не должно содержать пробелов. Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i < num_users; i++)
		{
			if (strcmp(user_buf_name, users[i].name) == 0)		//сравнение имени нового пользователя с существующими в базе данных для исключения повторения логина
			{
				printf("Пользователь с таким именем уже существует, повторите попытку: ");
				was = 1;
				break;
			}
			else was = 0;
		}
		if (was == 1)
			continue;
		break;
	}
	printf("Введите пароль пользователя: ");
	while (1)
	{
		gets(user_buf_password);
		for (i = 0; i < strlen(user_buf_password); i++)
		{
			if (user_buf_password[i] == ' ')
			{
				probel = 1;
				printf("Пароль пользователя не должен содержать пробелов. Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		if (strlen(user_buf_password) > 20 || strlen(user_buf_password) < 8)
		{
			printf("Пароль пользователя должен больше 8, но меньше 20 символов. Повторите попытку: ");
			continue;
		}
		break;
	}
	printf("Пользователь [%s], с паролем [%s] успешно создан!", user_buf_name, user_buf_password);
	fclose(file);
	encrypt(user_buf_name, user_buf_password);
	printf("\nНажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void show_users()
{
	int i;
	printf("\n");
	printf("---------------------------------------------\n");
	printf("|        Логин        |       Пароль        |\n");
	printf("---------------------------------------------\n");
	for (i = 0; i < num_users; i++)
	{
		printf("| %-20s| %-20s|\n", users[i].name, users[i].password);		//вывод логина и пароля пользователя на экран
		printf("---------------------------------------------\n");
	}
	printf("Кол-во пользователей: %d\n", num_users);
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void count_users()
{
	int i = 0;
	FILE *file;
	fopen_s(&file, "users.txt", "r");
	do {
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		i++;
	} while (!feof(file));
	extern int num_users;
	num_users = i - 1;
	fclose(file);
}

// Шифрование
void encrypt(char user_buf_name[20], char user_buf_password[20])
{
	FILE *file;
	fopen_s(&file, "users.txt", "a");
	int flag, j = 0, n = 5;
	char c;
	c = user_buf_name[j];
	while (j != strlen(user_buf_name))
	{
		flag = 0;
		if (c >= 'A' && c <= 'Z')
		{
			c = c + (n % ENG);
			if (c > 'Z') c = 'A' + (c - 'Z') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= 'a' && c <= 'z')
		{
			c = c + (n % ENG);
			if (c > 'z') c = 'a' + (c - 'z') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= 'А' && c <= 'Я')
		{
			c = c + (n % RUS);
			if (c > 'Я') c = 'А' + (c - 'Я') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= 'а' && c <= 'я')
		{
			c = c + (n % RUS);
			if (c > 'я') c = 'а' + (c - 'я') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= '0' && c <= '9')
		{
			c = c + (n % ENG);
			if (c > '9') c = '0' + (c - '9') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (!flag) fprintf(file, "%c", c);
		j++;
		c = user_buf_name[j];
	}
	fprintf(file, " ");
	j = 0;
	c = user_buf_password[j];
	while (j != strlen(user_buf_password))
	{
		flag = 0;
		if (c >= 'A' && c <= 'Z')
		{
			c = c + (n % ENG);
			if (c > 'Z') c = 'A' + (c - 'Z') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= 'a' && c <= 'z')
		{
			c = c + (n % ENG);
			if (c > 'z') c = 'a' + (c - 'z') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= 'А' && c <= 'Я')
		{
			c = c + (n % RUS);
			if (c > 'Я') c = 'А' + (c - 'Я') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= 'а' && c <= 'я')
		{
			c = c + (n % RUS);
			if (c > 'я') c = 'а' + (c - 'я') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= '0' && c <= '9')
		{
			c = c + (n % ENG);
			if (c > '9') c = '0' + (c - '9') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (!flag) fprintf(file, "%c", c);
		j++;
		c = user_buf_password[j];
	}
	fprintf(file, "\r\n");
	fclose(file);
}

// Дешифрование
void decipher()
{
	FILE *file;
	fopen_s(&file, "users.txt", "r");
	int flag, i, n = 5, j;
	char c, user_buf_name[20], user_buf_password[20];
	for (i = 0; i < num_users; i++)
	{
		j = 0;
		fscanf_s(file, "%s", user_buf_name, _countof(user_buf_name));
		c = user_buf_name[j];
		while (j < strlen(user_buf_name))
		{
			flag = 0;
			if (c >= 'A' && c <= 'Z')
			{
				c = c - (n % ENG);
				if (c < 'A') c = 'Z' - ('A' - c) + 1;
				users[i].name[j] = c;
				flag = 1;
			}
			if (c >= 'a' && c <= 'z')
			{
				c = c - (n % ENG);
				if (c < 'a') c = 'z' - ('a' - c) + 1;
				users[i].name[j] = c;
				flag = 1;
			}
			if (c >= 'А' && c <= 'Я')
			{
				c = c - (n % RUS);
				if (c < 'А') c = 'Я' - ('А' - c) + 1;
				users[i].name[j] = c;
				flag = 1;
			}
			if (c >= 'а' && c <= 'я')
			{
				c = c - (n % RUS);
				if (c < 'а') c = 'я' - ('а' - c) + 1;
				users[i].name[j] = c;
				flag = 1;
			}
			if (c >= '0' && c <= '9')
			{
				c = c - (n % ENG);
				if (c < '0') c = '9' - ('0' - c) + 1;
				users[i].name[j] = c;
				flag = 1;
			}
			if (!flag)
				users[i].name[j] = c;
			j++;
			c = user_buf_name[j];
		}
		j = 0;
		fscanf_s(file, "%s", user_buf_password, _countof(user_buf_password));
		while (j < strlen(user_buf_password))
		{
			c = user_buf_password[j];
			flag = 0;
			if (c >= 'A' && c <= 'Z')
			{
				c = c - (n % ENG);
				if (c < 'A') c = 'Z' - ('A' - c) + 1;
				users[i].password[j] = c;
				flag = 1;
			}
			if (c >= 'a' && c <= 'z')
			{
				c = c - (n % ENG);
				if (c < 'a') c = 'z' - ('a' - c) + 1;
				users[i].password[j] = c;
				flag = 1;
			}
			if (c >= 'А' && c <= 'Я')
			{
				c = c - (n % RUS);
				if (c < 'А') c = 'Я' - ('А' - c) + 1;
				users[i].password[j] = c;
				flag = 1;
			}
			if (c >= 'а' && c <= 'я')
			{
				c = c - (n % RUS);
				if (c < 'а') c = 'я' - ('а' - c) + 1;
				users[i].password[j] = c;
				flag = 1;
			}
			if (c >= '0' && c <= '9')
			{
				c = c - (n % ENG);
				if (c < '0') c = '9' - ('0' - c) + 1;
				users[i].password[j] = c;
				flag = 1;
			}
			if (!flag)
				users[i].password[j] = c;
			j++;
		}
	}
	fclose(file);
}

void add_supplier()
{
	FILE *company;
	fopen_s(&company, "companies.txt", "a");
	char buf[200];
	int i, probel = 0, was = 0, norm = 0;
	printf("[ДОБАВЛЕНИЕ ПОСТАВЩИКА]\n");
	printf("Введите название компании: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("Название компании должно быть меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("Название компании не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i < num_suppliers; i++)
		{
			if (strcmp(buf, suppliers[i].name) == 0)	//сравнение нового названия компании с существующими в базе данных
			{
				printf("Компания с таким названием уже существует, повторите попытку: ");
				was = 1;
				break;
			}
			else was = 0;
		}
		if (was == 1)
			continue;
		fprintf(company, "%s ", buf);
		break;
	}
	printf("Введите местонахождение компании (офиса)\n");
	printf("Введите город: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("Название города должно быть меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("Название города не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		fprintf(company, "%s ", buf);
		break;
	}
	printf("Введите улицу: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("Название улицы должно быть меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("Название улицы не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		fprintf(company, "%s ", buf);
		break;
	}
	printf("Введите номер здания: ");
	while (norm == 0)
	{
		gets(buf);
		for (i = 0; i < strlen(buf); i++)
		{
			if ((buf[i]) >= '0' && (buf[i]) <= '9')
			{
				norm = 1;
			}
			else
			{
				printf("Номер здания должен состоять из цифр. Повторите попытку: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("Введите представителя компании\n");
	printf("Введите имя: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("Имя должно быть меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("Имя не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		fprintf(company, "%s ", buf);
		break;
	}
	printf("Введите фамилию: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("Фамилия должна быть меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("Фамилия не должна содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		fprintf(company, "%s ", buf);
		break;
	}
	printf("Введите отчество: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("Отчество должно быть меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("Отчество не должно содержать пробелов. Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		fprintf(company, "%s ", buf);
		break;
	}
	printf("Введите номер для связи: +");
	norm = 0;
	while (norm == 0)
	{
		gets(buf);
		for (i = 0; i < strlen(buf); i++)
		{
			if ((buf[i]) >= '0' && (buf[i]) <= '9')
			{
				norm = 1;
			}
			else
			{
				printf("Номер должен состоять из цифр. Повторите попытку: +");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("Введите день регистрации (к примеру, 06): ");
	norm = 0;
	while (norm == 0)
	{
		gets(buf);
		for (i = 0; i < strlen(buf); i++)
		{
			if ((buf[i]) >= '0' && (buf[i]) <= '9' && strlen(buf) == 2 && atoi(buf) >= 0 && atoi(buf) <= 31)
			{
				norm = 1;
			}
			else
			{
				printf("День должен состоять из цифр (2). Повторите попытку: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("Введите месяц регистрации (к примеру, 06): ");
	norm = 0;
	while (norm == 0)
	{
		gets(buf);
		for (i = 0; i < strlen(buf); i++)
		{
			if ((buf[i]) >= '0' && (buf[i]) <= '9' && strlen(buf) == 2 && atoi(buf) >= 0 && atoi(buf) <= 12)
			{
				norm = 1;
			}
			else
			{
				printf("Месяц должен состоять из цифр (2). Повторите попытку: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("Введите год регистрации: ");
	norm = 0;
	while (norm == 0)
	{
		gets(buf);
		for (i = 0; i < strlen(buf); i++)
		{
			if ((buf[i]) >= '0' && (buf[i]) <= '9' && strlen(buf) == 4)
			{
				norm = 1;
			}
			else
			{
				printf("Год должен состоять из цифр (4). Повторите попытку: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s\n", buf);
	printf("Новый поставщик успешно добавлен!\nНажмите любую клавишу для продолжения...");
	fclose(company);
	_getch();
	count_companies();
	system("cls");
	fill_companies();
}

void fill_companies()
{
	FILE *file;
	int i;
	fopen_s(&file, "companies.txt", "r");
	for (i = 0; i < num_suppliers; i++)
	{
		fscanf_s(file, "%s", suppliers[i].name, _countof(suppliers[i].name));	//считывание имени компании из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].location.town, _countof(suppliers[i].location.town));		//считывание города из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].location.street, _countof(suppliers[i].location.street));		//считывание улицы из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].location.number, _countof(suppliers[i].location.number));		//считывание номер здания из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].first_name, _countof(suppliers[i].first_name));		//считывание имени представителя компании из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].second_name, _countof(suppliers[i].second_name));		//считывание фамилии представителя компании из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].last_name, _countof(suppliers[i].last_name));			//считывание отчества представителя компании из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].phone, _countof(suppliers[i].phone));			//считывание номера компании из файла в базу данных (структуру)
		fscanf_s(file, "%s", suppliers[i].day, _countof(suppliers[i].day));
		fscanf_s(file, "%s", suppliers[i].month, _countof(suppliers[i].month));
		fscanf_s(file, "%s", suppliers[i].year, _countof(suppliers[i].year));
	}
	fclose(file);
}

void count_companies()
{
	int i = 0;
	FILE *file;
	fopen_s(&file, "companies.txt", "r");
	do {
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		fscanf_s(file, "%*s");
		i++;
	} while (!feof(file));
	extern int num_suppliers;
	num_suppliers = i - 1;
	fclose(file);
}

void delete_supplier()
{
	FILE *file;
	int i, probel = 0, was = 0;
	char name[20];
	fopen_s(&file, "companies.txt", "r");
	printf("[УДАЛЕНИЕ ПОСТАВЩИКА]");
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название компании   |                      Местонахождение                       |                      Представитель (менеджер)                 |       Телефон       | Дата регистрации |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s| г.%-20s ул.%-20s д.%-10s| %-20s %-20s %-20s| +%-19s| \t%s.%s.%s   |\n", suppliers[i].name, suppliers[i].location.town, suppliers[i].location.street, suppliers[i].location.number, suppliers[i].second_name, suppliers[i].first_name, suppliers[i].last_name, suppliers[i].phone, suppliers[i].day, suppliers[i].month, suppliers[i].year);	//вывод информации о поставщике на экран
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("Кол-во поставщиков: %d\n", num_suppliers);
	printf("Введите название компании, которую хотите удалить: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 2)
		{
			printf("Название компании должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ' || (name[i] >= '0' && name[i] <= '9'))
			{
				probel = 1;
				printf("Название компании не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i <= num_suppliers; i++)
		{
			if (strcmp(name, suppliers[i].name) == 0)	//сравнение имени удаляемой компании с именами компаний в базе данных
			{
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				was = 1;
				printf("Компания [%s] удалёна. Нажмите любую клавишу для продолжения...", suppliers[i].name);	//вывод имени удалённой компании
				fscanf_s(file, "%s", suppliers[i].name, _countof(suppliers[i].name));	//считывание имени компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].location.town, _countof(suppliers[i].location.town));	//считывание города из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].location.street, _countof(suppliers[i].location.street));	//считывание улицы из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].location.number, _countof(suppliers[i].location.number));	//считывание номер здания из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].first_name, _countof(suppliers[i].first_name));	//считывание имени представителя компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].second_name, _countof(suppliers[i].second_name));	//считывание фамилии представителя компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].last_name, _countof(suppliers[i].last_name));	//считывание отчества представителя компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].phone, _countof(suppliers[i].phone));	//считывание номера компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].day, _countof(suppliers[i].day));
				fscanf_s(file, "%s", suppliers[i].month, _countof(suppliers[i].month));
				fscanf_s(file, "%s", suppliers[i].year, _countof(suppliers[i].year));
			}
			else
			{
				fscanf_s(file, "%s", suppliers[i].name, _countof(suppliers[i].name));	//считывание имени компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].location.town, _countof(suppliers[i].location.town));	//считывание города из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].location.street, _countof(suppliers[i].location.street));	//считывание улицы из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].location.number, _countof(suppliers[i].location.number));	//считывание номер здания из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].first_name, _countof(suppliers[i].first_name));	//считывание имени представителя компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].second_name, _countof(suppliers[i].second_name));	//считывание фамилии представителя компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].last_name, _countof(suppliers[i].last_name));	//считывание отчества представителя компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].phone, _countof(suppliers[i].phone));	//считывание номера компании из файла в базу данных (структуру)
				fscanf_s(file, "%s", suppliers[i].day, _countof(suppliers[i].day));
				fscanf_s(file, "%s", suppliers[i].month, _countof(suppliers[i].month));
				fscanf_s(file, "%s", suppliers[i].year, _countof(suppliers[i].year));
			}
		}
		if (was == 0)
		{
			printf("Нет компании с таким названием. Нажмите любую клавишу для продолжения...");
			fclose(file);
			_getch();
			system("cls");
			break;
		}
		_getch();
		fclose(file);
		fopen_s(&file, "companies.txt", "w");
		for (i = 0; i < num_suppliers - 1; i++)
		{
			fprintf(file, "%s ", suppliers[i].name);	//запись названия компании в файл
			fprintf(file, "%s ", suppliers[i].location.town);	//запись города в файл
			fprintf(file, "%s ", suppliers[i].location.street);	//запись улицы в файл
			fprintf(file, "%s ", suppliers[i].location.number);	//запись номера здания в файл
			fprintf(file, "%s ", suppliers[i].first_name);	//запись имени представителя компании в файл
			fprintf(file, "%s ", suppliers[i].second_name);	//запись фамилии представителя компании в файл
			fprintf(file, "%s ", suppliers[i].last_name);	//запись отчества представителя компании в файл
			fprintf(file, "%s ", suppliers[i].phone);	//запись номера компании в файл
			fprintf(file, "%s ", suppliers[i].day);
			fprintf(file, "%s ", suppliers[i].month);
			fprintf(file, "%s\r\n", suppliers[i].year);
		}
		fclose(file);
		count_companies();
		fill_companies();
		system("cls");
		break;
	}
}

void show_suppliers()
{
	int i;
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название компании   |                      Местонахождение                       |                      Представитель (менеджер)                 |       Телефон       | Дата регистрации |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s| г.%-20s ул.%-20s д.%-10s| %-20s %-20s %-20s| +%-19s| \t%s.%s.%s   |\n", suppliers[i].name, suppliers[i].location.town, suppliers[i].location.street, suppliers[i].location.number, suppliers[i].second_name, suppliers[i].first_name, suppliers[i].last_name, suppliers[i].phone, suppliers[i].day, suppliers[i].month, suppliers[i].year);	//вывод информации о поставщике на экран
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("Кол-во поставщиков: %d\n", num_suppliers);
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void show_goods()
{
	FILE *file;
	char name[30];
	int j;
	for (int i = 0; i < num_suppliers; i++)
	{
		strcpy(name, suppliers[i].name);
		strcat(name, ".txt");
		fopen_s(&file, name, "r");
		if (file == NULL)
		{
			continue;
		}
		printf("\nТОВАРЫ КОМПАНИИ \"%s\"", suppliers[i].name);
		printf("\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		int j = 0;
		while (strlen(suppliers[i].good[j].name) != 0)
		{
			printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year);
			printf("---------------------------------------------------------------------------------------------------------------\n");
			j++;
		}
		fclose(file);
	}
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void edit_supplier()
{
	FILE *file;
	int i, probel = 0, was = 0, norm = 0, j;
	char name[200], buf[200];
	fopen_s(&file, "companies.txt", "r");
	printf("[ИЗМЕНЕНИЕ ДАННЫХ ПОСТАВЩИКА]");
	printf("\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название компании   |                      Местонахождение                       |                      Представитель (менеджер)                 |       Телефон       |\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s| г.%-20s ул.%-20s д.%-10s| %-20s %-20s %-20s| +%-19s|\n", suppliers[i].name, suppliers[i].location.town, suppliers[i].location.street, suppliers[i].location.number, suppliers[i].second_name, suppliers[i].first_name, suppliers[i].last_name, suppliers[i].phone);	//вывод информации о поставщике на экран
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("Кол-во поставщиков: %d\n", num_suppliers);
	printf("Введите название компании, в которой хотите провести изменения: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 2)
		{
			printf("Название компании должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ' || (name[i] >= '0' && name[i] <= '9'))
			{
				probel = 1;
				printf("Название компании не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		char choice;
		for (i = 0; i <= num_suppliers; i++)
		{
			if (strcmp(name, suppliers[i].name) == 0)	//сравнение имени удаляемой компании с именами компаний в базе данных
			{
				while (1)
				{
					printf("1 - Редактирование города\n2 - Редактирование улицы\n3 - Редактирование дома\n4 - Редактирование имени представителя\n5 - Редактирование фамилии представителя\n6 - Редактирование отчества представителя\n7 - Редактирование номера\n8 - Назад\n");
					choice = _getch();
					if (choice == '1')
					{
						printf("Введите город: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("Название города должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("Название города не должно содержать пробелов (цифр). Повторите попытку: ");
									break;
								}
								else
									probel = 0;
							}
							if (probel == 1)
								continue;
							strcpy(suppliers[i].location.town, buf);
							break;
						}
						break;
					}
					else if (choice == '2')
					{
						printf("Введите улицу: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("Название улицы должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("Название улицы не должно содержать пробелов (цифр). Повторите попытку: ");
									break;
								}
								else
									probel = 0;
							}
							if (probel == 1)
								continue;
							strcpy(suppliers[i].location.street, buf);
							break;
						}
						break;
					}
					else if (choice == '3')
					{
						printf("Введите номер здания: ");
						while (norm == 0)
						{
							gets(buf);
							for (j = 0; j < strlen(buf); j++)
							{
								if ((buf[j]) >= '0' && (buf[j]) <= '9')
								{
									norm = 1;
								}
								else
								{
									printf("Номер здания должен состоять из цифр. Повторите попытку: ");
									norm = 0;
									break;
								}
							}
						}
						strcpy(suppliers[i].location.number, buf);
						break;
					}
					else if (choice == '4')
					{
						printf("Введите имя: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("Имя должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("Имя не должно содержать пробелов (цифр). Повторите попытку: ");
									break;
								}
								else
									probel = 0;
							}
							if (probel == 1)
								continue;
							strcpy(suppliers[i].first_name, buf);
							break;
						}
						break;
					}
					else if (choice == '5')
					{
						printf("Введите фамилию: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("Фамилия должна содержать меньше 20, но больше 2 символов. Повторите попытку: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("Фамилия не должна содержать пробелов (цифр). Повторите попытку: ");
									break;
								}
								else
									probel = 0;
							}
							if (probel == 1)
								continue;
							strcpy(suppliers[i].second_name, buf);
							break;
						}
						break;
					}
					else if (choice == '6')
					{
						printf("Введите отчество: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("Отчество должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("Отчество не должно содержать пробелов (цифр). Повторите попытку: ");
									break;
								}
								else
									probel = 0;
							}
							if (probel == 1)
								continue;
							strcpy(suppliers[i].last_name, buf);
							break;
						}
						break;
					}
					else if (choice == '7')
					{
						printf("Введите номер для связи: +");
						norm = 0;
						while (norm == 0)
						{
							gets(buf);
							for (j = 0; j < strlen(buf); j++)
							{
								if ((buf[j]) >= '0' && (buf[j]) <= '9')
								{
									norm = 1;
								}
								else
								{
									printf("Номер должен состоять из цифр. Повторите попытку: +");
									norm = 0;
									break;
								}
							}
						}
						strcpy(suppliers[i].phone, buf);
						break;
					}
					else if (choice == '8')
					{
						system("cls");
						return;
					}
					else
					{
						printf("Нет такого пункта!\nНажмите любую клавишу для продолжения...");
						_getch();
						system("cls");
						return;
					}
				}
				printf("Данные поставщика успешно изменены!\nНажмите любую клавишу для продолжения...");
				_getch();
				system("cls");
				was = 1;
			}
		}
		if (was == 0)
		{
			printf("Нет компании с таким названием. Нажмите любую клавишу для продолжения...");
			fclose(file);
			_getch();
			system("cls");
			break;
		}
		fclose(file);
		fopen_s(&file, "companies.txt", "w");
		for (i = 0; i < num_suppliers; i++)
		{
			fprintf(file, "%s ", suppliers[i].name);	//запись названия компании в файл
			fprintf(file, "%s ", suppliers[i].location.town);	//запись города в файл
			fprintf(file, "%s ", suppliers[i].location.street);	//запись улицы в файл
			fprintf(file, "%s ", suppliers[i].location.number);	//запись номера здания в файл
			fprintf(file, "%s ", suppliers[i].first_name);	//запись имени представителя компании в файл
			fprintf(file, "%s ", suppliers[i].second_name);	//запись фамилии представителя компании в файл
			fprintf(file, "%s ", suppliers[i].last_name);	//запись отчества представителя компании в файл
			fprintf(file, "%s ", suppliers[i].phone);	//запись номера компании в файл
			fprintf(file, "%s ", suppliers[i].day);
			fprintf(file, "%s ", suppliers[i].month);
			fprintf(file, "%s\n", suppliers[i].year);
		}
		fclose(file);
		fill_companies();
		system("cls");
		break;
	}
}

void add_goods()
{
	FILE *file;
	int i, probel = 0, was = 0, norm = 0;;
	char name[200], buf[200];
	printf("[ДОБАВЛЕНИЕ ТОВАРА]");
	printf("\n");
	printf("------------------------\n");
	printf("|  Название компании   |\n");
	printf("------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s|\n", suppliers[i].name);	//вывод информации о поставщике на экран
		printf("------------------------\n");
	}
	printf("Кол-во поставщиков: %d\n", num_suppliers);
	printf("Введите название компании, которая будет поставлять продукт: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 2)
		{
			printf("Название компании должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ' || (name[i] >= '0' && name[i] <= '9'))
			{
				probel = 1;
				printf("Название компании не должно содержать пробелов (цифр). Повторите попытку: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i <= num_suppliers; i++)
		{
			if (strcmp(name, suppliers[i].name) == 0)
			{
				was = 1;
				break;
			}
		}
		break;
	}
	if (was == 0)
	{
		printf("Нет такой компании. Нажмите любую клавишу для продолжения...");
		_getch();
		system("cls");
		return;
	}
	else
	{
		int j;
		for (j = 0; j < strlen(suppliers[i].name); j++)
		{
			name[j] = suppliers[i].name[j];
		}
		strcat(name, ".txt");
		fopen_s(&file, name, "a");
		printf("Введите название продукта: ");
		while (1)
		{
			gets(buf);
			if (strlen(buf) > 20 || strlen(buf) < 2)
			{
				printf("Название продукта должно содержать меньше 20, но больше 2 символов. Повторите попытку: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
				{
					probel = 1;
					printf("Название продукта не должно содержать пробелов (цифр). Повторите попытку: ");
					break;
				}
				else
					probel = 0;
			}
			if (probel == 1)
				continue;
			fprintf(file, "%s ", buf);
			break;
		}
		printf("Введите модель продукта: ");
		while (1)
		{
			gets(buf);
			if (strlen(buf) > 7 || strlen(buf) < 1)
			{
				printf("Модель продукта должна содержать меньше 7, но больше 1 символов. Повторите попытку: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if (buf[i] == ' ')
				{
					probel = 1;
					printf("Тип не должен содержать пробелов. Повторите попытку: ");
					break;
				}
				else
					probel = 0;
			}
			if (probel == 1)
				continue;
			fprintf(file, "%s ", buf);
			break;
		}
		printf("Введите тип продукта: ");
		while (1)
		{
			gets(buf);
			if (strlen(buf) > 20 || strlen(buf) < 2)
			{
				printf("Тип должен содержать меньше 20, но больше 2 символов. Повторите попытку: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
				{
					probel = 1;
					printf("Тип не должен содержать пробелов или цифр. Повторите попытку: ");
					break;
				}
				else
					probel = 0;
			}
			if (probel == 1)
				continue;
			fprintf(file, "%s ", buf);
			break;
		}
		printf("Введите уникальный номер продукта: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			if (strlen(buf) > 10 || strlen(buf) == 0)
			{
				printf("Уникальный номер продукта должен содержать меньше 20, но больше 1 символов. Повторите попытку: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if ((buf[i]) >= '0' && (buf[i]) <= '9')
				{
					norm = 1;
				}
				else
				{
					printf("Уникальный номер продукта должен состоять из цифр. Повторите попытку: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("Введите цену продукта: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			if (strlen(buf) > 10 || strlen(buf) == 0)
			{
				printf("Цена продукта должна содержать меньше 20, но больше 1 символов. Повторите попытку: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if ((buf[i]) >= '0' && (buf[i]) <= '9')
				{
					norm = 1;
				}
				else
				{
					printf("Цена должна состоять из цифр. Повторите попытку: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("Введите день подачи: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			for (i = 0; i < strlen(buf); i++)
			{
				if ((buf[i]) >= '0' && (buf[i]) <= '9' && strlen(buf) == 2 && atoi(buf) >= 0 && atoi(buf) <= 31)
				{
					norm = 1;
				}
				else
				{
					printf("День должен состоять из цифр (2). Повторите попытку: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("Введите месяц подачи: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			for (i = 0; i < strlen(buf); i++)
			{
				if ((buf[i]) >= '0' && (buf[i]) <= '9' && strlen(buf) == 2 && atoi(buf) >= 0 && atoi(buf) <= 12)
				{
					norm = 1;
				}
				else
				{
					printf("Месяц должен состоять из цифр (2). Повторите попытку: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("Введите год подачи: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			for (i = 0; i < strlen(buf); i++)
			{
				if ((buf[i]) >= '0' && (buf[i]) <= '9' && strlen(buf) == 4)
				{
					norm = 1;
				}
				else
				{
					printf("Год должен состоять из цифр (4). Повторите попытку: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s\n", buf);
		printf("Товар успешно добавлен. Нажмите любую клавишу для продолжения...");
	}
	fclose(file);
	fill_goods();
	_getch();
	system("cls");
}

void delete_goods()
{
	FILE *file;
	int i, j = 0, was = 0;
	char name[200], nam[200];
	for (int i = 0; i < num_suppliers; i++)
	{
		strcpy(name, suppliers[i].name);
		strcat(name, ".txt");
		fopen_s(&file, name, "r");
		if (file == NULL)
		{
			continue;
		}
		printf("\nТОВАРЫ КОМПАНИИ \"%s\"", suppliers[i].name);
		printf("\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		int j = 0;
		while (strlen(suppliers[i].good[j].name) != 0)
		{
			printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year);
			printf("---------------------------------------------------------------------------------------------------------------\n");
			j++;
		}
		fclose(file);
	}
	printf("Введите название компании, у которой хотите удалить продукт: ");
	gets(name);
	for (i = 0; i <= num_suppliers; i++)
	{
		if (strcmp(name, suppliers[i].name) == 0)
		{
			was = 1;
			strcpy(name, suppliers[i].name);
			strcat(name, ".txt");
			strcpy(nam, name);
			break;
		}
		else
			was = 0;
	}
	if (was == 0)
	{
		printf("Такой компании нет. Нажмите любую клавишу для продолжения...");
		_getch();
		system("cls");
		return;
	}
	was = 0;
	printf("Введите название продукта, который хотите удалить: ");
	fopen_s(&file, nam, "r");
	gets(name);
	while (strlen(suppliers[i].good[j].name) != 0)
	{
		if (strcmp(name, suppliers[i].good[j].name) == 0)
		{
			was = 1;
		}
		j++;
	}
	j = 0;
	if (file != NULL)
		fclose(file);
	if (was == 0)
	{
		printf("Такого продукта нет. Нажмите любую клавишу для продолжения...");
		_getch();
		system("cls");
		return;
	}
	fopen_s(&file, nam, "w");
	while (strlen(suppliers[i].good[j].name) != 0)
	{
		if (strcmp(name, suppliers[i].good[j].name) == 0)
		{
			j++;
			continue;
		}
		else
		{
			fprintf(file, "%s ", suppliers[i].good[j].name);
			fprintf(file, "%s ", suppliers[i].good[j].model);
			fprintf(file, "%s ", suppliers[i].good[j].type);
			fprintf(file, "%s ", suppliers[i].good[j].id);
			fprintf(file, "%s ", suppliers[i].good[j].price);
			fprintf(file, "%s ", suppliers[i].good[j].day);
			fprintf(file, "%s ", suppliers[i].good[j].month);
			fprintf(file, "%s\n", suppliers[i].good[j].year);
		}
		j++;
	}
	printf("Продукт удалён. Нажмите любую клавишу для продолжения...");
	fclose(file);
	j = 0;
	for (i = 0; i < num_suppliers; i++)
	{
		char name[25];
		strcpy(name, suppliers[i].name);
		strcat(name, ".txt");
		fopen_s(&file, name, "r");
		if (file == NULL)
			continue;
		else
		{
			while (1)
			{
				fscanf_s(file, "%s", suppliers[i].good[j].name, _countof(suppliers[i].good[j].name));
				fscanf_s(file, "%s", suppliers[i].good[j].model, _countof(suppliers[i].good[j].model));
				fscanf_s(file, "%s", suppliers[i].good[j].type, _countof(suppliers[i].good[j].type));
				fscanf_s(file, "%s", suppliers[i].good[j].id, _countof(suppliers[i].good[j].id));
				fscanf_s(file, "%s", suppliers[i].good[j].price, _countof(suppliers[i].good[j].price));
				fscanf_s(file, "%s", suppliers[i].good[j].name, _countof(suppliers[i].good[j].day));
				fscanf_s(file, "%s", suppliers[i].good[j].name, _countof(suppliers[i].good[j].month));
				fscanf_s(file, "%s", suppliers[i].good[j].name, _countof(suppliers[i].good[j].year));
				char c;
				if ((c = fgetc(file)) == EOF)
					break;
				j++;
			}
			memset(suppliers[i].good[j].name, 0, sizeof(suppliers[i].good[j].name));
		}
		j = 0;
		fclose(file);
	}
	fill_goods();
	_getch();
	system("cls");
}

void fill_goods()
{
	FILE *file;
	int j = 0;
	for (int i = 0; i < num_suppliers; i++)
	{
		char name[25];
		extern int num_goods;
		strcpy(name, suppliers[i].name);
		strcat(name, ".txt");
		fopen_s(&file, name, "r");
		if (file == NULL)
			continue;
		else
		{
			while (1)
			{
				fscanf_s(file, "%s", suppliers[i].good[j].name, _countof(suppliers[i].good[j].name));
				fscanf_s(file, "%s", suppliers[i].good[j].model, _countof(suppliers[i].good[j].model));
				fscanf_s(file, "%s", suppliers[i].good[j].type, _countof(suppliers[i].good[j].type));
				fscanf_s(file, "%s", suppliers[i].good[j].id, _countof(suppliers[i].good[j].id));
				fscanf_s(file, "%s", suppliers[i].good[j].price, _countof(suppliers[i].good[j].price));
				fscanf_s(file, "%s", suppliers[i].good[j].day, _countof(suppliers[i].good[j].day));
				fscanf_s(file, "%s", suppliers[i].good[j].month, _countof(suppliers[i].good[j].month));
				fscanf_s(file, "%s", suppliers[i].good[j].year, _countof(suppliers[i].good[j].year));
				char c;
				if ((c = fgetc(file)) == EOF)
					break;
				j++;
				num_goods++;
			}
		}
		j = 0;
		fclose(file);
	}
}

void task()
{
	int array[60], i, j, g = 0, min, lenth;
	printf("[ВЫПОЛНЕНИЕ ЗАДАЧИ]\nТовары за последний месяц:\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			if (strcmp(suppliers[i].good[j].month, "04") == 0 && strcmp(suppliers[i].good[j].year, "2020") == 0)
			{
				printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year);
				printf("---------------------------------------------------------------------------------------------------------------\n");
			}
		}
	}
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			if (strcmp(suppliers[i].good[j].month, "04") == 0 && strcmp(suppliers[i].good[j].year, "2020") == 0)
			{
				min = atoi(suppliers[i].good[j].price);
				array[g] = i;
				g++;
				array[g] = j;
				g++;
			}
		}
		lenth = g;
	}
	if (g == 0)
	{
		printf("Товаров за последний месяц нет.");
		printf("\nНажмите любую клавишу для продолжения...");
		_getch();
		system("cls");
		return;
	}
	for (g = 0; g < lenth; g += 2)
	{
		if (atoi(suppliers[array[g]].good[array[g + 1]].price) <= min)
		{
			i = array[g];
			j = array[g + 1];
			min = atoi(suppliers[array[g]].good[array[g + 1]].price);
		}
	}
	printf("\nСамый дешёвый товар за последний месяц: ");
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |     Компания     |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s | %-17s|\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year, suppliers[i].name);
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
	return;
}

void find_name()
{
	char name[200];
	int i, j;
	printf("[ПОИСК ПО ИМЕНИ]\n");
	printf("Введите имя продукта или его часть: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 1)
		{
			printf("Название продукта должно содержать меньше 20, но больше 1 символов. Повторите попытку: \n");
			continue;
		}
		break;
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			if (strstr(suppliers[i].good[j].name, name) != NULL)
			{
				printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year);
				printf("---------------------------------------------------------------------------------------------------------------\n");
			}
		}
	}
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void find_id()
{
	char name[200];
	int i, j;
	printf("[ПОИСК ПО ID]\n");
	printf("Введите ID продукта или его часть: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 10 || strlen(name) < 1)
		{
			printf("ID продукта должно содержать меньше 10, но больше 1 символов. Повторите попытку: \n");
			continue;
		}
		break;
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			if (strstr(suppliers[i].good[j].id, name) != NULL)
			{
				printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year);
				printf("---------------------------------------------------------------------------------------------------------------\n");
			}
		}
	}
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void find_type()
{
	char name[200];
	int i, j;
	printf("[ПОИСК ПО ТИПУ]\n");
	printf("Введите тип продукта или его часть: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 1)
		{
			printf("Тип продукта должно содержать меньше 20, но больше 1 символов. Повторите попытку: \n");
			continue;
		}
		break;
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			if (strstr(suppliers[i].good[j].type, name) != NULL)
			{
				printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year);
				printf("---------------------------------------------------------------------------------------------------------------\n");
			}
		}
	}
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void filter_vozr(int num_goods)
{
	printf("[ФИЛЬТРАЦИЯ ПО ВОЗРАСТАНИЮ]\n");
	int step, i, j, tmp;
	int g = 0, arr[100];
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			arr[g] = atoi(suppliers[i].good[j].price);
			g++;
		}
	}
	for (step = num_goods / 2; step > 0; step /= 2)
		for (i = step; i < num_goods; i++)
			for (j = i - step; j >= 0 && arr[j] > arr[j + step]; j -= step)
			{
				tmp = arr[j];
				arr[j] = arr[j + step];
				arr[j + step] = tmp;
			}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_goods; i++)
	{
		for (g = 0; g < num_suppliers; g++)
		{
			for (j = 0; j < num_goods; j++)
			{
				if (arr[i] == atoi(suppliers[g].good[j].price))
				{
					printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[g].good[j].name, suppliers[g].good[j].model, suppliers[g].good[j].type, suppliers[g].good[j].id, suppliers[g].good[j].price, suppliers[g].good[j].day, suppliers[g].good[j].month, suppliers[g].good[j].year);
					printf("---------------------------------------------------------------------------------------------------------------\n");
				}
			}
		}
	}
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void filter_ubuv(int num_goods)
{
	printf("[ФИЛЬТРАЦИЯ ПО УБЫВАНИЮ]\n");
	int step, i, j, tmp;
	int g = 0, arr[100];
	for (i = 0; i < num_suppliers; i++)
	{
		for (j = 0; strlen(suppliers[i].good[j].name) != 0; j++)
		{
			arr[g] = atoi(suppliers[i].good[j].price);
			g++;
		}
	}
	for (step = num_goods / 2; step > 0; step /= 2)
		for (i = step; i < num_goods; i++)
			for (j = i - step; j >= 0 && arr[j] < arr[j + step]; j -= step)
			{
				tmp = arr[j];
				arr[j] = arr[j + step];
				arr[j + step] = tmp;
			}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  Название продукта   | Модель |       Тип         |  Идентификационный номер  |      Цена     | Дата подачи |\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_goods; i++)
	{
		for (g = 0; g < num_suppliers; g++)
		{
			for (j = 0; j < num_goods; j++)
			{
				if (arr[i] == atoi(suppliers[g].good[j].price))
				{
					printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s |\n", suppliers[g].good[j].name, suppliers[g].good[j].model, suppliers[g].good[j].type, suppliers[g].good[j].id, suppliers[g].good[j].price, suppliers[g].good[j].day, suppliers[g].good[j].month, suppliers[g].good[j].year);
					printf("---------------------------------------------------------------------------------------------------------------\n");
				}
			}
		}
	}
	printf("Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void clear_users()
{
	FILE *file;
	fopen_s(&file, "users.txt", "w");
	fclose(file);
	printf("Успешная очистка! Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}

void clear_companies()
{
	FILE *file;
	fopen_s(&file, "companies.txt", "w");
	fclose(file);
	printf("Успешная очистка! Нажмите любую клавишу для продолжения...");
	_getch();
	system("cls");
}