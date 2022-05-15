#include <iostream>
#include <Windows.h>
#include <fstream>
#include<conio.h>
#include<string>
#include"validation.h"
using namespace std;

//	���������� ��� ������ � ������
fstream FILE_USERS;
fstream FILE_SHOES;

//	������
class Authentication;
class Shoes_Shop;


//	���� � �������� ������ � ������
int Entry(Authentication& authent);

//	���� ��� ������ � ��������������
void menu_authentication(Authentication& authent);
//	���� ��� ������ � �������
void ShoesProperties_Menu(Shoes_Shop& ss, int access);

//	�������� ������
const string UsersFile = "Authentication.txt";
const string ShoesFile = "Shoes.txt";



//	�������������� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Authentication
{
public:
	//	�����������
	Authentication();
	//	����������
	~Authentication();

	//	��������������
	int authentication(const string login, const string pass);
	//	�������� �� ������������ ������
	bool checkUniq(const string login);

	//	�������� ���� �������������
	void printAll();
	//	�������� �� ������������� ������
	void printBYlogin(string login);
	//	������� ���������� �������������
	int GetVol() { return Vol; }

	//	����������
	void PushFront(const string login, const string pass);

	//	�������������� ������ � ������
	void edit_all(const string login);
	//	�������������� ������
	void edit_login(const string login);
	//	�������������� ������
	void edit_pass(const string login);

	//	�������� ������� ������������
	void pop_front();
	//	�������� ���� �������������
	void clear();
	//	�������� �� �����
	void removeBYlogin(const string login);

private:
	//	��������� �����	/	������������
	class User
	{
	public:
		//	��������� �� ��������� ������
		User* pNext;
		//	�����
		string login;
		//	������
		string Pass;

		//	�����������
		User(string login, string pass, User* next = nullptr)
		{
			this->login = login;
			Pass = pass;
			pNext = next;
		}
	};

	//	��������� �� ������ ������
	User* begin;
	//	���������� �������������
	int Vol;

	//	������ �� �����
	void ReadFrom(fstream& fs);
	//	������ � ����
	void WriteIn(fstream& fs);

	//	����� � ������ ��������������
	string AdminLogin = "admin";
	string AdminPass = "admin";
};

//	�����������	/	Authen

//	���������� ���������� ���������� ����/�����
istream& operator >> (istream& is, Authentication& shs) { is >> shs; return is; }
ostream& operator << (ostream& os, const Authentication& shs) { os << shs; return os; }

//	����������� ����� � �������� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Shoes_Shop
{
public:
	//	�����������
	Shoes_Shop();
	//	����������
	~Shoes_Shop();

	//	���������� � ������
	void PushFront(string art, string name, double price, string make, int size, int count);
	//	���������� � �����
	void PushBack(string art, string name, double price, string maker, int size, int count);

	//	�������� ������ ������
	void pop_front();
	//	�������� ��������� ������
	void pop_back();
	//	�������� �� �������(��)
	void remove_At(const int index);
	//	�������� ���� �������
	void clear();

	//	�������� ���� �������
	void print();
	//	�������� �� ������������� ������� � �������
	void print_as(string art, int size);

	//	������� ���������� �������
	int GetVol() { return Vol; }

private:
	//	��������� �����
	class Shoe
	{
	public:
		//	��������� �� ��������� ������
		Shoe* pNext;
		string Art;
		string Name;
		double Price;
		string Make;
		int Size;
		int Count;

		//	�����������
		Shoe(string art, string name, double price, string make, int size, int count, Shoe* next = nullptr)
		{
			Art = art;
			Name = name;
			Price = price;
			Make = make;
			Size = size;
			Count = count;
			pNext = next;
		}
	};

	//	���������� �������
	int Vol;
	//	��������� �� ������ ������
	Shoe* begin;

	//	������ �� �����
	void ost(fstream& fs);
	//	������ � ����
	void ist(fstream& fs);
};

