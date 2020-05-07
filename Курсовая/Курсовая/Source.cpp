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
	char name[20];			// ��� ������������
	char password[20];		// ������ ������������
} users[100];

struct locations
{
	char town[20];		// �����
	char street[20];	// �����
	char number[20];	// ����� ������
};

struct goods
{
	char name[20];		// �������� ��������
	char type[20];		// ��� ��������
	char model[20];		// ������ ��������
	char id[10];		// ���������� ����� ��������
	char price[10];		// ���� ��������
	char day[3];		// ����
	char month[3];		// �����
	char year[5];		// ���
};

struct SUPPLIER
{
	char name[20];				// �������� ��������
	struct locations location;	// ���������� � ��������������
	struct goods good[10];		// ������ ��������
	char first_name[20];		// ��� ������������� ��������
	char second_name[20];		// ������� ������������� ��������
	char last_name[20];			// �������� ������������� ��������
	char phone[20];				// �������
	char day[3];				// ����
	char month[3];				// �����
	char year[5];				// ���
} suppliers[100];

void menu();				// ���� �����
void admin();				// ����������� ��� ��������������
void user();				// ����������� ��� ������������
void user_menu();			// ���� ��� ������������
void admin_menu();			// ���� ��� ��������������
void actions_with_users();	// ���� ���������� ��������������
void delete_user();			// ������� �������� ������������
void create_user();			// ������� ���������� ������������
void show_users();			// ������� ����������� ������ ������������� � ��������� �����
void count_users();			// ������� �������� ���������� �������������
void fill_companies();		// ������� ���������� ����� ���������, �������� ������ � ����������
void count_companies();		// ������� �������� ���������� ��������
void edit_supplier();		// ������� �������������� ������ ����������
void show_suppliers();		// ������� ����������� ������ ����������� � ��������� �����
void show_goods();			// ������� ����������� ���������� � ������� � ��������� �����
void add_goods();			// ������� ���������� ������ ��� ����������
void delete_goods();		// ������� �������� ������ ����������
void delete_supplier();		// ������� �������� ����������
void fill_goods();			// ������� ���������� ����� ���������, ���������� ���������� � ������� �����������
void encrypt(char user_buf_name[20], char user_buf_password[20]); // ������� ���������� ������ � ������ ������������
void decipher();			// ������� ������������ ������� � �������
void add_supplier();		// ������� ���������� ���������� 
void task();				// ������� ���������� ������
void find_name();			// ������� ������ ������ �� �����
void find_id();				// ������� ������ ������ �� ����������� ������
void find_type();			// ������� ������ ������ �� ����
void filter_vozr(int num_goods);	// ���������� ������ �� ���� (�����������)
void filter_ubuv(int num_goods);	// ���������� ������ �� ���� (��������)
void clear_users();			// ������� ������� ����� � ��������������
void clear_companies();		// ������� ������� ����� � ����������

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
	printf("1 - ���� ��� �������������\n2 - ���� ��� ������������\n3 - �����\n");
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
			printf("1 - ����� ��� �������������\n2 - ����� ��� ������������\n3 - �����\n");
			printf("������� ���������� ������ (�� �����: %c)\n", choice);
		}
	}
}

