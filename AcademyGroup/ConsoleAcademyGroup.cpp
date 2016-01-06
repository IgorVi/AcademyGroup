#include<iostream>
#include <conio.h>
#include <Windows.h>

#include "ConsoleAcademyGroup.h"
#include "Menu.h"

#define MAX_STR 256

static enum { ESC = 27, UP = 72, DOWN = 80, ENTER = 13 };

bool ConsoleAcademyGroup::flag = false;

static ConsoleAcademyGroup CAGobj;

ConsoleAcademyGroup::ConsoleAcademyGroup()
{
	if (!flag){
		ID = 0;
		flag = true;
		CMGptr = new ConsoleAcademyGroup;
		Mptr = nullptr;
		AGptr = new AcademyGroup;
	}
}


ConsoleAcademyGroup::~ConsoleAcademyGroup()
{
	if (flag){
		delete CMGptr;
		delete Mptr;
		delete AGptr;
	}
}

void ConsoleAcademyGroup::Start()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	menu_item list[] {
			{ "Добавление студентов в группу", AddingStudentsGroup },
			{ "Удаление студента из группы", RemovalStudentFromGroup },
			{ "Модификация данных студента", ModificationStudentData },
			{ "Показ студентов академической группы", PrintAcademicGroup },
			{ "Сортировка списка студентов", SortListStudents },
			{ "Поиск студента по заданному критерию", SearchStudentAccordingPredeterminedCriteria },
			{ "Выход из программы", ExitProgram }
	};

	Mptr = new Menu(sizeof(list) / sizeof(list[0]), list);

	Mptr->MenuShow();
}

bool AddingStudentsGroup()	//	Добавление студентов в группу
{

	int key;

	Student Sobj;
	int temp = 0;
	double tmp = 0.0;
	char buf[MAX_STR];

	do{
		system("cls");

		std::cout << "\t\t\tДобавление студентов в группу" << std::endl << std::endl;

		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());

		std::cout << "Введите фамилию студента:\t";
		std::cin.getline(buf, MAX_STR);
		Sobj.setSurname(buf);

		std::cout << "Введите имя студента:\t";
		std::cin.getline(buf, MAX_STR);
		Sobj.setName(buf);

		std::cout << "Введите возраст студента:\t";
		std::cin >> temp;
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		Sobj.setAge(temp);

		std::cout << "Введите номер телефона студента:\t";
		std::cin.getline(buf, MAX_STR);
		Sobj.setPhone(buf);

		std::cout << "Введите average студента:\t";
		std::cin >> tmp;
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		Sobj.setAverage(tmp);

		CAGobj.AGptr->AddStudents(Sobj);

		std::cout << "\n\nДля дообавления студента, нажмите клавишу Enter." << std::endl;
		std::cout << "Дль завершения ввода нажмите Esc." << std::endl;

		key = _getch();
	} while (key != ESC || key == ENTER);

	system("cls");
	return true;
}

bool RemovalStudentFromGroup()	//	Удаление студента из группы
{
	system("cls");

	std::cout << "Удаление студента из группы" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		int key = 0;

		std::cout << "Удалить студента из групы?" << std::endl;
		std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
		std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

		do{
			key = _getch();
		} while (key != ESC && key != ENTER);

		if (key == ENTER){
			CAGobj.AGptr->DeleteStudent(CAGobj.ID);
		}
	}

	system("cls");
	return true;
}

bool ModificationStudentData()	//	Модификация данных студента
{
	system("cls");

	std::cout << "Модификация данных студента" << std::endl;

	menu_item listSearch[] {
			{ "Изменить фамилию", ModificationSurname },
			{ "Изменить имя", ModificationName },
			{ "Изменить возраст", ModificationAge },
			{ "Изменить телефон", ModificationPhone },
			{ "Изменить avege", ModificationAverage }
	};

	Menu m(sizeof(listSearch) / sizeof(listSearch[0]), listSearch, { 0, 2 });

	m.MenuShow();

	system("cls");
	return true;
}

