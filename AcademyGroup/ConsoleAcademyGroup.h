#pragma once

#include "Menu.h"
#include "AcademyGroup.h"

bool AddingStudentsGroup();	//	���������� ��������� � ������
bool RemovalStudentFromGroup();	//	�������� �������� �� ������
bool ModificationStudentData();	//	����������� ������ ��������
bool PrintAcademicGroup();	//	������ ������������� ������
bool SortListStudents();	//	���������� ������ ���������
bool SearchStudentAccordingPredeterminedCriteria();	//	����� �������� �� ��������� ��������
bool ExitProgram();	//	����� �� ���������

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

