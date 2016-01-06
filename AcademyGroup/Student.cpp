#include "Student.h"

Student::Student(){
	age = 0U;

	const unsigned int capacity = strlen("Unknown") + 1U;

	name = new char[capacity]; if (!name) { exit(0); }
	strcpy_s(name, capacity, "Unknown");

	surname = new char[capacity]; if (!surname) { exit(0); }
	strcpy_s(surname, capacity, "Unknown");

	strcpy_s(phone, capacity, "Unknown");

	average = 0.0;
}

Student::Student(const char * name, const char * surname, int age, const char * phone, double average){
	this->average = average;
	this->age = age;
	const unsigned int capacity = strlen(phone) + 1U;
	const unsigned int capacityName = strlen(name) + 1U;
	const unsigned int capacitySurname = strlen(surname) + 1U;

	this->name = new char[capacityName]; if (!this->name) { exit(0); }
	this->surname = new char[capacitySurname]; if (!this->surname) { exit(0); }

	strcpy_s(this->name, capacityName, name);
	strcpy_s(this->surname, capacitySurname, surname);
	strcpy_s(this->phone, capacity, phone);

	this->average = average;
}

Student::~Student(){
	if (strcmp(name, "Unknown") != 0)
		delete[] name;
	if (strcmp(surname, "Unknown") != 0)
		delete[] surname;
}

char* Student::getName() const{
	return name;
}

char* Student::getSurname() const{
	return surname;
}

int Student::getAge() const{
	return age;
}

double Student::getAverage() const{
	return average;
}

char* Student::getPhone()
{
	return phone;	 
}

void Student::setName(const char * name){
	delete[] this->name;
	const unsigned int capacityName = strlen(name) + 1U;
	this->name = new char[capacityName]; if (!this->name) { exit(0); }
	strcpy_s(this->name, capacityName, name);
}

void Student::setSurname(const char * surname){
	delete[] this->surname;
	const unsigned int capacitySurname = strlen(surname) + 1U;
	this->surname = new char[capacitySurname]; if (!this->surname) { exit(0); }
	strcpy_s(this->surname, capacitySurname, surname);
}

void Student::setPhone(const char * phone){
	for (int i = 0; i < 12; i++){
		this->phone[i] = *(phone + i);
	}
}

void Student::setAge(int age){
	this->age = age;
}

void Student::setAverage(double average){
	this->average = average;
}