bool PrintAcademicGroup()	//	Печать академической группы
{
	system("cls");

	std::cout << "\t\tСтуденты академической группы" << std::endl << std::endl;

	for (int i = 0; i < CAGobj.AGptr->GetCount(); i++){
		std::cout << endl;
		std::cout.width(2);
		std::cout << i + 1;
		std::cout << "  Фамилия             " << CAGobj.AGptr->GetStudent(i)->getSurname() << std::endl;
		std::cout << "    Имя                 " << CAGobj.AGptr->GetStudent(i)->getName() << std::endl;
		std::cout << "    Возраст             " << CAGobj.AGptr->GetStudent(i)->getAge() << std::endl;
		std::cout << "    Телефон             " << CAGobj.AGptr->GetStudent(i)->getPhone() << std::endl;
		std::cout << "    Average             " << CAGobj.AGptr->GetStudent(i)->getAverage() << std::endl << std::endl;
	}

	std::cout << "Для продолжения нажмите любую клавишу" << std::endl;
	_getch();

	system("cls");
	return true;
}

bool SortListStudents()	//	Сортировка списка студентов
{
	system("cls");
	std::cout << "Сортировка списка студентов" << std::endl;

	menu_item listSort[] {
			{ "по фамилии", SortSurname },
			{ "по имени", SortName },
			{ "по возрасту", SortAge },
			{ "по avege", SortAverage }
	};
	
	Menu m(sizeof(listSort) / sizeof(listSort[0]), listSort, { 0, 2 });

	m.MenuShow();

	PrintAcademicGroup();

	system("cls");
	return true;
}

bool SearchStudentAccordingPredeterminedCriteria()	//	Поиск студента по заданному критерию
{
	system("cls");
	std::cout << "Поиск студента по заданному критерию" << std::endl;

	menu_item listSearch[] {
			{ "по фамилии", SearchSurname },
			{ "по имени", SearchName },
			{ "по возрасту", SearchAge },
			{ "по avege", SearchAverage }
	};

	Menu m(sizeof(listSearch) / sizeof(listSearch[0]), listSearch, { 0, 2 });

	m.MenuShow();

	system("cls");
	return true;
}

bool ExitProgram()	//	Выход из программы
{
	system("cls");

	std::cout << "Выйти из програмы?" << std::endl;
	std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
	std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

	int key;
	do{
		key = _getch();
	} while (key != ESC && key != ENTER);

	if (key == ENTER){
		return false;
	}

	return true;
}

bool SortSurname(){
	CAGobj.AGptr->SortSurname();

	return false;
}

bool SortName(){
	CAGobj.AGptr->SortName();

	return false;
}

bool SortAge(){
	CAGobj.AGptr->SortAge();

	return false;
}

bool SortAverage(){
	CAGobj.AGptr->SortAverage();

	return false;
}


bool  SearchSurname(){
	system("cls");

	char buf[MAX_STR];
	std::cout << "Введите фамилию студента:\t";
	std::cin.getline(buf, MAX_STR);
	
	CAGobj.ID = CAGobj.AGptr->SearchSurname(buf);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "Для продолжения нажмите любую клавишу" << std::endl;
	_getch();

	system("cls");
	return false;
}

bool SearchName(){
	system("cls");

	char buf[MAX_STR];
	std::cout << "Введите имя студента:\t";
	std::cin.getline(buf, MAX_STR);

	CAGobj.ID = CAGobj.AGptr->SearchName(buf);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "Для продолжения нажмите любую клавишу" << std::endl;
	_getch();

	system("cls");
	return false;
}

bool SearchAge(){
	system("cls");

	int tmp;
	std::cout << "Введите возраст студента:\t";
	std::cin >> tmp;
	std::cin.clear();
	std::cin.ignore(cin.rdbuf()->in_avail());
	
	CAGobj.ID = CAGobj.AGptr->SearchAge(tmp);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "Для продолжения нажмите любую клавишу" << std::endl;
	_getch();

	system("cls");
	return false;
}

bool SearchAverage(){
	system("cls");

	double tmp;
	std::cout << "Введите average студента:\t";
	std::cin >> tmp;
	std::cin.clear();
	std::cin.ignore(cin.rdbuf()->in_avail());

	CAGobj.ID = CAGobj.AGptr->SearchAverage(tmp);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "Для продолжения нажмите любую клавишу" << std::endl;
	_getch();

	system("cls");
	return false;
}