//	�����������	/	Shoe_Shop


//	���������� ���������� ���������� ����� � ������	/	Shoe_Shop
istream& operator >> (istream& is, Shoes_Shop& shs) { is >> shs; return is; }
ostream& operator << (ostream& os, const Shoes_Shop& shs) { os << shs; return os; }

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Authentication authen;
	Shoes_Shop shoes;
	bool menu = true;
	int choice;
	int access = Entry(authen);

	while (menu == true) {

		//	���� ��������������
		if (access == 1)
		{
			cout << "\n===== ���� �������������� =====" <<
				"\n\t1. ������ � �������� ��������" <<
				"\n\t2. ������ � �������" <<
				"\n\tesc. ����� � �����������" <<
				"\n\t0. �����\n\n";
			cout << "�������� >>>\n\n";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case '0': menu = false; break;
			case 27: access = Entry(authen); break;
			case '1': menu_authentication(authen); break;
			case '2': ShoesProperties_Menu(shoes, access); break;
			}
		}

		//	���� ������������
		if (access == 2)
		{
			cout << "\n===== ���� ������������ =====" <<
				"\n\t1. �����" <<
				"\n\tesc. ����� � �����������" <<
				"\n\t0. �����\n\n";
			cout << "�������� >>>\n\n";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case '0': menu = false; break;
			case 27: access = Entry(authen); break;
			case '1': ShoesProperties_Menu(shoes, access); break;
			}
		}
		if (access == 3)
		{
			cout << "�������: ";
			int RegChoice = EnterNum();
			system("cls");
			if (RegChoice == 1)
			{
				bool flag;
				string login, pass;
				cout << "\n===== ����������� =====" << endl;
				cout << "������� �����: ";
				cin >> login;
				flag = authen.checkUniq(login);
				if (!flag)
				{
					cout << "������� ������: ";
					cin >> pass;
					flag = NEW();
					if (flag == true) authen.PushFront(login, pass);
					access = Entry(authen);
				}
				else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
			}
			else if (RegChoice == 2) access = Entry(authen);
		}
	}
	return 0;
}

//	���� � �������� ������ � ������
int Entry(Authentication& authent)
{
	int access = 0;
	string login, pass;
	cout << "������� \"exit\", ���� ������ �����\n";
	cout << "�����:\t";
	cin >> login;
	if (login == "exit") exit(0);
	cout << "������:\t";
	cin >> pass;
	access = authent.authentication(login, pass);
	return access;
}

