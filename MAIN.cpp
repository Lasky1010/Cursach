#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include"validation.h"


using namespace std;

class Authentication;
const string users_path = "UsersBase.txt";
fstream file_auth;
const string shoes_path = "ShoesBase.txt";
fstream file_shoes;
class Shoes_Shop;


int Entry(Authentication& authent);
//	���� ��� ������ � ��������������
void menu_authentication(Authentication& authen);
//	���� ��� ������ � �������
void ShoesProperties_Menu(Shoes_Shop& shoes, int access);

class Authentication
{
public:
	Authentication();
	~Authentication();
	int authentication(const string login, const string pass);
	bool checkUniq(const string login);
	void print();
	void print_login(string login);
	int  GetAmount();
	void push_front(const string login, const string pass);
	void Edit_All(const string login);
	void edit_login(const string login);
	void edit_pass(const string login);
	void delete_first();
	void Clear();
	void remove_At(const string login);
	void WriteIn(fstream& fs);
	void ReadFrom(fstream& fs);
private:
	class User
	{
	public:
		User* pNext;
		string login;
		string Pass;
		User(string login, string pass, User* next = nullptr)
		{
			this->login = login;
			Pass = pass;
			pNext = next;
		}
	};
	User* begin;
	int Amount;

	string AdminLogin = "admin";
	string AdminPass = "admin";
};

class Shoes_Shop
{
public:
	Shoes_Shop();
	~Shoes_Shop();

	//	���������� � ���
	void PushFront(string art, string name, double price, string make, int size, int count);
	//	���������� � �����
	void PushBack(string art, string name, double price, string make, int size, int count);

	void delete_first();
	void pop_back();
	void remove_At(const int index);
	void clear();

	void print();
	void PrintShoesByArt(string art, double size);
	void PrintShoesByBrand(string Brand);

	int GetAmount();

private:
	class Shoes
	{
	public:
		Shoes* pNext;
		string Art;
		string Name;
		double Price;
		string Make;
		int Size;
		int Count;
		Shoes(string art, string name, double price, string make, int size, int count, Shoes* next);
	};

	int Amount;
	Shoes* begin;

	//	������ �� �����
	void ReadFrom(fstream& fs);
	//	������ � ����
	void WriteIn(fstream& fs);
};

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
			cout << "��������...\n\n";
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
			cout << "��������...\n\n";
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
			int RegChoice = _getch();
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
					if (flag == true) authen.push_front(login, pass);
					access = Entry(authen);
				}
				else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
			}
			else if (RegChoice == 2) access = Entry(authen);
		}
	}
	return 0;
}



Shoes_Shop::Shoes::Shoes(string art, string name, double price, string make, int size, int count, Shoes* next=nullptr)
{
	Art = art;
	Name = name;
	Price = price;
	Make = make;
	Size = size;
	Count = count;
	pNext = next ;
}
Shoes_Shop::Shoes_Shop()
{
	begin = nullptr;
	Amount = 0;

	file_shoes.open(shoes_path, ios::in | ios::app);
	if (!file_shoes.is_open()) { cout << "������ �������� �����! ������ �� ���������!" << endl; }
	else
	{
		ReadFrom(file_shoes);
		if (GetAmount() != 0) cout << "������� " << GetAmount() << " �������." << endl << endl;
	}
	file_shoes.close();
}
Shoes_Shop::~Shoes_Shop()
{
	file_shoes.open(shoes_path, ios::out);
	WriteIn(file_shoes);
	file_shoes.close();

	clear();
}


void Shoes_Shop::PushFront(string art, string name, double price, string make, int size, int count)
{
	begin = new Shoes(art, name, price, make, size, count, begin);
	Amount++;
}

void Shoes_Shop::PushBack(string art, string name, double price, string make, int size, int count)
{
	if (begin == nullptr) begin = new Shoes(art, name, price, make, size, count);
	else
	{
		Shoes* temp = begin;
		while (temp->pNext != nullptr) temp = temp->pNext;
		temp->pNext = new Shoes(art, name, price, make, size, count);
	}
	Amount++;
}
void Shoes_Shop::delete_first()
{
	Shoes* temp = begin;
	begin = begin->pNext;
	delete temp;
	Amount--;
}

void Shoes_Shop::pop_back() { remove_At(Amount); }

void Shoes_Shop::remove_At(const int index)
{
	if (index == 1) delete_first();
	else
	{
		Shoes* temp = begin;
		for (int i = 1; i <= index; i++) temp = temp->pNext;
		Shoes* del = temp->pNext;
		temp->pNext = del->pNext;
		delete del;
		Amount--;
	}
}