bool SearchPhone(){
	system("cls");

	char buf[MAX_STR];
	std::cout << "Введите номер телефона студента:\t";
	std::cin.getline(buf, MAX_STR);

	CAGobj.ID = CAGobj.AGptr->SearchPhone(buf);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "Для продолжения нажмите любую клавишу" << std::endl;
	_getch();

	system("cls");
	return false;
}

void PrintStudent(int n){
	if (n >= 0 && n < CAGobj.AGptr->GetCount()){
		std::cout << "    Фамилия             " << CAGobj.AGptr->GetStudent(n)->getSurname() << std::endl;
		std::cout << "    Имя                 " << CAGobj.AGptr->GetStudent(n)->getName() << std::endl;
		std::cout << "    Возраст             " << CAGobj.AGptr->GetStudent(n)->getAge() << std::endl;
		std::cout << "    Телефон             " << CAGobj.AGptr->GetStudent(n)->getPhone() << std::endl;
		std::cout << "    Average             " << CAGobj.AGptr->GetStudent(n)->getAverage() << std::endl << std::endl;
	}
}


bool ModificationSurname(){
	system("cls");
	std::cout << "Изменеие фамилии" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){
		
		char buf[MAX_STR];
		std::cout << "Введите измененную фамилию студента:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin.getline(buf, MAX_STR);

		std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
		std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

		int key = 0;
		do{
			key = _getch();
		} while (key != ESC && key != ENTER);

		if (key == ENTER){
			CAGobj.AGptr->GetStudent(CAGobj.ID)->setSurname(buf);
			PrintStudent(CAGobj.ID);
			_getch();
		}
	}
	system("cls");
	return false;
}

bool ModificationName(){
	system("cls");
	std::cout << "Изменеие имени" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		char buf[MAX_STR];
		std::cout << "Введите измененное имя студента:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin.getline(buf, MAX_STR);

		std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
		std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

		int key = 0;
		do{
			key = _getch();
		} while (key != ESC && key != ENTER);

		if (key == ENTER){
			CAGobj.AGptr->GetStudent(CAGobj.ID)->setName(buf);
			PrintStudent(CAGobj.ID);
			_getch();
		}
	}
	system("cls");
	return false;
}

bool ModificationAge(){
	system("cls");
	std::cout << "Изменеие возрвста" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		int tmp;
		std::cout << "Введите измененный возраст студента:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin >> tmp;

		std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
		std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

		int key = 0;
		do{
			key = _getch();
		} while (key != ESC && key != ENTER);

		if (key == ENTER){
			CAGobj.AGptr->GetStudent(CAGobj.ID)->setAge(tmp);
			PrintStudent(CAGobj.ID);
			_getch();
		}
	}
	system("cls");
	return false;
}

bool ModificationPhone(){
	system("cls");
	std::cout << "Изменеие телефона" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		char buf[MAX_STR];
		std::cout << "Введите измененный номер телефона студента:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin.getline(buf, MAX_STR);

		std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
		std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

		int key = 0;
		do{
			key = _getch();
		} while (key != ESC && key != ENTER);

		if (key == ENTER){
			CAGobj.AGptr->GetStudent(CAGobj.ID)->setPhone(buf);
			PrintStudent(CAGobj.ID);
			_getch();
		}
	}
	system("cls");
	return false;
}

bool ModificationAverage(){
	system("cls");
	std::cout << "Изменеие average" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		double tmp;
		std::cout << "Введите измененный average студента:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin >> tmp;

		std::cout << "Для подтверждения нажмите клавишу Enter" << std::endl;
		std::cout << "Для отмены нажмите клавишу Esc" << std::endl;

		int key = 0;
		do{
			key = _getch();
		} while (key != ESC && key != ENTER);

		if (key == ENTER){
			CAGobj.AGptr->GetStudent(CAGobj.ID)->setAverage(tmp);
			PrintStudent(CAGobj.ID);
			_getch();
		}
	}
	system("cls");
	return false;
}