//	���� ������ � �������� ��������
void menu_authentication(Authentication& authent)
{
	int choice = 0;
	bool ready, bl;
	string login, pass;
	ready = bl = true;

	while (ready)
	{
		cout << "===== ������ � �������� �������� =====" <<
			"\n\t1. ��������" <<
			"\n\t2. ����������" <<
			"\n\t3. �������������� �� ������" <<
			"\n\t4. ��������" <<
			"\n\tesc. �����\n\n";
		cout << "�������� >>> ";
		choice = _getch();
		system("cls");
		switch (choice)
		{
		case 27: ready = false; break;
		case '1':
			cout << "\n===== �������� ������������� =====" << endl;
			if (authent.GetVol() == 0) cout << "���� �������������!" << endl;
			else authent.printAll();
			break;
		case '2':
			cout << "\n===== ���������� ������������ =====" << endl;
			cout << "������� �����: ";
			cin >> login;
			bl = authent.checkUniq(login);
			if (!bl)
			{
				cout << "������� ������: ";
				cin >> pass;
				bl = NEW();
				if (bl) authent.PushFront(login, pass);
			}
			else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
			break;
		case '3':
			cout << "\n===== �������������� ������������ =====" << endl;
			cout << "������� �����: ";
			cin >> login;
			bl = authent.checkUniq(login);
			if (bl)
			{
				cout << "���������������: "
					<< "\n\t1. ����� � ������"
					<< "\n\t2. �����"
					<< "\n\t3. ������"
					<< "\n\tesc. �����\n\n";
				cout << "�������� >>> ";
				choice = EnterNum();
				switch (choice)
				{
				case 27: break;
				case '1': authent.edit_all(login); break;
				case '2': authent.edit_login(login); break;
				case '3': authent.edit_pass(login); break;
				}
			}
			else cout << "������������ ��� ������� \"" << login << "\" �� ������!" << endl;
			break;
		case '4':
			cout << "\n===== �������� ������������� =====" << endl;
			cout << "\t1. �� ������" <<
				"\n\t2. ���" <<
				"\n\t0. �����\n\n";
			cout << "�������� >>> ";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case 27: break;
			case '1':
				cout << "������� �����: ";
				cin >> login;
				bl = authent.checkUniq(login);
				if (bl)
				{
					authent.printBYlogin(login);
					bl = DEL();
					if (bl) authent.removeBYlogin(login);
				}
				else cout << "������������ ��� ������� \"" << login << "\" �� ������!" << endl;
				break;
			case '2':
				bl = DEL();
				if (bl) authent.clear();
				break;
			}
			break;
		}
	}
}
//	���� ������ � �������
void ShoesProperties_Menu(Shoes_Shop& shoes, int access)
{
	int choice, index, count, size;
	string art, name, maker;
	double price;
	bool ready, bl;

	choice = index = count = size = int();
	ready = bl = true;

	while (ready)
	{
		cout << "===== ������ � ������� =====" <<
			"\n\t1. ��������";
		if (access == 1)
			cout << "\n\t2. ����������" << "\n\t3. ��������";
		cout << "\n\tesc. �����\n\n�������� >>>\n\n";
		choice = _getch();
		system("cls");
		if (access == 2)
		{
			while (choice != '1' && choice != '0' && choice != 27)
			{
				cout << "������ ������ ���� ���\n";
				cout << "===== ������ � ������� =====" <<
					"\n\t1. ��������";
				if (access == 1)
					cout << "\n\t2. ����������" << "\n\t3. ��������";
				cout << "\n\tesc. �����\n\n�������� >>>\n";
				choice = _getch();
				system("cls");
			}
		}

		switch (choice)
		{
		case 27: ready = false; break;
		case '1':
			cout << "\n===== �������� ������ =====" << endl;
			if (shoes.GetVol() == 0) cout << "��� ������!" << endl;
			else
			{
				cout << "\t1. ��� ������" <<
					"\n\t2. �� ������������� ������� � �������" <<
					"\n\tesc. �����\n\n";
				cout << "�������� >>>\n\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case 27: break;
				case '1': shoes.print(); break;
				case '2':
					cout << "�������" <<
						"\n\t1. � (������� �����)"
						"\n\t2. � (������� �����)"
						"\n\t3. � (������� �����)" << endl;
					cout << "�������� >>> ";
					choice = _getch();
					system("cls");
					switch (choice)
					{
					case '1': art = "�"; break;
					case '2': art = "�"; break;
					case '3': art = "�"; break;
					}
					cout << "������� ������: ";
					size = EnterNum();
					shoes.print_as(art, size);
					break;
				}
			}
			break;
		case '2':
			cout << "\n===== ���������� ������ =====" << endl;
			cout << "\t1. � ������\n" << "\t2. � �����\n" << "\tesc. �����\n\n";
			cout << "�������� >>>\n";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case 27: break;
			case '1':
				cout << "�������" <<
					"\n\t1. � (������� �����)"
					"\n\t2. � (������� �����)"
					"\n\t3. � (������� �����)" << endl;
				cout << "�������� >>>\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case '1': art = "�"; break;
				case '2': art = "�"; break;
				case '3': art = "�"; break;
				}
				cout << "������� ������������: ";
				getline(cin, name, '\n');
				getline(cin, name, '\n');
				//cin >> name;
				cout << "������� ����: ";
				price = EnterNumD();
				cout << "������� ������������: ";
				getline(cin, maker, '\n');
				cout << "������� ������: ";
				size = EnterNumD();
				cout << "������� ����������: ";
				count = EnterNum();
				bl = NEW();
				if (bl) shoes.PushFront(art, name, price, maker, size, count);
				break;
			case '2':
				cout << "�������" <<
					"\n\t1. � (������� �����)"
					"\n\t2. � (������� �����)"
					"\n\t3. � (������� �����)" << endl;
				cout << "�������� >>>\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case '1': art = "�"; break;
				case '2': art = "�"; break;
				case '3': art = "�"; break;
				}
				cout << "������� ������������: ";
				getline(cin, name, '\n');
				cout << "������� ����: ";
				price = EnterNumD();
				cout << "������� ������������: ";
				getline(cin, maker, '\n');
				cout << "������� ������: ";
				size = EnterNumD();
				cout << "������� ����������: ";
				count = EnterNum();
				bl = NEW();
				if (bl) shoes.PushBack(art, name, price, maker, size, count);
				break;
			}
			break;
		case 3:
			cout << "\n===== �������� ������ =====" << endl;
			if (shoes.GetVol() == 0) cout << "��� ������!" << endl;
			else
			{
				cout << "\t1. ���\n" << "\t2. �� ��\n" << "\tesc. �����\n\n";
				cout << "�������� >>> ";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case 27: break;
				case '1':
					bl = DEL();
					if (bl) shoes.clear();
					break;
				case '2':
					cout << "������� ��(�� 0 �� " << shoes.GetVol() << "): ";
					cin >> index;
					bl = DEL();
					if (bl) shoes.remove_At(index);
					break;
				}
				break;
			}
			break;
		}
	}
}
Authentication::Authentication()
{
	begin = nullptr;
	Vol = 0;

	FILE_USERS.open(UsersFile, ios::in | ios::app);
	if (!FILE_USERS.is_open()) cout << "������ �������� �����! ������������ �� ���������!" << endl;
	else
	{
		ReadFrom(FILE_USERS);
		if (GetVol() != 0) cout << "������� " << GetVol() << " �������������." << endl << endl;
	}
	FILE_USERS.close();
}
// ����������	/	Authen
Authentication::~Authentication()
{
	FILE_USERS.open(UsersFile, ios::out);
	WriteIn(FILE_USERS);
	FILE_USERS.close();

	clear();
}