void Shoes_Shop::clear() { while (Amount) delete_first(); }

void Shoes_Shop::print()
{
	Shoes* temp = begin;

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
// ����� ����� �� ��������
void Shoes_Shop::PrintShoesByArt(string art, double size)
{
	Shoes* temp = begin;
	int a = int();

	for (int i = 1; temp != nullptr; i++)
	{
		if (temp->Art == art && temp->Size == size)
		{
			if (a == 0) { cout << "= = = = = = = = = =" << endl; a++; }
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
// ����� ����� �� ������
void Shoes_Shop::PrintShoesByBrand(string brand)
{
	Shoes* temp = begin;
	int a = 0;

	for (int i = 1; temp != nullptr; i++)
	{
		if (temp->Make == brand)
		{
			if (a == 0) { cout << "= = = = = = = = = =" << endl; a++; }
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

// ������ �� �����	/	Shoe_Shop
void Shoes_Shop::ReadFrom(fstream& fs)
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
// ������ � ����	/	Shoe_Shop
void Shoes_Shop::WriteIn(fstream& fs)
{
	Shoes* temp = begin;
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




//	�������� ������ � ������
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




//	�������� �� ������������ �����
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
// �����
void Authentication::print()
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
// ����� �� ������
void Authentication::print_login(string login)
{
	User* temp = begin;
	cout << "= = = = = = = = = =" << endl;
	while (temp != nullptr)
	{
		if (temp->login == login)
		{
			cout << "�����: " << temp->login;
			cout << "\n������: " << temp->Pass;
			cout << "\n= = = = = = = = = =\n" << endl;
		}
		temp = temp->pNext;
	}
}
// ���������� ������ ������������
void Authentication::push_front(const string login, const string pass) { begin = new User(login, pass, begin); Amount++; }

// �������������� � ������, � ������
void Authentication::Edit_All(const string login)
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
// ���. ������ ������
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
// ���. ������ ������
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
// �������� �������
void Authentication::delete_first()
{
	User* temp = begin;
	begin = begin->pNext;
	delete temp;
	Amount--;
}
//
void Authentication::Clear()
{
	while (Amount)
	{
		User* temp = begin;
		begin = begin->pNext;
		delete temp;
		Amount--;
	}
}

void Authentication::remove_At(const string login)
{

	User* del = begin;
	User* temp = del->pNext;
	while (temp != NULL) {
		if (temp->login == login) {
			del->pNext = temp->pNext;
			delete temp;
			temp = del->pNext;
		}
		else {
			del = temp;
			temp = temp->pNext;
		}
	}
	if (begin->login == login) {
		temp = begin;
		begin = begin->pNext;
		delete temp;
	}

}

void Authentication::ReadFrom(fstream& fs)
{
	string login, pass;

	while (true)
	{
		fs >> login;
		if (fs.eof()) break;
		fs >> pass;
		push_front(login, pass);
	}
}
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



Authentication::Authentication()
{
	begin = nullptr;
	Amount = 0;

	file_auth.open(users_path, ios::in | ios::app);
	if (!file_auth.is_open()) cout << "������ �������� �����! ������������ �� ���������!" << endl;
	else
	{
		ReadFrom(file_auth);
		if (GetAmount() != 0) cout << "������� " << GetAmount() << " �������������." << endl << endl;
	}
	file_auth.close();
}
Authentication::~Authentication()
{
	file_auth.open(users_path, ios::out);
	WriteIn(file_auth);
	file_auth.close();

	Clear();
}


int Authentication::GetAmount() { return Amount; }
int Shoes_Shop::GetAmount() { return Amount; }


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

void menu_authentication(Authentication& authen)
{
	int choice = 0;
	bool ready, flag;
	string login, pass;
	ready = flag = true;

	while (ready)
	{
		cout << "===== ������ � �������� �������� =====" <<
			"\n\t1. ��������" <<
			"\n\t2. ����������" <<
			"\n\t3. �������������� �� ������" <<
			"\n\t4. ��������" <<
			"\n\tesc. �����\n\n";
		cout << "��������...\n";
		choice = _getch();
		system("cls");
		switch (choice)
		{
		case 27: ready = false; break;
		case '1':
			cout << "\n===== �������� ������������� =====" << endl;
			if (authen.GetAmount() == 0) cout << "���� �������������!" << endl;
			else authen.print();
			break;
		case '2':
			cout << "\n===== ���������� ������������ =====" << endl;
			cout << "������� �����: ";
			cin >> login;
			flag = authen.checkUniq(login);
			if (!flag)
			{
				cout << "������� ������: ";
				cin >> pass;
				flag = NEW();
				if (flag) authen.push_front(login, pass);
			}
			else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
			break;
		case '3':
			cout << "\n===== �������������� ������������ =====" << endl;
			cout << "������� �����: ";
			cin >> login;
			flag = authen.checkUniq(login);
			if (flag)
			{
				cout << "���������������: "
					<< "\n\t1. ����� � ������"
					<< "\n\t2. �����"
					<< "\n\t3. ������"
					<< "\n\tesc. �����\n\n";
				cout << "��������...\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case 0: break;
				case 1: authen.Edit_All(login); break;
				case 2: authen.edit_login(login); break;
				case 3: authen.edit_pass(login); break;
				}
			}
			else cout << "������������ ��� ������� \"" << login << "\" �� ������!" << endl;
			break;
		case '4':
			cout << "\n===== �������� ������������� =====" << endl;
			cout << "\t1. �� ������" <<
				"\n\t2. ���" <<
				"\n\tesc. �����\n\n";
			cout << "��������...\n";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case 27: break;
			case '1':
				cout << "������� �����: ";
				cin >> login;
				flag = authen.checkUniq(login);
				if (flag)
				{
					authen.print_login(login);
					flag = DEL();
					if (flag) authen.remove_At(login);
				}
				else cout << "������������ ��� ������� \"" << login << "\" �� ������!" << endl;
				break;
			case '2':
				flag = DEL();
				if (flag) authen.Clear();
				break;
			}
			break;
		}
	}
}

//	���� ������ � �������
void ShoesProperties_Menu(Shoes_Shop& shoes, int access)
{
	int choice, index, count;
	string art, name, maker;
	double price, size;
	bool ready, bl;

	choice = index = count = int(0);
	ready = bl = true;

	while (ready)
	{

		cout << "===== ������ � ������� =====" <<
			"\n\t1. ��������";
		if (access == 1)
			cout << "\n\t2. ����������" << "\n\t3. ��������";
		cout << "\n\tesc. �����\n\n��������...\n\n";
		choice = _getch();
		system("cls");

		if (access == 2)
		{
			while (choice != '1' && choice != '0' && choice !=27)
			{
				cout << "������ ������ ���� ���\n";
				cout << "===== ������ � ������� =====" <<
					"\n\t1. ��������";
				if (access == 1)
					cout << "\n\t2. ����������" << "\n\t3. ��������";
				cout << "\n\tesc. �����\n\n��������...\n";

				choice = _getch();
				system("cls");
			}
		}
		switch (choice)
		{
		case 27:
			ready = false;
			break;
		case '1':
			cout << "\n===== �������� ������ =====" << endl;
			if (shoes.GetAmount() == 0) cout << "��� ������!" << endl;
			else
			{
				cout << "\t1. ��� ������" <<
					"\n\t2. �� ������������� ������� � �������" <<
					"\n\t3. �� ������������� ������" <<
					"\n\tesc. �����\n\n";
				cout << "��������...\n\n";
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
					cout << "��������...\n";
					choice = _getch();
					system("cls");
					switch (choice)
					{
					case '1': art = "�"; break;
					case '2': art = "�"; break;
					case '3': art = "�"; break;
					}
					cout << "������� ������: ";
					size = EnterNumD();
					shoes.PrintShoesByArt(art, size);
					break;
				case '3':
					cout << "������� �������� �����: ";
					getline(cin, maker, '\n');
					shoes.PrintShoesByBrand(maker);
					break;
				}
			}
			break;
		case '2':
			cout << "\n===== ���������� ������ =====" << endl;
			cout << "\t1. � ������\n" << "\t2. � �����\n" << "\tesc. �����\n\n";
			cout << "��������...\n";
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
				cout << "��������...\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case '1': art = "�"; break;
				case '2': art = "�"; break;
				case '3': art = "�"; break;
				}
				cout << "������� ������������: ";
				//getline(cin, name, '\n');
				cin >> name;
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
				cout << "��������...\n";
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
		case '3':
			cout << "\n===== �������� ������ =====" << endl;
			if (shoes.GetAmount() == 0) cout << "��� ������!" << endl;
			else
			{
				cout << "\t1. ���\n" << "\t2. �� ��\n" << "\tesc. �����\n\n";
				cout << "��������...\n";
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
					cout << "������� ��(�� 0 �� " << shoes.GetAmount() << "): ";
					cin >> index;
					bl = DEL();
					if (bl) shoes.remove_At(index);
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}
