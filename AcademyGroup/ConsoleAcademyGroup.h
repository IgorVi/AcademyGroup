#pragma once

#include "Menu.h"
#include "AcademyGroup.h"

bool AddingStudentsGroup();	//	Добавление студентов в группу
bool RemovalStudentFromGroup();	//	Удаление студента из группы
bool ModificationStudentData();	//	Модификация данных студента
bool PrintAcademicGroup();	//	Печать академической группы
bool SortListStudents();	//	Сортировка списка студентов
bool SearchStudentAccordingPredeterminedCriteria();	//	Поиск студента по заданному критерию
bool ExitProgram();	//	Выход из программы

bool SortSurname();
bool SortName();
bool SortAge();
bool SortAverage();

bool SearchSurname();
bool SearchName();
bool SearchAge();
bool SearchAverage();;
bool SearchProgram();

void PrintStudent(int);

bool ModificationSurname();
bool ModificationName();
bool ModificationAge();
bool ModificationPhone();
bool ModificationAverage();

class ConsoleAcademyGroup
{
	static bool flag;
	ConsoleAcademyGroup *CMGptr;
	Menu *Mptr;
public:
	int ID;
	AcademyGroup *AGptr;
	ConsoleAcademyGroup();
	~ConsoleAcademyGroup();
	void Start();
};

