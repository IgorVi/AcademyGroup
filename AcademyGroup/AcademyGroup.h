#pragma once
#include "Student.h"
class AcademyGroup
{
	Student** pSt;
	int count;
	const int sizof;
public:
	AcademyGroup();
	~AcademyGroup();

	int GetCount();
	Student* GetStudent(int n);

	void AddStudents(Student & add);
	void DeleteStudent(int n);

	void Save();
	void Load();

	void SortSurname();
	void SortName();
	void SortAge();
	void SortAverage();

	int SearchSurname(char*);
	int SearchName(char*);
	int SearchAge(int);
	int SearchAverage(double);
	int SearchPhone(char*);
};