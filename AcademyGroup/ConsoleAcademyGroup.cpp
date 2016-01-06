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
			{ "���������� ��������� � ������", AddingStudentsGroup },
			{ "�������� �������� �� ������", RemovalStudentFromGroup },
			{ "����������� ������ ��������", ModificationStudentData },
			{ "����� ��������� ������������� ������", PrintAcademicGroup },
			{ "���������� ������ ���������", SortListStudents },
			{ "����� �������� �� ��������� ��������", SearchStudentAccordingPredeterminedCriteria },
			{ "����� �� ���������", ExitProgram }
	};

	Mptr = new Menu(sizeof(list) / sizeof(list[0]), list);

	Mptr->MenuShow();
}

bool AddingStudentsGroup()	//	���������� ��������� � ������
{

	int key;

	Student Sobj;
	int temp = 0;
	double tmp = 0.0;
	char buf[MAX_STR];

	do{
		system("cls");

		std::cout << "\t\t\t���������� ��������� � ������" << std::endl << std::endl;

		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());

		std::cout << "������� ������� ��������:\t";
		std::cin.getline(buf, MAX_STR);
		Sobj.setSurname(buf);

		std::cout << "������� ��� ��������:\t";
		std::cin.getline(buf, MAX_STR);
		Sobj.setName(buf);

		std::cout << "������� ������� ��������:\t";
		std::cin >> temp;
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		Sobj.setAge(temp);

		std::cout << "������� ����� �������� ��������:\t";
		std::cin.getline(buf, MAX_STR);
		Sobj.setPhone(buf);

		std::cout << "������� average ��������:\t";
		std::cin >> tmp;
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		Sobj.setAverage(tmp);

		CAGobj.AGptr->AddStudents(Sobj);

		std::cout << "\n\n��� ����������� ��������, ������� ������� Enter." << std::endl;
		std::cout << "��� ���������� ����� ������� Esc." << std::endl;

		key = _getch();
	} while (key != ESC || key == ENTER);

	system("cls");
	return true;
}