//	�������� ������ � ������	/	Authen
int Authentication::authentication(const string login, const string pass)
{
	if (login == AdminLogin && pass == AdminPass) return 1;
	else if (begin != nullptr)
	{
		User* temp = begin;
		while (temp != nullptr)
		{
			if (temp->login == login && temp->Pass == pass) return 2;
			temp = temp->pNext;
		}
	}
	cout << "\n����� ��� ������ ������ �����������!\n��� ������ ������������ �� ����������\n������ ������������������ ?\n1 - ��\n2 - ���\n";
	return 3;
}
//	�������� �� ������������ �����	/	Authen
bool Authentication::checkUniq(const string login)
{
	User* temp = begin;

	while (temp != nullptr)
	{
		if (temp->login == login) return true;
		temp = temp->pNext;
	}
	return false;
}

//	�������� ���� ������	/	Authen
void Authentication::printAll()
{
	User* temp = begin;
	cout << "= = = = = = = = = =" << endl;
	while (temp != nullptr)
	{
		cout << "�����: " << temp->login << endl;
		cout << "������: " << temp->Pass << endl;
		cout << "= = = = = = = = = =" << endl;
		temp = temp->pNext;
	}
}
//	�������� �� ������������� ������	/	Authen
void Authentication::printBYlogin(string login)
{
	User* temp = begin;
	cout << "= = = = = = = = = =" << endl;
	while (temp != nullptr)
	{
		if (temp->login == login)
		{
			cout << "�����: " << temp->login;
			cout << "������: " << temp->Pass;
			cout << "= = = = = = = = = =" << endl;
		}
		temp = temp->pNext;
	}
}

