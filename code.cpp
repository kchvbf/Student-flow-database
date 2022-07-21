#include <iostream>
#include <conio.h> //для работы _getch
#include <windows.h> //для работы полифила
#include <fstream> //для работы с файлами
#include <string> //для работы со строками

using namespace std;

struct Student
{
	string Full_Name;
	int set_of_marks[5];
	int scholarship_size;
	Student* next;
};

struct Group
{
	int group_number;
	Student* link1;
	Group* link2;
};

void Group_Student(Group*& Back, Student*& p)
{
	string a;
	int x, i;
	int array[5];

	cout << "Введите ФИО студента: " << endl;
	cin.ignore();
	getline(cin, a);
	if (a == "0")
	{
		Back->link1 = 0;
		return;
	}
	Back->link1 = new Student;
	p = Back->link1;

	p->Full_Name = a;

	cout << "Введите набор оценок студента за последнюю сессию: " << endl;
	for (i = 0; i < 5; i++)
	{
		cin >> array[i];
		p->set_of_marks[i] = array[i];
	}

	cout << "Введите размер стипендии студента: " << endl;
	cin >> x;
	p->scholarship_size = x;

	p->next = 0;
}

int Student_Student(Student*& p)
{
	string a;
	int x, i;
	int array[5];

	cout << "Введите ФИО студента: " << endl;
	cin.ignore();
	getline(cin, a);
	if (a == "0")
	{
		p->next = 0;
		return 1;
	}
	p->next = new Student;
	p = p->next;

	p->Full_Name = a;

	cout << "Введите набор оценок студента за последнюю сессию: " << endl;
	for (i = 0; i < 5; i++)
	{
		cin >> array[i];
		p->set_of_marks[i] = array[i];
	}

	cout << "Введите размер стипендии студента: " << endl;
	cin >> x;
	p->scholarship_size = x;

	return 0;
}

int Group_Group(Group*& Back)
{
	int x;

	cout << "Введите номер группы: " << endl;
	cin >> x;
	if (x == 0)
	{
		Back->link2 = 0;
		return 1;
	}
	Back->link2 = new Group;
	Back = Back->link2;

	Back->group_number = x;

	return 0;
}

void F_Group_Student(Group*& Back, Student*& p, ifstream& y)
{
	string a;
	int x, i;
	int array[5];

	y.ignore();
	getline(y, a);
	if (a == "0")
	{
		Back->link1 = 0;
		return;
	}
	Back->link1 = new Student;
	p = Back->link1;

	p->Full_Name = a;

	for (i = 0; i < 5; i++)
	{
		y >> array[i];
		p->set_of_marks[i] = array[i];
	}

	y >> x;
	p->scholarship_size = x;

	p->next = 0;
}

int F_Student_Student(Student*& p, ifstream& y)
{
	string a;
	int x, i;
	int array[5];

	y.ignore();
	getline(y, a);
	if (a == "0")
	{
		p->next = 0;
		return 1;
	}
	p->next = new Student;
	p = p->next;

	p->Full_Name = a;

	for (i = 0; i < 5; i++)
	{
		y >> array[i];
		p->set_of_marks[i] = array[i];
	}

	y >> x;
	p->scholarship_size = x;

	return 0;
}

int F_Group_Group(Group*& Back, ifstream& y)
{
	int x;

	y >> x;
	if (x == 0)
	{
		Back->link2 = 0;
		return 1;
	}
	Back->link2 = new Group;
	Back = Back->link2;

	Back->group_number = x;

	return 0;
}

void showMenu() //функция вывода пунктов меню
{
	system("cls"); //очистка экрана при помощи данной команды 
	cout << "1) Консольный ввод данных о потоке" << endl;
	cout << "2) Консольный вывод данных о потоке" << endl;
	cout << "3) Добавление студента" << endl;
	cout << "4) Удаление студента" << endl;
	cout << "5) Добавление группы" << endl;
	cout << "6) Удаление группы" << endl;
	cout << "7) Файловый ввод данных о потоке" << endl;
	cout << "8) Файловый вывод данных о потоке" << endl;
	cout << "9) Выход" << endl;	
}

void gotoxy(int x, int y) //функция перемещения стрелочки по консоли
{
	HANDLE hConsole;
	COORD cursorLoc;
	cout.flush();
	cursorLoc.X = x;
	cursorLoc.Y = y;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, cursorLoc);
}