bool RemovalStudentFromGroup()	//	�������� �������� �� ������
{
	system("cls");

	std::cout << "�������� �������� �� ������" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		int key = 0;

		std::cout << "������� �������� �� �����?" << std::endl;
		std::cout << "��� ������������� ������� ������� Enter" << std::endl;
		std::cout << "��� ������ ������� ������� Esc" << std::endl;

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

bool ModificationStudentData()	//	����������� ������ ��������
{
	system("cls");

	std::cout << "����������� ������ ��������" << std::endl;

	menu_item listSearch[] {
			{ "�������� �������", ModificationSurname },
			{ "�������� ���", ModificationName },
			{ "�������� �������", ModificationAge },
			{ "�������� �������", ModificationPhone },
			{ "�������� avege", ModificationAverage }
	};

	Menu m(sizeof(listSearch) / sizeof(listSearch[0]), listSearch, { 0, 2 });

	m.MenuShow();

	system("cls");
	return true;
}

bool PrintAcademicGroup()	//	������ ������������� ������
{
	system("cls");

	std::cout << "\t\t�������� ������������� ������" << std::endl << std::endl;

	for (int i = 0; i < CAGobj.AGptr->GetCount(); i++){
		std::cout << endl;
		std::cout.width(2);
		std::cout << i + 1;
		std::cout << "  �������             " << CAGobj.AGptr->GetStudent(i)->getSurname() << std::endl;
		std::cout << "    ���                 " << CAGobj.AGptr->GetStudent(i)->getName() << std::endl;
		std::cout << "    �������             " << CAGobj.AGptr->GetStudent(i)->getAge() << std::endl;
		std::cout << "    �������             " << CAGobj.AGptr->GetStudent(i)->getPhone() << std::endl;
		std::cout << "    Average             " << CAGobj.AGptr->GetStudent(i)->getAverage() << std::endl << std::endl;
	}

	std::cout << "��� ����������� ������� ����� �������" << std::endl;
	_getch();

	system("cls");
	return true;
}

bool SortListStudents()	//	���������� ������ ���������
{
	system("cls");
	std::cout << "���������� ������ ���������" << std::endl;

	menu_item listSort[] {
			{ "�� �������", SortSurname },
			{ "�� �����", SortName },
			{ "�� ��������", SortAge },
			{ "�� avege", SortAverage }
	};
	
	Menu m(sizeof(listSort) / sizeof(listSort[0]), listSort, { 0, 2 });

	m.MenuShow();

	PrintAcademicGroup();

	system("cls");
	return true;
}

bool SearchStudentAccordingPredeterminedCriteria()	//	����� �������� �� ��������� ��������
{
	system("cls");
	std::cout << "����� �������� �� ��������� ��������" << std::endl;

	menu_item listSearch[] {
			{ "�� �������", SearchSurname },
			{ "�� �����", SearchName },
			{ "�� ��������", SearchAge },
			{ "�� avege", SearchAverage }
	};

	Menu m(sizeof(listSearch) / sizeof(listSearch[0]), listSearch, { 0, 2 });

	m.MenuShow();

	system("cls");
	return true;
}

bool ExitProgram()	//	����� �� ���������
{
	system("cls");

	std::cout << "����� �� ��������?" << std::endl;
	std::cout << "��� ������������� ������� ������� Enter" << std::endl;
	std::cout << "��� ������ ������� ������� Esc" << std::endl;

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
	std::cout << "������� ������� ��������:\t";
	std::cin.getline(buf, MAX_STR);
	
	CAGobj.ID = CAGobj.AGptr->SearchSurname(buf);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "��� ����������� ������� ����� �������" << std::endl;
	_getch();

	system("cls");
	return false;
}

bool SearchName(){
	system("cls");

	char buf[MAX_STR];
	std::cout << "������� ��� ��������:\t";
	std::cin.getline(buf, MAX_STR);

	CAGobj.ID = CAGobj.AGptr->SearchName(buf);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "��� ����������� ������� ����� �������" << std::endl;
	_getch();

	system("cls");
	return false;
}

bool SearchAge(){
	system("cls");

	int tmp;
	std::cout << "������� ������� ��������:\t";
	std::cin >> tmp;
	std::cin.clear();
	std::cin.ignore(cin.rdbuf()->in_avail());
	
	CAGobj.ID = CAGobj.AGptr->SearchAge(tmp);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "��� ����������� ������� ����� �������" << std::endl;
	_getch();

	system("cls");
	return false;
}

bool SearchAverage(){
	system("cls");

	double tmp;
	std::cout << "������� average ��������:\t";
	std::cin >> tmp;
	std::cin.clear();
	std::cin.ignore(cin.rdbuf()->in_avail());

	CAGobj.ID = CAGobj.AGptr->SearchAverage(tmp);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "��� ����������� ������� ����� �������" << std::endl;
	_getch();

	system("cls");
	return false;
}


bool SearchPhone(){
	system("cls");

	char buf[MAX_STR];
	std::cout << "������� ����� �������� ��������:\t";
	std::cin.getline(buf, MAX_STR);

	CAGobj.ID = CAGobj.AGptr->SearchPhone(buf);

	if (CAGobj.ID >= 0){
		PrintStudent(CAGobj.ID);
	}
	else
		std::cout << "Error..." << std::endl;

	std::cout << "��� ����������� ������� ����� �������" << std::endl;
	_getch();

	system("cls");
	return false;
}

void PrintStudent(int n){
	if (n >= 0 && n < CAGobj.AGptr->GetCount()){
		std::cout << "    �������             " << CAGobj.AGptr->GetStudent(n)->getSurname() << std::endl;
		std::cout << "    ���                 " << CAGobj.AGptr->GetStudent(n)->getName() << std::endl;
		std::cout << "    �������             " << CAGobj.AGptr->GetStudent(n)->getAge() << std::endl;
		std::cout << "    �������             " << CAGobj.AGptr->GetStudent(n)->getPhone() << std::endl;
		std::cout << "    Average             " << CAGobj.AGptr->GetStudent(n)->getAverage() << std::endl << std::endl;
	}
}


bool ModificationSurname(){
	system("cls");
	std::cout << "�������� �������" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){
		
		char buf[MAX_STR];
		std::cout << "������� ���������� ������� ��������:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin.getline(buf, MAX_STR);

		std::cout << "��� ������������� ������� ������� Enter" << std::endl;
		std::cout << "��� ������ ������� ������� Esc" << std::endl;

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
	std::cout << "�������� �����" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		char buf[MAX_STR];
		std::cout << "������� ���������� ��� ��������:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin.getline(buf, MAX_STR);

		std::cout << "��� ������������� ������� ������� Enter" << std::endl;
		std::cout << "��� ������ ������� ������� Esc" << std::endl;

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
	std::cout << "�������� ��������" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		int tmp;
		std::cout << "������� ���������� ������� ��������:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin >> tmp;

		std::cout << "��� ������������� ������� ������� Enter" << std::endl;
		std::cout << "��� ������ ������� ������� Esc" << std::endl;

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
	std::cout << "�������� ��������" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		char buf[MAX_STR];
		std::cout << "������� ���������� ����� �������� ��������:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin.getline(buf, MAX_STR);

		std::cout << "��� ������������� ������� ������� Enter" << std::endl;
		std::cout << "��� ������ ������� ������� Esc" << std::endl;

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
	std::cout << "�������� average" << std::endl;

	SearchStudentAccordingPredeterminedCriteria();

	if (CAGobj.ID >= 0){

		double tmp;
		std::cout << "������� ���������� average ��������:\t";
		std::cin.clear();
		std::cin.ignore(cin.rdbuf()->in_avail());
		std::cin >> tmp;

		std::cout << "��� ������������� ������� ������� Enter" << std::endl;
		std::cout << "��� ������ ������� ������� Esc" << std::endl;

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