//	����������	/	Authen
void Authentication::PushFront(const string login, const string pass) { begin = new User(login, pass, begin); Vol++; }

//	�������������� ������ � ������	/	Authen
void Authentication::edit_all(const string login)
{
	User* temp = begin;
	string loginnew, pass;
	bool bl, login_new;

	cout << "������� ����� �����: ";
	cin >> loginnew;

	login_new = checkUniq(loginnew);
	if (!login_new)
	{
		cout << "������� ����� ������: ";
		cin >> pass;

		while (temp != nullptr)
		{
			if (temp->login == login)
			{
				bl = EDIT();
				if (bl)
				{
					temp->login = loginnew;
					temp->Pass = pass;
				}
				break;
			}
			temp = temp->pNext;
		}
	}
	else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
}
//	�������������� ������	/	Authen
void Authentication::edit_login(const string login)
{
	User* temp = begin;
	string loginnew, pass;
	bool bl, login_new;

	cout << "������� ����� �����: ";
	cin >> loginnew;

	login_new = checkUniq(loginnew);
	if (!login_new)
	{
		while (temp != nullptr)
		{
			if (temp->login == login)
			{
				bl = EDIT();
				if (bl) temp->login = loginnew;
				break;
			}
			temp = temp->pNext;
		}
	}
	else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
}
//	�������������� ������	/	Authen
void Authentication::edit_pass(const string login)
{
	User* temp = begin;
	string loginnew, pass;
	bool bl;

	cout << "������� ����� ������: ";
	cin >> pass;

	while (temp != nullptr)
	{
		if (temp->login == login)
		{
			bl = EDIT();
			if (bl) temp->Pass = pass;
			break;
		}
		temp = temp->pNext;
	}
}

//	�������� ������ ������	/	Authen
void Authentication::pop_front()
{
	User* temp = begin;
	begin = begin->pNext;
	delete temp;
	Vol--;
}
//	�������� ���� ������	/	Authen
void Authentication::clear()
{
	while (Vol)
	{
		User* temp = begin;
		begin = begin->pNext;
		delete temp;
		Vol--;
	}
}
//	�������� �� ������������� ������	/	Authen
void Authentication::removeBYlogin(const string login)
{
	User* temp = begin;
	int count = 1;

	while (temp != nullptr)
	{
		if (temp->login == login) break;
		count++;
	}

	if (count == 1) pop_front();
	else
	{
		while (temp != nullptr)
		{
			if (temp->login == login)
			{
				User* del = temp->pNext;
				temp->pNext = del->pNext;
				delete del;
				Vol--;
				break;
			}
			temp = temp->pNext;
		}
	}
}

//	������ �� �����	/	Authen
void Authentication::ReadFrom(fstream& fs)
{
	string login, pass;

	while (true)
	{
		fs >> login;
		if (fs.eof()) break;
		fs >> pass;
		PushFront(login, pass);
	}
}
//	������ � �����	/	Authen
void Authentication::WriteIn(fstream& fs)
{
	User* temp = begin;

	while (temp != nullptr)
	{
		fs << temp->login << endl;
		fs << temp->Pass << endl;
		temp = temp->pNext;
	}
}

Shoes_Shop::Shoes_Shop()
{
	begin = nullptr;
	Vol = 0;

	FILE_SHOES.open(ShoesFile, ios::in | ios::app);
	if (!FILE_SHOES.is_open()) { cout << "������ �������� �����! ������ �� ���������!" << endl; }
	else
	{
		ost(FILE_SHOES);
		if (GetVol() != 0) cout << "������� " << GetVol() << " �������." << endl << endl;
	}
	FILE_SHOES.close();
}
//	����������	/	Shoe_Shop
Shoes_Shop::~Shoes_Shop()
{
	FILE_SHOES.open(ShoesFile, ios::out);
	ist(FILE_SHOES);
	FILE_SHOES.close();

	clear();
}

