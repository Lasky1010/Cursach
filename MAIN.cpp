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
//	Меню для работы с пользователями
void menu_authentication(Authentication& authen);
//	Меню для работы с данными
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

	//	Добавление в нач
	void PushFront(string art, string name, double price, string make, int size, int count);
	//	Добавление в конец
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

	//	Чтение из файла
	void ReadFrom(fstream& fs);
	//	Запись в файл
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

		//	Меню Администратора
		if (access == 1)
		{
			cout << "\n===== Меню Администратора =====" <<
				"\n\t1. Работа с учетными записями" <<
				"\n\t2. Работа с данными" <<
				"\n\tesc. Назад к авторизации" <<
				"\n\t0. Выход\n\n";
			cout << "Выберите...\n\n";
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

		//	Меню Пользователя
		if (access == 2)
		{
			cout << "\n===== Меню Пользователя =====" <<
				"\n\t1. Поиск" <<
				"\n\tesc. Назад к авторизации" <<
				"\n\t0. Выход\n\n";
			cout << "Выберите...\n\n";
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
			cout << "Введите: ";
			int RegChoice = _getch();
			system("cls");
			if (RegChoice == 1)
			{
				bool flag;
				string login, pass;
				cout << "\n===== Регистрация =====" << endl;
				cout << "Введите логин: ";
				cin >> login;
				flag = authen.checkUniq(login);
				if (!flag)
				{
					cout << "Введите пароль: ";
					cin >> pass;
					flag = NEW();
					if (flag == true) authen.push_front(login, pass);
					access = Entry(authen);
				}
				else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
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
	if (!file_shoes.is_open()) { cout << "Ошибка открытия файла! Данные не загружены!" << endl; }
	else
	{
		ReadFrom(file_shoes);
		if (GetAmount() != 0) cout << "Найдено " << GetAmount() << " записей." << endl << endl;
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
		cout << "ИД: " << i << endl;
		cout << "Артикул: " << temp->Art << endl;
		cout << "Наименование: " << temp->Name << endl;
		cout << "Цена: " << temp->Price << endl;
		cout << "Изготовитель: " << temp->Make << endl;
		cout << "Размер: " << temp->Size << endl;
		cout << "Количество пар: " << temp->Count << endl;
		cout << "= = = = = = = = = =" << endl;
		temp = temp->pNext;
	}
}
// Вывод обуви по артикулу
void Shoes_Shop::PrintShoesByArt(string art, double size)
{
	Shoes* temp = begin;
	int a = int();

	for (int i = 1; temp != nullptr; i++)
	{
		if (temp->Art == art && temp->Size == size)
		{
			if (a == 0) { cout << "= = = = = = = = = =" << endl; a++; }
			cout << "ИД: " << i << endl;
			cout << "Артикул: " << temp->Art << endl;
			cout << "Наименование: " << temp->Name << endl;
			cout << "Цена: " << temp->Price << endl;
			cout << "Изготовитель: " << temp->Make << endl;
			cout << "Размер: " << temp->Size << endl;
			cout << "Количество пар: " << temp->Count << endl;
			cout << "= = = = = = = = = =" << endl;
		}
		temp = temp->pNext;
	}
}
// Вывод обуви по бренду
void Shoes_Shop::PrintShoesByBrand(string brand)
{
	Shoes* temp = begin;
	int a = 0;

	for (int i = 1; temp != nullptr; i++)
	{
		if (temp->Make == brand)
		{
			if (a == 0) { cout << "= = = = = = = = = =" << endl; a++; }
			cout << "ИД: " << i << endl;
			cout << "Артикул: " << temp->Art << endl;
			cout << "Наименование: " << temp->Name << endl;
			cout << "Цена: " << temp->Price << endl;
			cout << "Изготовитель: " << temp->Make << endl;
			cout << "Размер: " << temp->Size << endl;
			cout << "Количество пар: " << temp->Count << endl;
			cout << "= = = = = = = = = =" << endl;
		}
		temp = temp->pNext;
	}
}

// Чтение из файла	/	Shoe_Shop
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
// Запись в файл	/	Shoe_Shop
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




//	Проверка логина и пароля
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
	cout << "\nЛогин или пароль введен неправильно!\nИли иакого пользователя не существует\nХотите зарегестрироваться ?\n1 - Да\n2 - Нет\n";
	return 3;

}




//	Проверка на существующий логин
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
// Вывод
void Authentication::print()
{
	User* temp = begin;
	cout << "= = = = = = = = = =" << endl;
	while (temp != nullptr)
	{
		cout << "Логин: " << temp->login << endl;
		cout << "Пароль: " << temp->Pass << endl;
		cout << "= = = = = = = = = =" << endl;
		temp = temp->pNext;
	}
}
// Вывод по логину
void Authentication::print_login(string login)
{
	User* temp = begin;
	cout << "= = = = = = = = = =" << endl;
	while (temp != nullptr)
	{
		if (temp->login == login)
		{
			cout << "Логин: " << temp->login;
			cout << "\nПароль: " << temp->Pass;
			cout << "\n= = = = = = = = = =\n" << endl;
		}
		temp = temp->pNext;
	}
}
// Добавление нового пользователя
void Authentication::push_front(const string login, const string pass) { begin = new User(login, pass, begin); Amount++; }

// Редактирование и логина, и пароля
void Authentication::Edit_All(const string login)
{
	User* temp = begin;
	string loginnew, pass;
	bool bl, login_new;

	cout << "Введите новый логин: ";
	cin >> loginnew;

	login_new = checkUniq(loginnew);
	if (!login_new)
	{
		cout << "Введите новый пароль: ";
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
	else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
}
// Ред. только логина
void Authentication::edit_login(const string login)
{
	User* temp = begin;
	string loginnew, pass;
	bool bl, login_new;

	cout << "Введите новый логин: ";
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
	else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
}
// Ред. только пароля
void Authentication::edit_pass(const string login)
{
	User* temp = begin;
	string loginnew, pass;
	bool bl;

	cout << "Введите новый пароль: ";
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
// Удаление первого
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
	if (!file_auth.is_open()) cout << "Ошибка открытия файла! Пользователи не загружены!" << endl;
	else
	{
		ReadFrom(file_auth);
		if (GetAmount() != 0) cout << "Найдено " << GetAmount() << " пользователей." << endl << endl;
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


//	Ввод и проверка логина и пароля
int Entry(Authentication& authent)
{
	int access = 0;
	string login, pass;
	cout << "Введите \"exit\", если хотите выйти\n";
	cout << "Логин:\t";
	cin >> login;
	if (login == "exit") exit(0);
	cout << "Пароль:\t";
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
		cout << "===== Работа с учетными записями =====" <<
			"\n\t1. Просмотр" <<
			"\n\t2. Добавление" <<
			"\n\t3. Редактирование по логину" <<
			"\n\t4. Удаление" <<
			"\n\tesc. Назад\n\n";
		cout << "Выберите...\n";
		choice = _getch();
		system("cls");
		switch (choice)
		{
		case 27: ready = false; break;
		case '1':
			cout << "\n===== Просмотр пользователей =====" << endl;
			if (authen.GetAmount() == 0) cout << "Нету пользователей!" << endl;
			else authen.print();
			break;
		case '2':
			cout << "\n===== Добавление пользователя =====" << endl;
			cout << "Введите логин: ";
			cin >> login;
			flag = authen.checkUniq(login);
			if (!flag)
			{
				cout << "Введите пароль: ";
				cin >> pass;
				flag = NEW();
				if (flag) authen.push_front(login, pass);
			}
			else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
			break;
		case '3':
			cout << "\n===== Редактирование пользователя =====" << endl;
			cout << "Введите логин: ";
			cin >> login;
			flag = authen.checkUniq(login);
			if (flag)
			{
				cout << "Отредактировать: "
					<< "\n\t1. Логин и пароль"
					<< "\n\t2. Логин"
					<< "\n\t3. Пароль"
					<< "\n\tesc. Назад\n\n";
				cout << "Выберите...\n";
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
			else cout << "Пользователь под логином \"" << login << "\" не найден!" << endl;
			break;
		case '4':
			cout << "\n===== Удаление пользователей =====" << endl;
			cout << "\t1. По логину" <<
				"\n\t2. Все" <<
				"\n\tesc. Назад\n\n";
			cout << "Выберите...\n";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case 27: break;
			case '1':
				cout << "Введите логин: ";
				cin >> login;
				flag = authen.checkUniq(login);
				if (flag)
				{
					authen.print_login(login);
					flag = DEL();
					if (flag) authen.remove_At(login);
				}
				else cout << "Пользователь под логином \"" << login << "\" не найден!" << endl;
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

//	Меню работы с данными
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

		cout << "===== Работа с данными =====" <<
			"\n\t1. Просмотр";
		if (access == 1)
			cout << "\n\t2. Добавление" << "\n\t3. Удаление";
		cout << "\n\tesc. Назад\n\nВыберите...\n\n";
		choice = _getch();
		system("cls");

		if (access == 2)
		{
			while (choice != '1' && choice != '0' && choice !=27)
			{
				cout << "Такого пункта меню нет\n";
				cout << "===== Работа с данными =====" <<
					"\n\t1. Просмотр";
				if (access == 1)
					cout << "\n\t2. Добавление" << "\n\t3. Удаление";
				cout << "\n\tesc. Назад\n\nВыберите...\n";

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
			cout << "\n===== Просмотр данных =====" << endl;
			if (shoes.GetAmount() == 0) cout << "Нет данных!" << endl;
			else
			{
				cout << "\t1. Все данные" <<
					"\n\t2. По определенному артиклу и размеру" <<
					"\n\t3. По определенному бренду" <<
					"\n\tesc. Назад\n\n";
				cout << "Выберите...\n\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case 27: break;
				case '1': shoes.print(); break;
				case '2':
					cout << "Артикул" <<
						"\n\t1. Ж (женская обувь)"
						"\n\t2. М (мужская обувь)"
						"\n\t3. Д (детская обувь)" << endl;
					cout << "Выберите...\n";
					choice = _getch();
					system("cls");
					switch (choice)
					{
					case '1': art = "Ж"; break;
					case '2': art = "М"; break;
					case '3': art = "Д"; break;
					}
					cout << "Введите размер: ";
					size = EnterNumD();
					shoes.PrintShoesByArt(art, size);
					break;
				case '3':
					cout << "Введите желаемый бренд: ";
					getline(cin, maker, '\n');
					shoes.PrintShoesByBrand(maker);
					break;
				}
			}
			break;
		case '2':
			cout << "\n===== Добавление данных =====" << endl;
			cout << "\t1. В начало\n" << "\t2. В конец\n" << "\tesc. Назад\n\n";
			cout << "Выберите...\n";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case 27: break;
			case '1':
				cout << "Артикул" <<
					"\n\t1. Ж (женская обувь)"
					"\n\t2. М (мужская обувь)"
					"\n\t3. Д (детская обувь)" << endl;
				cout << "Выберите...\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case '1': art = "Ж"; break;
				case '2': art = "М"; break;
				case '3': art = "Д"; break;
				}
				cout << "Введите наименование: ";
				//getline(cin, name, '\n');
				cin >> name;
				cout << "Введите цену: ";
				price = EnterNumD();
				cout << "Введите изготовителя: ";
				getline(cin, maker, '\n');
				cout << "Введите размер: ";
				size = EnterNumD();
				cout << "Введите количество: ";
				count = EnterNum();
				bl = NEW();
				if (bl) shoes.PushFront(art, name, price, maker, size, count);
				break;
			case '2':
				cout << "Артикул" <<
					"\n\t1. Ж (женская обувь)"
					"\n\t2. М (мужская обувь)"
					"\n\t3. Д (детская обувь)" << endl;
				cout << "Выберите...\n";
				choice = _getch();
				system("cls");
				switch (choice)
				{
				case '1': art = "Ж"; break;
				case '2': art = "М"; break;
				case '3': art = "Д"; break;
				}
				cout << "Введите наименование: ";
				getline(cin, name, '\n');
				cout << "Введите цену: ";
				price = EnterNumD();
				cout << "Введите изготовителя: ";
				getline(cin, maker, '\n');
				cout << "Введите размер: ";
				size = EnterNumD();
				cout << "Введите количество: ";
				count = EnterNum();
				bl = NEW();
				if (bl) shoes.PushBack(art, name, price, maker, size, count);
				break;
			}
			break;
		case '3':
			cout << "\n===== Удаление данных =====" << endl;
			if (shoes.GetAmount() == 0) cout << "Нет данных!" << endl;
			else
			{
				cout << "\t1. Все\n" << "\t2. По ИД\n" << "\tesc. Назад\n\n";
				cout << "Выберите...\n";
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
					cout << "Введите ИД(от 0 до " << shoes.GetAmount() << "): ";
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
