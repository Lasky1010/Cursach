
#include <iostream>
#include <windows.h>
#include <string>
#include <string.h>
#include <conio.h>
#include"validation.h"
using namespace std;

bool DEL()
{
	int choice = 0;
	bool del = true;
	cout << "Вы уверены что хотите удалить?" <<
		"\n\t1. Да" <<
		"\n\t2. Нет\n\n";
	cout << "Выберите: ";
	choice = EnterNum();
	if (choice == 1) cout << "Данные успешно удалены!" << endl;
	return del = (choice == 1 ? true : false);
}
bool EDIT()
{
	int choice = 0;
	bool edit = true;
	cout << "Вы уверены что хотите отредактировать?" <<
		"\n\t1. Да" <<
		"\n\t2. Нет\n\n";
	cout << "Выберите: ";
	choice = EnterNum();
	if (choice == 1) cout << "Данные успешно отредактированы!" << endl;
	return edit = (choice == 1 ? true : false);
}
bool NEW()
{
	int choice = 0;
	bool New = true;
	cout << "Вы уверены что хотите добавить данные?" <<
		"\n\t1. Да" <<
		"\n\t2. Нет\n\n";
	cout << "Выберите: ";
	choice = EnterNum();
	if (choice == 1) cout << "Данные успешно добавлены!" << endl;
	return New = (choice == 1 ? true : false);
}

int EnterNum()
{
	int num;
	while (true)
	{
		cin >> num;
		if (isNum())/* system("cls");*/  return num;
		cout << "Некорректный ввод!\n";
	}

}
double EnterNumD()
{
	double num;
	while (true)
	{
		cin >> num;
		if (isNum())  return num;
		cout << "Некорректный ввод!\n";
	}
}
bool isNum()
{
	if (cin.get() == '\n') return true;
	else
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}