void admin()
{
	char login[100], password[100], esc;

	while (1)
	{
		printf("������� �����: ");
		gets(login);
		if (strlen(login) >= 20)
		{
			system("cls");
			printf("����� �������� ����� 20 ��������. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
			printf("�������� �����. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
		printf("������� ������: ");
		gets(password);
		if (strlen(password) >= 20)
		{
			system("cls");
			printf("������ �������� ����� 20 ��������. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
			printf("�������� ������. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
		printf("[���� ������������]\n");
		printf("1 - �������� ���� ������ � ��������� �����\n2 - ���������� ������\n3 - ��������� ��������� ������ � ���������� ������\n4 - �����\n");
		choice = _getch();
		if (choice == '1')
		{
			system("cls");
			while (1)
			{
				printf("[�������� ���� ������ � ��������� �����]\n");
				printf("1 - ������ ����������� � �����������\n2 - ������ ������\n3 - �����");
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
					printf("������� ���������� ������ (�� �����: %c)\n", choice);
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
				printf("[��������� ��������� ������ � ���������� ������]\n");
				printf("1 - ����� ������ �� �����\n2 - ����� ������ �� ����\n3 - ����� ������ �� ID\n4 - ���������� �� �����������\n5 - ���������� �� ��������\n6 - �����");
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
					printf("������� ���������� ������ (�� �����: %c)\n", choice);
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
		printf("[���� ��������������]\n");
		printf("1 - ���������� ������\n2 - �������� � ������� ���������� � ��������\n3 - �������� ���� ������ � ��������� �����\n4 - ��������� ��������� ������ � ���������� ������\n5 - ���������� ��������������\n6 - ������ � �������\n7 - �����\n");
		choice = _getch();
		if (choice == '1')
		{
			system("cls");
			while (1)
			{
				printf("[���������� ������]\n");
				printf("1 - ���������� ������ ����������\n2 - ���������� ������ ��� ����������\n3 - �����");
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
				printf("[�������� � ������� ���������� � ��������]\n");
				printf("1 - �������������� ������ ����������\n2 - �������� ����������\n3 - �������� ������\n4 - �����");
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
				printf("[�������� ���� ������ � ��������� �����]\n");
				printf("1 - ������ ����������� � �����������\n2 - ������ ������\n3 - �����");
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
				printf("[��������� ��������� ������ � ���������� ������]\n");
				printf("1 - ����� ������ �� �����\n2 - ����� ������ �� ����\n3 - ����� ������ �� ID\n4 - ���������� �� �����������\n5 - ���������� �� ��������\n6 - �����");
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
				printf("[������ � �������]\n");
				printf("1 - ������� ����� � ��������������\n2 - ������� ����� � ����������\n3 - �����\n");
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
		printf("������� �����: ");
		gets(login);
		if (strlen(login) >= 20)
		{
			system("cls");
			printf("����� �������� ����� 20 ��������. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
			printf("�������� �����. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
		printf("������� ������: ");
		gets(password);
		if (strlen(password) > 20 || strlen(password) < 8)
		{
			system("cls");
			printf("������ ������ ��������� �� ����� 20 � �� ������ 8 ��������. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
			printf("�������� ������. ������� ESC ��� ������ ��� ����� ������� ��� ���������� ����� ������: ");
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
		printf("[���������� ��������������]\n");
		printf("1 - ���������� ������������\n2 - �������� ������������\n3 - �������� ������ �������������\n4 - �����\n");
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
	printf("[�������� ������������]");
	printf("\n");
	printf("---------------------------------------------\n");
	printf("|        �����        |       ������        |\n");
	printf("---------------------------------------------\n");
	for (i = 0; i < num_users; i++)
	{
		printf("| %-20s| %-20s|\n", users[i].name, users[i].password);		//����� ������ � ������ ������������ �� �����
		printf("---------------------------------------------\n");
	}
	printf("���-�� �������������: %d\n", num_users);
	printf("������� ��� ������������, �������� ������ �������: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 4)
		{
			printf("��� ������������ ������ ���� ������ 20, �� ������ 4 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ')
			{
				probel = 1;
				printf("��� ������������ �� ������ ��������� ��������. ��������� �������: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i < num_users; i++)
		{
			if (strcmp(name, users[i].name) == 0)		//��������� ��������� ����� � ������� � ���� ������ ��� �������� ����������� ������������
			{
				fscanf_s(file, "%*s");
				fscanf_s(file, "%*s");
				was = 1;
				printf("������������ � ������ [%s] �����. ������� ����� ������� ��� �����������...", users[i].name);	//����� ����� ��������� ������������ �� �����
				fscanf_s(file, "%s", users[i].name, _countof(users[i].name));		//���������� ����� ���������� ������������ �� ����� ������ ���������
				fscanf_s(file, "%s", users[i].password, _countof(users[i].password));		//���������� ������ ���������� ������������ �� ����� ������ ���������
			}
			else
			{
				fscanf_s(file, "%s", users[i].name, _countof(users[i].name));		//���������� ����� ������������ �� �����
				fscanf_s(file, "%s", users[i].password, _countof(users[i].password));		//���������� ������ ������������ �� �����
			}
		}
		if (was == 0)
		{
			printf("��� ������������ � ����� ������. ������� ����� ������� ��� �����������...");
			fclose(file);
			count_users();
			decipher();
			break;
		}
		fclose(file);
		fopen_s(&file, "users.txt", "w");
		for (i = 0; i < num_users - 1; i++)
		{
			fprintf(file, "%s ", users[i].name);		//������ ����� ������������ � ����
			fprintf(file, "%s\n", users[i].password);		////������ ������ ������������ � ����
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
	printf("[���������� ������������]\n");
	int i, was = 0, probel = 0;
	char user_buf_name[21];
	char user_buf_password[21];
	fopen_s(&file, "users.txt", "a");
	printf("������� ��� ������������, �������� ������ ��������: ");
	while (1)
	{
		gets(user_buf_name);
		if (strlen(user_buf_name) > 20 || strlen(user_buf_name) < 4)
		{
			printf("��� ������������ ������ ���� ������ 20, �� ������ 4 ��������. ��������� �������: ");
			*user_buf_name = 0;
			continue;
		}
		for (i = 0; i < strlen(user_buf_name); i++)
		{
			if (user_buf_name[i] == ' ')
			{
				probel = 1;
				printf("��� ������������ �� ������ ��������� ��������. ��������� �������: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i < num_users; i++)
		{
			if (strcmp(user_buf_name, users[i].name) == 0)		//��������� ����� ������ ������������ � ������������� � ���� ������ ��� ���������� ���������� ������
			{
				printf("������������ � ����� ������ ��� ����������, ��������� �������: ");
				was = 1;
				break;
			}
			else was = 0;
		}
		if (was == 1)
			continue;
		break;
	}
	printf("������� ������ ������������: ");
	while (1)
	{
		gets(user_buf_password);
		for (i = 0; i < strlen(user_buf_password); i++)
		{
			if (user_buf_password[i] == ' ')
			{
				probel = 1;
				printf("������ ������������ �� ������ ��������� ��������. ��������� �������: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		if (strlen(user_buf_password) > 20 || strlen(user_buf_password) < 8)
		{
			printf("������ ������������ ������ ������ 8, �� ������ 20 ��������. ��������� �������: ");
			continue;
		}
		break;
	}
	printf("������������ [%s], � ������� [%s] ������� ������!", user_buf_name, user_buf_password);
	fclose(file);
	encrypt(user_buf_name, user_buf_password);
	printf("\n������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void show_users()
{
	int i;
	printf("\n");
	printf("---------------------------------------------\n");
	printf("|        �����        |       ������        |\n");
	printf("---------------------------------------------\n");
	for (i = 0; i < num_users; i++)
	{
		printf("| %-20s| %-20s|\n", users[i].name, users[i].password);		//����� ������ � ������ ������������ �� �����
		printf("---------------------------------------------\n");
	}
	printf("���-�� �������������: %d\n", num_users);
	printf("������� ����� ������� ��� �����������...");
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

// ����������
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
		if (c >= '�' && c <= '�')
		{
			c = c + (n % RUS);
			if (c > '�') c = '�' + (c - '�') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= '�' && c <= '�')
		{
			c = c + (n % RUS);
			if (c > '�') c = '�' + (c - '�') - 1;
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
		if (c >= '�' && c <= '�')
		{
			c = c + (n % RUS);
			if (c > '�') c = '�' + (c - '�') - 1;
			fprintf(file, "%c", c);
			flag = 1;
		}
		if (c >= '�' && c <= '�')
		{
			c = c + (n % RUS);
			if (c > '�') c = '�' + (c - '�') - 1;
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

// ������������
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
			if (c >= '�' && c <= '�')
			{
				c = c - (n % RUS);
				if (c < '�') c = '�' - ('�' - c) + 1;
				users[i].name[j] = c;
				flag = 1;
			}
			if (c >= '�' && c <= '�')
			{
				c = c - (n % RUS);
				if (c < '�') c = '�' - ('�' - c) + 1;
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
			if (c >= '�' && c <= '�')
			{
				c = c - (n % RUS);
				if (c < '�') c = '�' - ('�' - c) + 1;
				users[i].password[j] = c;
				flag = 1;
			}
			if (c >= '�' && c <= '�')
			{
				c = c - (n % RUS);
				if (c < '�') c = '�' - ('�' - c) + 1;
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
	printf("[���������� ����������]\n");
	printf("������� �������� ��������: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("�������� �������� ������ ���� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("�������� �������� �� ������ ��������� �������� (����). ��������� �������: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i < num_suppliers; i++)
		{
			if (strcmp(buf, suppliers[i].name) == 0)	//��������� ������ �������� �������� � ������������� � ���� ������
			{
				printf("�������� � ����� ��������� ��� ����������, ��������� �������: ");
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
	printf("������� ��������������� �������� (�����)\n");
	printf("������� �����: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("�������� ������ ������ ���� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("�������� ������ �� ������ ��������� �������� (����). ��������� �������: ");
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
	printf("������� �����: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("�������� ����� ������ ���� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("�������� ����� �� ������ ��������� �������� (����). ��������� �������: ");
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
	printf("������� ����� ������: ");
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
				printf("����� ������ ������ �������� �� ����. ��������� �������: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("������� ������������� ��������\n");
	printf("������� ���: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("��� ������ ���� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("��� �� ������ ��������� �������� (����). ��������� �������: ");
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
	printf("������� �������: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("������� ������ ���� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("������� �� ������ ��������� �������� (����). ��������� �������: ");
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
	printf("������� ��������: ");
	while (1)
	{
		gets(buf);
		if (strlen(buf) > 20 || strlen(buf) < 2)
		{
			printf("�������� ������ ���� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				probel = 1;
				printf("�������� �� ������ ��������� ��������. ��������� �������: ");
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
	printf("������� ����� ��� �����: +");
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
				printf("����� ������ �������� �� ����. ��������� �������: +");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("������� ���� ����������� (� �������, 06): ");
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
				printf("���� ������ �������� �� ���� (2). ��������� �������: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("������� ����� ����������� (� �������, 06): ");
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
				printf("����� ������ �������� �� ���� (2). ��������� �������: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s ", buf);
	printf("������� ��� �����������: ");
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
				printf("��� ������ �������� �� ���� (4). ��������� �������: ");
				norm = 0;
				break;
			}
		}
	}
	fprintf(company, "%s\n", buf);
	printf("����� ��������� ������� ��������!\n������� ����� ������� ��� �����������...");
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
		fscanf_s(file, "%s", suppliers[i].name, _countof(suppliers[i].name));	//���������� ����� �������� �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].location.town, _countof(suppliers[i].location.town));		//���������� ������ �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].location.street, _countof(suppliers[i].location.street));		//���������� ����� �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].location.number, _countof(suppliers[i].location.number));		//���������� ����� ������ �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].first_name, _countof(suppliers[i].first_name));		//���������� ����� ������������� �������� �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].second_name, _countof(suppliers[i].second_name));		//���������� ������� ������������� �������� �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].last_name, _countof(suppliers[i].last_name));			//���������� �������� ������������� �������� �� ����� � ���� ������ (���������)
		fscanf_s(file, "%s", suppliers[i].phone, _countof(suppliers[i].phone));			//���������� ������ �������� �� ����� � ���� ������ (���������)
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
	printf("[�������� ����������]");
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   |                      ���������������                       |                      ������������� (��������)                 |       �������       | ���� ����������� |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s| �.%-20s ��.%-20s �.%-10s| %-20s %-20s %-20s| +%-19s| \t%s.%s.%s   |\n", suppliers[i].name, suppliers[i].location.town, suppliers[i].location.street, suppliers[i].location.number, suppliers[i].second_name, suppliers[i].first_name, suppliers[i].last_name, suppliers[i].phone, suppliers[i].day, suppliers[i].month, suppliers[i].year);	//����� ���������� � ���������� �� �����
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("���-�� �����������: %d\n", num_suppliers);
	printf("������� �������� ��������, ������� ������ �������: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 2)
		{
			printf("�������� �������� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ' || (name[i] >= '0' && name[i] <= '9'))
			{
				probel = 1;
				printf("�������� �������� �� ������ ��������� �������� (����). ��������� �������: ");
				break;
			}
			else
				probel = 0;
		}
		if (probel == 1)
			continue;
		for (i = 0; i <= num_suppliers; i++)
		{
			if (strcmp(name, suppliers[i].name) == 0)	//��������� ����� ��������� �������� � ������� �������� � ���� ������
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
				printf("�������� [%s] ������. ������� ����� ������� ��� �����������...", suppliers[i].name);	//����� ����� �������� ��������
				fscanf_s(file, "%s", suppliers[i].name, _countof(suppliers[i].name));	//���������� ����� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].location.town, _countof(suppliers[i].location.town));	//���������� ������ �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].location.street, _countof(suppliers[i].location.street));	//���������� ����� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].location.number, _countof(suppliers[i].location.number));	//���������� ����� ������ �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].first_name, _countof(suppliers[i].first_name));	//���������� ����� ������������� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].second_name, _countof(suppliers[i].second_name));	//���������� ������� ������������� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].last_name, _countof(suppliers[i].last_name));	//���������� �������� ������������� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].phone, _countof(suppliers[i].phone));	//���������� ������ �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].day, _countof(suppliers[i].day));
				fscanf_s(file, "%s", suppliers[i].month, _countof(suppliers[i].month));
				fscanf_s(file, "%s", suppliers[i].year, _countof(suppliers[i].year));
			}
			else
			{
				fscanf_s(file, "%s", suppliers[i].name, _countof(suppliers[i].name));	//���������� ����� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].location.town, _countof(suppliers[i].location.town));	//���������� ������ �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].location.street, _countof(suppliers[i].location.street));	//���������� ����� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].location.number, _countof(suppliers[i].location.number));	//���������� ����� ������ �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].first_name, _countof(suppliers[i].first_name));	//���������� ����� ������������� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].second_name, _countof(suppliers[i].second_name));	//���������� ������� ������������� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].last_name, _countof(suppliers[i].last_name));	//���������� �������� ������������� �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].phone, _countof(suppliers[i].phone));	//���������� ������ �������� �� ����� � ���� ������ (���������)
				fscanf_s(file, "%s", suppliers[i].day, _countof(suppliers[i].day));
				fscanf_s(file, "%s", suppliers[i].month, _countof(suppliers[i].month));
				fscanf_s(file, "%s", suppliers[i].year, _countof(suppliers[i].year));
			}
		}
		if (was == 0)
		{
			printf("��� �������� � ����� ���������. ������� ����� ������� ��� �����������...");
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
			fprintf(file, "%s ", suppliers[i].name);	//������ �������� �������� � ����
			fprintf(file, "%s ", suppliers[i].location.town);	//������ ������ � ����
			fprintf(file, "%s ", suppliers[i].location.street);	//������ ����� � ����
			fprintf(file, "%s ", suppliers[i].location.number);	//������ ������ ������ � ����
			fprintf(file, "%s ", suppliers[i].first_name);	//������ ����� ������������� �������� � ����
			fprintf(file, "%s ", suppliers[i].second_name);	//������ ������� ������������� �������� � ����
			fprintf(file, "%s ", suppliers[i].last_name);	//������ �������� ������������� �������� � ����
			fprintf(file, "%s ", suppliers[i].phone);	//������ ������ �������� � ����
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
	printf("|  �������� ��������   |                      ���������������                       |                      ������������� (��������)                 |       �������       | ���� ����������� |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s| �.%-20s ��.%-20s �.%-10s| %-20s %-20s %-20s| +%-19s| \t%s.%s.%s   |\n", suppliers[i].name, suppliers[i].location.town, suppliers[i].location.street, suppliers[i].location.number, suppliers[i].second_name, suppliers[i].first_name, suppliers[i].last_name, suppliers[i].phone, suppliers[i].day, suppliers[i].month, suppliers[i].year);	//����� ���������� � ���������� �� �����
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("���-�� �����������: %d\n", num_suppliers);
	printf("������� ����� ������� ��� �����������...");
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
		printf("\n������ �������� \"%s\"", suppliers[i].name);
		printf("\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void edit_supplier()
{
	FILE *file;
	int i, probel = 0, was = 0, norm = 0, j;
	char name[200], buf[200];
	fopen_s(&file, "companies.txt", "r");
	printf("[��������� ������ ����������]");
	printf("\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   |                      ���������������                       |                      ������������� (��������)                 |       �������       |\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s| �.%-20s ��.%-20s �.%-10s| %-20s %-20s %-20s| +%-19s|\n", suppliers[i].name, suppliers[i].location.town, suppliers[i].location.street, suppliers[i].location.number, suppliers[i].second_name, suppliers[i].first_name, suppliers[i].last_name, suppliers[i].phone);	//����� ���������� � ���������� �� �����
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("���-�� �����������: %d\n", num_suppliers);
	printf("������� �������� ��������, � ������� ������ �������� ���������: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 2)
		{
			printf("�������� �������� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ' || (name[i] >= '0' && name[i] <= '9'))
			{
				probel = 1;
				printf("�������� �������� �� ������ ��������� �������� (����). ��������� �������: ");
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
			if (strcmp(name, suppliers[i].name) == 0)	//��������� ����� ��������� �������� � ������� �������� � ���� ������
			{
				while (1)
				{
					printf("1 - �������������� ������\n2 - �������������� �����\n3 - �������������� ����\n4 - �������������� ����� �������������\n5 - �������������� ������� �������������\n6 - �������������� �������� �������������\n7 - �������������� ������\n8 - �����\n");
					choice = _getch();
					if (choice == '1')
					{
						printf("������� �����: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("�������� ������ ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("�������� ������ �� ������ ��������� �������� (����). ��������� �������: ");
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
						printf("������� �����: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("�������� ����� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("�������� ����� �� ������ ��������� �������� (����). ��������� �������: ");
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
						printf("������� ����� ������: ");
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
									printf("����� ������ ������ �������� �� ����. ��������� �������: ");
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
						printf("������� ���: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("��� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("��� �� ������ ��������� �������� (����). ��������� �������: ");
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
						printf("������� �������: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("������� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("������� �� ������ ��������� �������� (����). ��������� �������: ");
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
						printf("������� ��������: ");
						while (1)
						{
							gets(buf);
							if (strlen(buf) > 20 || strlen(buf) < 2)
							{
								printf("�������� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
								continue;
							}
							for (j = 0; j < strlen(buf); j++)
							{
								if (buf[j] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
								{
									probel = 1;
									printf("�������� �� ������ ��������� �������� (����). ��������� �������: ");
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
						printf("������� ����� ��� �����: +");
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
									printf("����� ������ �������� �� ����. ��������� �������: +");
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
						printf("��� ������ ������!\n������� ����� ������� ��� �����������...");
						_getch();
						system("cls");
						return;
					}
				}
				printf("������ ���������� ������� ��������!\n������� ����� ������� ��� �����������...");
				_getch();
				system("cls");
				was = 1;
			}
		}
		if (was == 0)
		{
			printf("��� �������� � ����� ���������. ������� ����� ������� ��� �����������...");
			fclose(file);
			_getch();
			system("cls");
			break;
		}
		fclose(file);
		fopen_s(&file, "companies.txt", "w");
		for (i = 0; i < num_suppliers; i++)
		{
			fprintf(file, "%s ", suppliers[i].name);	//������ �������� �������� � ����
			fprintf(file, "%s ", suppliers[i].location.town);	//������ ������ � ����
			fprintf(file, "%s ", suppliers[i].location.street);	//������ ����� � ����
			fprintf(file, "%s ", suppliers[i].location.number);	//������ ������ ������ � ����
			fprintf(file, "%s ", suppliers[i].first_name);	//������ ����� ������������� �������� � ����
			fprintf(file, "%s ", suppliers[i].second_name);	//������ ������� ������������� �������� � ����
			fprintf(file, "%s ", suppliers[i].last_name);	//������ �������� ������������� �������� � ����
			fprintf(file, "%s ", suppliers[i].phone);	//������ ������ �������� � ����
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
	printf("[���������� ������]");
	printf("\n");
	printf("------------------------\n");
	printf("|  �������� ��������   |\n");
	printf("------------------------\n");
	for (i = 0; i < num_suppliers; i++)
	{
		printf("| %-21s|\n", suppliers[i].name);	//����� ���������� � ���������� �� �����
		printf("------------------------\n");
	}
	printf("���-�� �����������: %d\n", num_suppliers);
	printf("������� �������� ��������, ������� ����� ���������� �������: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 2)
		{
			printf("�������� �������� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
			continue;
		}
		for (i = 0; i < strlen(name); i++)
		{
			if (name[i] == ' ' || (name[i] >= '0' && name[i] <= '9'))
			{
				probel = 1;
				printf("�������� �������� �� ������ ��������� �������� (����). ��������� �������: ");
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
		printf("��� ����� ��������. ������� ����� ������� ��� �����������...");
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
		printf("������� �������� ��������: ");
		while (1)
		{
			gets(buf);
			if (strlen(buf) > 20 || strlen(buf) < 2)
			{
				printf("�������� �������� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
				{
					probel = 1;
					printf("�������� �������� �� ������ ��������� �������� (����). ��������� �������: ");
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
		printf("������� ������ ��������: ");
		while (1)
		{
			gets(buf);
			if (strlen(buf) > 7 || strlen(buf) < 1)
			{
				printf("������ �������� ������ ��������� ������ 7, �� ������ 1 ��������. ��������� �������: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if (buf[i] == ' ')
				{
					probel = 1;
					printf("��� �� ������ ��������� ��������. ��������� �������: ");
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
		printf("������� ��� ��������: ");
		while (1)
		{
			gets(buf);
			if (strlen(buf) > 20 || strlen(buf) < 2)
			{
				printf("��� ������ ��������� ������ 20, �� ������ 2 ��������. ��������� �������: ");
				continue;
			}
			for (i = 0; i < strlen(buf); i++)
			{
				if (buf[i] == ' ' || (buf[i] >= '0' && buf[i] <= '9'))
				{
					probel = 1;
					printf("��� �� ������ ��������� �������� ��� ����. ��������� �������: ");
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
		printf("������� ���������� ����� ��������: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			if (strlen(buf) > 10 || strlen(buf) == 0)
			{
				printf("���������� ����� �������� ������ ��������� ������ 20, �� ������ 1 ��������. ��������� �������: ");
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
					printf("���������� ����� �������� ������ �������� �� ����. ��������� �������: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("������� ���� ��������: ");
		norm = 0;
		while (norm == 0)
		{
			gets(buf);
			if (strlen(buf) > 10 || strlen(buf) == 0)
			{
				printf("���� �������� ������ ��������� ������ 20, �� ������ 1 ��������. ��������� �������: ");
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
					printf("���� ������ �������� �� ����. ��������� �������: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("������� ���� ������: ");
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
					printf("���� ������ �������� �� ���� (2). ��������� �������: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("������� ����� ������: ");
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
					printf("����� ������ �������� �� ���� (2). ��������� �������: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s ", buf);
		printf("������� ��� ������: ");
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
					printf("��� ������ �������� �� ���� (4). ��������� �������: ");
					norm = 0;
					break;
				}
			}
		}
		fprintf(file, "%s\n", buf);
		printf("����� ������� ��������. ������� ����� ������� ��� �����������...");
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
		printf("\n������ �������� \"%s\"", suppliers[i].name);
		printf("\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� �������� ��������, � ������� ������ ������� �������: ");
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
		printf("����� �������� ���. ������� ����� ������� ��� �����������...");
		_getch();
		system("cls");
		return;
	}
	was = 0;
	printf("������� �������� ��������, ������� ������ �������: ");
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
		printf("������ �������� ���. ������� ����� ������� ��� �����������...");
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
	printf("������� �����. ������� ����� ������� ��� �����������...");
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
	printf("[���������� ������]\n������ �� ��������� �����:\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
		printf("������� �� ��������� ����� ���.");
		printf("\n������� ����� ������� ��� �����������...");
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
	printf("\n����� ������� ����� �� ��������� �����: ");
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |     ��������     |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("| %-21s| %-7s| %-18s| %-26s| %-14s|  %s.%s.%s | %-17s|\n", suppliers[i].good[j].name, suppliers[i].good[j].model, suppliers[i].good[j].type, suppliers[i].good[j].id, suppliers[i].good[j].price, suppliers[i].good[j].day, suppliers[i].good[j].month, suppliers[i].good[j].year, suppliers[i].name);
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
	return;
}

void find_name()
{
	char name[200];
	int i, j;
	printf("[����� �� �����]\n");
	printf("������� ��� �������� ��� ��� �����: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 1)
		{
			printf("�������� �������� ������ ��������� ������ 20, �� ������ 1 ��������. ��������� �������: \n");
			continue;
		}
		break;
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void find_id()
{
	char name[200];
	int i, j;
	printf("[����� �� ID]\n");
	printf("������� ID �������� ��� ��� �����: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 10 || strlen(name) < 1)
		{
			printf("ID �������� ������ ��������� ������ 10, �� ������ 1 ��������. ��������� �������: \n");
			continue;
		}
		break;
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void find_type()
{
	char name[200];
	int i, j;
	printf("[����� �� ����]\n");
	printf("������� ��� �������� ��� ��� �����: ");
	while (1)
	{
		gets(name);
		if (strlen(name) > 20 || strlen(name) < 1)
		{
			printf("��� �������� ������ ��������� ������ 20, �� ������ 1 ��������. ��������� �������: \n");
			continue;
		}
		break;
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void filter_vozr(int num_goods)
{
	printf("[���������� �� �����������]\n");
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
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void filter_ubuv(int num_goods)
{
	printf("[���������� �� ��������]\n");
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
	printf("|  �������� ��������   | ������ |       ���         |  ����������������� �����  |      ����     | ���� ������ |\n");
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
	printf("������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void clear_users()
{
	FILE *file;
	fopen_s(&file, "users.txt", "w");
	fclose(file);
	printf("�������� �������! ������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}

void clear_companies()
{
	FILE *file;
	fopen_s(&file, "companies.txt", "w");
	fclose(file);
	printf("�������� �������! ������� ����� ������� ��� �����������...");
	_getch();
	system("cls");
}