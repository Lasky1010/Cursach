
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
	cout << "�� ������� ��� ������ �������?" <<
		"\n\t1. ��" <<
		"\n\t2. ���\n\n";
	cout << "��������: ";
	choice = EnterNum();
	if (choice == 1) cout << "������ ������� �������!" << endl;
	return del = (choice == 1 ? true : false);
}
bool EDIT()
{
	int choice = 0;
	bool edit = true;
	cout << "�� ������� ��� ������ ���������������?" <<
		"\n\t1. ��" <<
		"\n\t2. ���\n\n";
	cout << "��������: ";
	choice = EnterNum();
	if (choice == 1) cout << "������ ������� ���������������!" << endl;
	return edit = (choice == 1 ? true : false);
}
bool NEW()
{
	int choice = 0;
	bool New = true;
	cout << "�� ������� ��� ������ �������� ������?" <<
		"\n\t1. ��" <<
		"\n\t2. ���\n\n";
	cout << "��������: ";
	choice = EnterNum();
	if (choice == 1) cout << "������ ������� ���������!" << endl;
	return New = (choice == 1 ? true : false);
}

int EnterNum()
{
	int num;
	while (true)
	{
		cin >> num;
		if (isNum())/* system("cls");*/  return num;
		cout << "������������ ����!\n";
	}

}
double EnterNumD()
{
	double num;
	while (true)
	{
		cin >> num;
		if (isNum())  return num;
		cout << "������������ ����!\n";
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


