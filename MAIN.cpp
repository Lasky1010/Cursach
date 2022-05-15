#include <iostream>
#include <Windows.h>
#include <fstream>
#include<conio.h>
#include<string>
#include"validation.h"
using namespace std;

//	Переменные для работы с файлом
fstream FILE_USERS;
fstream FILE_SHOES;

//	Классы
class Authentication;
class Shoes_Shop;


//	Ввод и проверка логина и пароля
int Entry(Authentication& authent);

//	Меню для работы с пользователями
void menu_authentication(Authentication& authent);
//	Меню для работы с данными
void ShoesProperties_Menu(Shoes_Shop& ss, int access);

//	Название файлов
const string UsersFile = "Authentication.txt";
const string ShoesFile = "Shoes.txt";



//	Аутентификация !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Authentication
{
public:
	//	Конструктор
	Authentication();
	//	Деструктор
	~Authentication();

	//	Аутентификация
	int authentication(const string login, const string pass);
	//	Проверка на уникальность логина
	bool checkUniq(const string login);

	//	Просмотр всех пользователей
	void printAll();
	//	Просмотр по определенному логину
	void printBYlogin(string login);
	//	Возврат количество пользователей
	int GetVol() { return Vol; }

	//	Добавление
	void PushFront(const string login, const string pass);

	//	Редактирование логина и пароля
	void edit_all(const string login);
	//	Редактирование логина
	void edit_login(const string login);
	//	Редактирование пароля
	void edit_pass(const string login);

	//	Удаление первого пользователя
	void pop_front();
	//	Удаление всех пользователей
	void clear();
	//	Удаление по логну
	void removeBYlogin(const string login);

private:
	//	Вложенный класс	/	пользователь
	class User
	{
	public:
		//	Указатель на следующую запись
		User* pNext;
		//	Логин
		string login;
		//	Пароль
		string Pass;

		//	Конструктор
		User(string login, string pass, User* next = nullptr)
		{
			this->login = login;
			Pass = pass;
			pNext = next;
		}
	};

	//	Указатель на первую запись
	User* begin;
	//	Количество пользователей
	int Vol;

	//	Чтение из файла
	void ReadFrom(fstream& fs);
	//	Запись в файл
	void WriteIn(fstream& fs);

	//	логин и пароль Администратора
	string AdminLogin = "admin";
	string AdminPass = "admin";
};

//	Конструктор	/	Authen

//	Перегрузка операторов потокового ввод/вывод
istream& operator >> (istream& is, Authentication& shs) { is >> shs; return is; }
ostream& operator << (ostream& os, const Authentication& shs) { os << shs; return os; }

//	Ассортимент обуви в магазине !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Shoes_Shop
{
public:
	//	Конструктор
	Shoes_Shop();
	//	Деструктор
	~Shoes_Shop();

	//	Добавление в начало
	void PushFront(string art, string name, double price, string make, int size, int count);
	//	Добавление в конец
	void PushBack(string art, string name, double price, string maker, int size, int count);

	//	Удаление первой записи
	void pop_front();
	//	Удаление последней записи
	void pop_back();
	//	Удаление по индексу(ИД)
	void remove_At(const int index);
	//	Удаление всех записей
	void clear();

	//	Просмотр всех записей
	void print();
	//	Просмотр по определенному артиклу и размеру
	void print_as(string art, int size);

	//	Возврат количество записей
	int GetVol() { return Vol; }

private:
	//	Вложенный класс
	class Shoe
	{
	public:
		//	Указатель на следующую запись
		Shoe* pNext;
		string Art;
		string Name;
		double Price;
		string Make;
		int Size;
		int Count;

		//	Конструктор
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

	//	Количество записей
	int Vol;
	//	Указатель на первую запись
	Shoe* begin;

	//	Чтение из файла
	void ost(fstream& fs);
	//	Запись в файл
	void ist(fstream& fs);
};

//	Конструктор	/	Shoe_Shop


//	Перегрузка операторов потокового ввода и вывода	/	Shoe_Shop
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

		//	Меню Администратора
		if (access == 1)
		{
			cout << "\n===== Меню Администратора =====" <<
				"\n\t1. Работа с учетными записями" <<
				"\n\t2. Работа с данными" <<
				"\n\tesc. Назад к авторизации" <<
				"\n\t0. Выход\n\n";
			cout << "Выберите >>>\n\n";
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
			cout << "Выберите >>>\n\n";
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
			int RegChoice = EnterNum();
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
					if (flag == true) authen.PushFront(login, pass);
					access = Entry(authen);
				}
				else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
			}
			else if (RegChoice == 2) access = Entry(authen);
		}
	}
	return 0;
}

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