int main()
{
	ifstream y;
	ofstream f;
	Group* Top = 0, * Back, * z;
	Student* p, * t;
	string a;
	int x, i, k;
	int array[5];
	const int NUM_MENU_ITEMS = 9; //кол-во пунктов меню, используется для ограничения перехода по пунктам меню
	int activeMenuItem = 0;
	int ch = 0;
	bool exit = false;

	setlocale(0, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (!exit) //работает до тех пор пока переменная exit не станет равна true
	{
		showMenu(); //функция меню

		gotoxy(0, activeMenuItem); //служит для того, чтобы переместить курсор в заданную позицию в консольном окне 

		ch = _getch(); //функция считывает код одной нажатой клавиши и записывает в переменную ch; получение кода нажатой клавиши
		if (ch == 224) //при нажатии клавиш стрелок сначала идет код 224 и только потом код клавиши стрелки
			ch = _getch();

		switch (ch) //блок обработки нажатой клавиши
		{
		case 27: exit = true; system("cls"); break; //если мы нажали ESC (код 27, этой клавиши) будет выход
		case 72: activeMenuItem--; break; //стрелка вверх
		case 80: activeMenuItem++; break; //стрелка вниз
		case 13: //клавиша enter, в зависимости от выбранного пункта меню
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			//Консольный ввод данных о потоке
			if (((ch == 13) && (activeMenuItem == 0)) || (ch == 49)) //первый пункт меню, выбор либо стрелочками и клавишей enter, либо просто клавишей 1 на клавиатуре
			{
				system("cls");

				if (Top != 0)
					cout << "Вы уже произвели ввод потока" << endl;
				else
				{
					cout << "Введите номер группы: " << endl;
					cin >> x;
					if (x == 0)
					{
						system("cls");
						return 0;
					}

					Top = new Group;
					Back = Top;
					Back->group_number = x;
					Group_Student(Back, p);

					while (1)
					{
						if (Back->link1 == 0) break;
						if (Student_Student(p)) break;
					}
					while (1)
					{
						if (Group_Group(Back)) break;
						Group_Student(Back, p);
						while (1)
						{
							if (Back->link1 == 0) break;
							if (Student_Student(p)) break;
						}
					}
					cout << "Консольный ввод успешно завершен" << endl;
				}

				_getch();
			}
			//Консольный вывод данных о потоке
			else if (((ch == 13) && (activeMenuItem == 1)) || (ch == 50)) //второй пункт меню, выбор либо стрелочками и клавишей enter, либо просто клавишей 2 на клавиатуре
			{
				system("cls");

				if (Top == 0)
					cout << "У вас нет данных о потоке сначала выполните консольный ввод или файловый ввод" << endl;
				else
				{
					Back = Top;
					while (Back)
					{
						cout << Back->group_number << endl;
						p = Back->link1;
						while (p)
						{
							cout << p->Full_Name << endl;
							for (i = 0; i < 5; i++)
							{
								cout << p->set_of_marks[i] << " ";
							}
							cout << "\n";
							cout << p->scholarship_size << endl;
							p = p->next;
						}
						Back = Back->link2;
						cout << "\n";
					}
				}

				_getch();
			}
			//Добавление студента
			else if (((ch == 13) && (activeMenuItem == 2)) || (ch == 51))
			{
				system("cls");

				if (Top == 0)
					cout << "У вас нет данных о потоке сначала выполните консольный ввод или файловый ввод" << endl;
				else
				{
					k = 0;
					cout << "Введите номер группы в которую хотите добавить студента: " << endl;
					cin >> x;
					Back = Top;

					while (Back->group_number != x)
					{
						if (Back->link2 == 0)
						{
							cout << "Нет группы с таким номером" << endl;
							k = 1;
							break;
						}
						Back = Back->link2;
					}
					if (k != 1)
					{
						p = Back->link1;
						if (p == 0)
						{
							Group_Student(Back, p);
							if (Back->link1 == 0)
								cout << "Операция добавления студента успешно отменена" << endl;
							else
								cout << "Добавление студента успешно произведено" << endl;
						}
						else
						{
							while (p->next != 0)
							{
								p = p->next;
							}
							Student_Student(p);
							if (p->next != 0)
								cout << "Добавление студента успешно произведено" << endl;
							else
								cout << "Операция добавления студента успешно отменена" << endl;
							p->next = 0;
						}
					}
				}

				_getch();
			}
			//Удаление студента
			else if (((ch == 13) && (activeMenuItem == 3)) || (ch == 52))
			{
				system("cls");

				if (Top == 0)
					cout << "У вас нет данных о потоке сначала выполните консольный ввод или файловый ввод" << endl;
				else
				{
					k = 0;
					cout << "Введите номер группы из которой хотите удалить студента: " << endl;
					cin >> x;
					Back = Top;

					while (Back->group_number != x)
					{
						if (Back->link2 == 0)
						{
							cout << "Нет группы с таким номером" << endl;
							k = 1;
							break;
						}
						Back = Back->link2;
					}
					if (k != 1)
					{
						p = Back->link1;
						cout << "Введите ФИО студента, которого хотите удалить из группы: " << endl;
						cin.ignore();
						getline(cin, a);
						if (Back->link1 == 0)
						{
							cout << "Студента с предложенным ФИО в этой группе нет" << endl;
						}
						while (p)
						{
							if (p->Full_Name == a)                                  //удаление с начала
							{
								p = p->next;
								delete Back->link1;
								Back->link1 = p;
								cout << "Удаление студента успешно произведено" << endl;
								break;
							}
							if (p->next == 0)
							{
								cout << "Студента с предложенным ФИО в этой группе нет" << endl;
								break;
							}
							if ((p->next->Full_Name == a) && (p->next->next != 0))  //удаление с середины
							{
								t = p->next->next;
								delete p->next;
								p->next = t;
								cout << "Удаление студента успешно произведено" << endl;
								break;
							}
							if ((p->next->Full_Name == a) && (p->next->next == 0))  //удаление с конца
							{
								delete p->next;
								p->next = 0;
								cout << "Удаление студента успешно произведено" << endl;
								break;
							}
							p = p->next;
						}
					}
				}

				_getch();
			}
			//Добавление группы
			else if (((ch == 13) && (activeMenuItem == 4)) || (ch == 53))
			{
				system("cls");

				if (Top == 0)
					cout << "У вас нет данных о потоке сначала выполните консольный ввод или файловый ввод" << endl;
				else
				{
					Back = Top;
					while (Back->link2 != 0)
					{
						Back = Back->link2;
					}
					if (Group_Group(Back))
						cout << "Операция добавления группы успешно отменена" << endl;
					else
					{
						cout << "Добавление группы успешно произведено" << endl;
						Back->link1 = 0;
						Back->link2 = 0;
					}
				}

				_getch();
			}
			//Удаление группы
			else if (((ch == 13) && (activeMenuItem == 5)) || (ch == 54))
			{
				system("cls");

				if (Top == 0)
					cout << "У вас нет данных о потоке сначала выполните консольный ввод или файловый ввод" << endl;
				else
				{
					k = 0;
					cout << "Введите номер группы, которую хотите удалить: " << endl;
					cin >> x;
					Back = Top;

					while (Back->group_number != x)
					{
						if (Back->link2 == 0)
						{
							cout << "Нет группы с таким номером" << endl;
							k = 1;
							break;
						}
						Back = Back->link2;
					}
					if (k != 1)
					{
						if (Back->link1 != 0)                    //удаление студентов из группы если они есть
						{
							p = Back->link1;
							while (p)
							{
								t = p->next;
								delete p;
								p = t;
							}
							Back->link1 = 0;
						}
						if (Back == Top)                         //удаление если группа стоит первой
						{
							Back = Back->link2;
							delete Top;
							Top = Back;
							if (Top == 0)
							{
								cout << "Групп в потоке больше нет" << endl;
							}
							cout << "Группа удалена успешно" << endl;
						}
						else
						{
							z = Top;                             //удаление с середины или с конца
							while (z->link2 != Back)
							{
								z = z->link2;
							}
							Back = Back->link2;
							delete z->link2;
							z->link2 = Back;
							cout << "Группа удалена успешно" << endl;
						}
					}
				}

				_getch();
			}
			//Файловый ввод данных о потоке
			else if (((ch == 13) && (activeMenuItem == 6)) || (ch == 55))
			{
				system("cls");

				if (Top != 0)
					cout << "Вы уже произвели ввод потока" << endl;
				else
				{
					y.open("Vvod.txt");

					y >> x;
					if (x == 0)
					{
						system("cls");
						return 0;
					}

					Top = new Group;
					Back = Top;
					Back->group_number = x;
					F_Group_Student(Back, p, y);

					while (1)
					{
						if (Back->link1 == 0) break;
						if (F_Student_Student(p, y)) break;
					}
					while (1)
					{
						if (F_Group_Group(Back, y)) break;
						F_Group_Student(Back, p, y);
						while (1)
						{
							if (Back->link1 == 0) break;
							if (F_Student_Student(p, y)) break;
						}
					}
					y.close();
					cout << "Файловый ввод успешно завершен" << endl;
				}

				_getch();
			}
			//Файловый вывод данных о потоке
			else if (((ch == 13) && (activeMenuItem == 7)) || (ch == 56))
			{
				system("cls");

				if (Top == 0)
					cout << "У вас нет данных о потоке сначала выполните консольный ввод или файловый ввод" << endl;
				else
				{
					f.open("Vivod.txt");
					Back = Top;
					while (Back)
					{
						f << endl;
						f << Back->group_number << endl;
						p = Back->link1;
						while (p)
						{
							f << p->Full_Name << endl;
							for (i = 0; i < 5; i++)
							{
								f << p->set_of_marks[i] << " ";
							}
							f << endl;
							f << p->scholarship_size << endl;
							p = p->next;
						}
						Back = Back->link2;
					}
					f.close();
					cout << "Вывод в файл успешно произведен" << endl;
				}

				_getch();
			}
			//Выход
			else if (((ch == 13) && (activeMenuItem == 8)) || (ch == 57))
			{
				system("cls");
				exit = true;
				break;
			}			
		}
		if (activeMenuItem < 0) activeMenuItem = 0; //ограничение перехода по пунткам меню, чтоб курсор не уходил вверх
		if (activeMenuItem > NUM_MENU_ITEMS - 1) activeMenuItem = NUM_MENU_ITEMS - 1; //ограничение перехода по пунткам меню, чтоб курсор не уходил вниз
	}
	return 0;
}