//	���������� � ������	/	Shoe_Shop
void Shoes_Shop::PushFront(string art, string name, double price, string make, int size, int count)
{
	begin = new Shoe(art, name, price, make, size, count, begin);
	Vol++;
}
//	���������� � �����	/	Shoe_Shop
void Shoes_Shop::PushBack(string art, string name, double price, string make, int size, int count)
{
	if (begin == nullptr) begin = new Shoe(art, name, price, make, size, count);
	else
	{
		Shoe* temp = begin;
		while (temp->pNext != nullptr) temp = temp->pNext;
		temp->pNext = new Shoe(art, name, price, make, size, count);
	}
	Vol++;
}

//	�������� ������ ������	/	Shoe_Shop
void Shoes_Shop::pop_front()
{
	Shoe* temp = begin;
	begin = begin->pNext;
	delete temp;
	Vol--;
}
//	�������� ��������� ������	/	Shoe_Shop
void Shoes_Shop::pop_back() { remove_At(Vol); }
//	�������� �� ������������� �������(��)	/	Shoe_Shop
void Shoes_Shop::remove_At(const int index)
{
	if (index == 1) pop_front();
	else
	{
		Shoe* temp = begin;
		for (int i = 1; i <= index; i++) temp = temp->pNext;
		Shoe* del = temp->pNext;
		temp->pNext = del->pNext;
		delete del;
		Vol--;
	}
}
//	�������� ���� �������	/	Shoe_Shop
void Shoes_Shop::clear() { while (Vol) pop_front(); }

//	�������� ���� �������	/	Shoe_Shop
void Shoes_Shop::print()
{
	Shoe* temp = begin;

	cout << "= = = = = = = = = =" << endl;
	for (int i = 1; temp != nullptr; i++)
	{
		cout << "��: " << i << endl;
		cout << "�������: " << temp->Art << endl;
		cout << "������������: " << temp->Name << endl;
		cout << "����: " << temp->Price << endl;
		cout << "������������: " << temp->Make << endl;
		cout << "������: " << temp->Size << endl;
		cout << "���������� ���: " << temp->Count << endl;
		cout << "= = = = = = = = = =" << endl;
		temp = temp->pNext;
	}
}
//	�������� �� ������������� ������� � �������
void Shoes_Shop::print_as(string art, int size)
{
	Shoe* temp = begin;


	for (int i = 1; temp != nullptr; i++)
	{
		if (temp->Art == art && temp->Size == size)
		{
			cout << "��: " << i << endl;
			cout << "�������: " << temp->Art << endl;
			cout << "������������: " << temp->Name << endl;
			cout << "����: " << temp->Price << endl;
			cout << "������������: " << temp->Make << endl;
			cout << "������: " << temp->Size << endl;
			cout << "���������� ���: " << temp->Count << endl;
			cout << "= = = = = = = = = =" << endl;
		}
		temp = temp->pNext;
	}
}

//	������ �� �����	/	Shoe_Shop
void Shoes_Shop::ost(fstream& fs)
{
	int count, size;
	string art, name, make;
	double price;

	while (true)
	{
		fs >> art;
		if (fs.eof()) break;
		fs >> name;
		fs >> price;
		fs >> make;
		fs >> size;
		fs >> count;
		PushBack(art, name, price, make, size, count);
	}
}
//	������ � ����	/	Shoe_Shop
void Shoes_Shop::ist(fstream& fs)
{
	Shoe* temp = begin;

	while (temp != nullptr)
	{
		fs << temp->Art << endl;
		fs << temp->Name << endl;
		fs << temp->Price << endl;
		fs << temp->Make << endl;
		fs << temp->Size << endl;
		fs << temp->Count << endl;
		temp = temp->pNext;
	}
}