#pragma once
#include<iostream>
using namespace std;
class Student
{
	char * name;
	char * surname;
	int age;
	char phone[12];
	double average;
public:
	Student();
	Student(const char * name, const char * surname, int age, const char * phone, double average);
	~Student();

	char* getName() const;
	char * getSurname() const;
	int getAge() const;
	double getAverage() const;
	char * getPhone();

	void setName(const char * name);
	void setSurname(const char * surname);
	void setPhone(const char * phone);
	void setAge(int age);
	void setAverage(double average);
};