//	Меню работы с учетными записями
void menu_authentication(Authentication& authent)
{
	int choice = 0;
	bool ready, bl;
	string login, pass;
	ready = bl = true;

	while (ready)
	{
		cout << "===== Работа с учетными записями =====" <<
			"\n\t1. Просмотр" <<
			"\n\t2. Добавление" <<
			"\n\t3. Редактирование по логину" <<
			"\n\t4. Удаление" <<
			"\n\tesc. Назад\n\n";
		cout << "Выберите >>> ";
		choice = _getch();
		system("cls");
		switch (choice)
		{
		case 27: ready = false; break;
		case '1':
			cout << "\n===== Просмотр пользователей =====" << endl;
			if (authent.GetVol() == 0) cout << "Нету пользователей!" << endl;
			else authent.printAll();
			break;
		case '2':
			cout << "\n===== Добавление пользователя =====" << endl;
			cout << "Введите логин: ";
			cin >> login;
			bl = authent.checkUniq(login);
			if (!bl)
			{
				cout << "Введите пароль: ";
				cin >> pass;
				bl = NEW();
				if (bl) authent.PushFront(login, pass);
			}
			else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
			break;
		case '3':
			cout << "\n===== Редактирование пользователя =====" << endl;
			cout << "Введите логин: ";
			cin >> login;
			bl = authent.checkUniq(login);
			if (bl)
			{
				cout << "Отредактировать: "
					<< "\n\t1. Логин и пароль"
					<< "\n\t2. Логин"
					<< "\n\t3. Пароль"
					<< "\n\tesc. Назад\n\n";
				cout << "Выберите >>> ";
				choice = EnterNum();
				switch (choice)
				{
				case 27: break;
				case '1': authent.edit_all(login); break;
				case '2': authent.edit_login(login); break;
				case '3': authent.edit_pass(login); break;
				}
			}
			else cout << "Пользователь под логином \"" << login << "\" не найден!" << endl;
			break;
		case '4':
			cout << "\n===== Удаление пользователей =====" << endl;
			cout << "\t1. По логину" <<
				"\n\t2. Все" <<
				"\n\t0. Назад\n\n";
			cout << "Выберите >>> ";
			choice = _getch();
			system("cls");
			switch (choice)
			{
			case 27: break;
			case '1':
				cout << "Введите логин: ";
				cin >> login;
				bl = authent.checkUniq(login);
				if (bl)
				{
					authent.printBYlogin(login);
					bl = DEL();
					if (bl) authent.removeBYlogin(login);
				}
				else cout << "Пользователь под логином \"" << login << "\" не найден!" << endl;
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
//	Меню работы с данными
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
		cout << "===== Работа с данными =====" <<
			"\n\t1. Просмотр";
		if (access == 1)
			cout << "\n\t2. Добавление" << "\n\t3. Удаление";
		cout << "\n\tesc. Назад\n\nВыберите >>>\n\n";
		choice = _getch();
		system("cls");
		if (access == 2)
		{
			while (choice != '1' && choice != '0' && choice != 27)
			{
				cout << "Такого пункта меню нет\n";
				cout << "===== Работа с данными =====" <<
					"\n\t1. Просмотр";
				if (access == 1)
					cout << "\n\t2. Добавление" << "\n\t3. Удаление";
				cout << "\n\tesc. Назад\n\nВыберите >>>\n";
				choice = _getch();
				system("cls");
			}
		}

		switch (choice)
		{
		case 27: ready = false; break;
		case '1':
			cout << "\n===== Просмотр данных =====" << endl;
			if (shoes.GetVol() == 0) cout << "Нет данных!" << endl;
			else
			{
				cout << "\t1. Все данные" <<
					"\n\t2. По определенному артиклу и размеру" <<
					"\n\tesc. Назад\n\n";
				cout << "Выберите >>>\n\n";
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
					cout << "Выберите >>> ";
					choice = _getch();
					system("cls");
					switch (choice)
					{
					case '1': art = "Ж"; break;
					case '2': art = "М"; break;
					case '3': art = "Д"; break;
					}
					cout << "Введите размер: ";
					size = EnterNum();
					shoes.print_as(art, size);
					break;
				}
			}
			break;
		case '2':
			cout << "\n===== Добавление данных =====" << endl;
			cout << "\t1. В начало\n" << "\t2. В конец\n" << "\tesc. Назад\n\n";
			cout << "Выберите >>>\n";
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
				cout << "Выберите >>>\n";
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
				getline(cin, name, '\n');
				//cin >> name;
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
				cout << "Выберите >>>\n";
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
		case 3:
			cout << "\n===== Удаление данных =====" << endl;
			if (shoes.GetVol() == 0) cout << "Нет данных!" << endl;
			else
			{
				cout << "\t1. Все\n" << "\t2. По ИД\n" << "\tesc. Назад\n\n";
				cout << "Выберите >>> ";
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
					cout << "Введите ИД(от 0 до " << shoes.GetVol() << "): ";
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
	if (!FILE_USERS.is_open()) cout << "Ошибка открытия файла! Пользователи не загружены!" << endl;
	else
	{
		ReadFrom(FILE_USERS);
		if (GetVol() != 0) cout << "Найдено " << GetVol() << " пользователей." << endl << endl;
	}
	FILE_USERS.close();
}
// Деструктор	/	Authen
Authentication::~Authentication()
{
	FILE_USERS.open(UsersFile, ios::out);
	WriteIn(FILE_USERS);
	FILE_USERS.close();

	clear();
}

//	Проверка логина и пароля	/	Authen
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
//	Проверка на существующий логин	/	Authen
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

//	Просмотр всех данных	/	Authen
void Authentication::printAll()
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
//	Просмотр по определенному логину	/	Authen
void Authentication::printBYlogin(string login)
{
	User* temp = begin;
	cout << "= = = = = = = = = =" << endl;
	while (temp != nullptr)
	{
		if (temp->login == login)
		{
			cout << "Логин: " << temp->login;
			cout << "Пароль: " << temp->Pass;
			cout << "= = = = = = = = = =" << endl;
		}
		temp = temp->pNext;
	}
}

//	Добавление	/	Authen
void Authentication::PushFront(const string login, const string pass) { begin = new User(login, pass, begin); Vol++; }

//	Редактирование логина и пароля	/	Authen
void Authentication::edit_all(const string login)
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
//	Редактирование логина	/	Authen
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
//	Редактирование пароля	/	Authen
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

//	Удаление первой записи	/	Authen
void Authentication::pop_front()
{
	User* temp = begin;
	begin = begin->pNext;
	delete temp;
	Vol--;
}
//	Удаление всех данных	/	Authen
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
//	Удаление по определенному логину	/	Authen
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

//	Чтение из файла	/	Authen
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
//	Запись в файла	/	Authen
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
	if (!FILE_SHOES.is_open()) { cout << "Ошибка открытия файла! Данные не загружены!" << endl; }
	else
	{
		ost(FILE_SHOES);
		if (GetVol() != 0) cout << "Найдено " << GetVol() << " записей." << endl << endl;
	}
	FILE_SHOES.close();
}
//	Деструктор	/	Shoe_Shop
Shoes_Shop::~Shoes_Shop()
{
	FILE_SHOES.open(ShoesFile, ios::out);
	ist(FILE_SHOES);
	FILE_SHOES.close();

	clear();
}

//	Добавление в начало	/	Shoe_Shop
void Shoes_Shop::PushFront(string art, string name, double price, string make, int size, int count)
{
	begin = new Shoe(art, name, price, make, size, count, begin);
	Vol++;
}
//	Добавление в конец	/	Shoe_Shop
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

//	Удаление первой записи	/	Shoe_Shop
void Shoes_Shop::pop_front()
{
	Shoe* temp = begin;
	begin = begin->pNext;
	delete temp;
	Vol--;
}
//	Удаление последней записи	/	Shoe_Shop
void Shoes_Shop::pop_back() { remove_At(Vol); }
//	Удаление по определенному индексу(ИД)	/	Shoe_Shop
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
//	Удаление всех записей	/	Shoe_Shop
void Shoes_Shop::clear() { while (Vol) pop_front(); }

//	Просмотр всех записей	/	Shoe_Shop
void Shoes_Shop::print()
{
	Shoe* temp = begin;

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
//	Просмотр по определенному артиклу и размеру
void Shoes_Shop::print_as(string art, int size)
{
	Shoe* temp = begin;


	for (int i = 1; temp != nullptr; i++)
	{
		if (temp->Art == art && temp->Size == size)
		{
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

//	Чтение из файла	/	Shoe_Shop
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
//	Запись в файл	/	Shoe_Shop
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