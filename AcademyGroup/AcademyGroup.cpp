#include "AcademyGroup.h"
#include "Student.h"

AcademyGroup::AcademyGroup() : 
sizof(5)
{
	count = 0;
	pSt = new Student*[sizof]; if (!pSt) { exit(0); }
	for (int i = 0; i < sizof; i++){
		pSt[i] = new Student; if (!pSt[i]) { exit(0); }
	}
	Load();
}

AcademyGroup::~AcademyGroup(){
	Save();

	int tmp;
	if (count % 5 == 0){
		tmp = count;
	}
	else{
		tmp = (sizof - (count % sizof)) + count;
	}
	for (int i = 0; i < tmp; i++){
		delete pSt[i];
	}
	delete[] pSt;
}

void AcademyGroup::AddStudents(Student & add){
	if (count % sizof == 0 && count != 0){
		Student **pStTemp = new  Student*[count + sizof]; if (!pStTemp) { exit(0); }
		int i;
		for (i = 0; i < count; i++){
			pStTemp[i] = pSt[i];
		}
		delete[] pSt;
		pSt = pStTemp;
		for (; i < count + sizof; i++){
			pSt[i] = new Student; if (!pSt[i]) { exit(0); }
		}
	}
	delete pSt[count];
	pSt[count] = new Student(add.getName(), add.getSurname(), add.getAge(), add.getPhone(), add.getAverage()); if (!pSt[count]) { exit(0); }
	count++;
}

void AcademyGroup::DeleteStudent(int n){
	if (n >= 0 && n < count){
		delete pSt[n];
		n++;
		int i;
		for (i = n; i < count; i++){
			pSt[i - 1] = pSt[i];
		}
		pSt[count - 1] = new Student; if (!pSt[count - 1]){ exit(0); }
		--count;
	}
}

void AcademyGroup::SortSurname(){
	for (int i = 0; i < count; i++){
		for (int j = 1; j < count; j++){
			if (strcmp(pSt[j - 1]->getSurname(), pSt[j]->getSurname()) > 0){
				Student* temp = pSt[j - 1];
				pSt[j - 1] = pSt[j];
				pSt[j] = temp;
			}
		}
	}
}


void AcademyGroup::SortName(){
	for (int i = 0; i < count; i++){
		for (int j = 1; j < count; j++){
			if (strcmp(pSt[j - 1]->getName(), pSt[j]->getName()) > 0){
				Student* temp = pSt[j - 1];
				pSt[j - 1] = pSt[j];
				pSt[j] = temp;
			}
		}
	}
}

void AcademyGroup::SortAge(){
	for (int i = 0; i < count; i++){
		for (int j = 1; j < count; j++){
			if (pSt[j - 1]->getAge() > pSt[j]->getAge()){
				Student* temp = pSt[j - 1];
				pSt[j - 1] = pSt[j];
				pSt[j] = temp;
			}
		}
	}
}

void AcademyGroup::SortAverage(){
	for (int i = 0; i < count; i++){
		for (int j = 1; j < count; j++){
			if (pSt[j - 1]->getAverage() > pSt[j]->getAverage()){
				Student* temp = pSt[j - 1];
				pSt[j - 1] = pSt[j];
				pSt[j] = temp;
			}
		}
	}
}

void AcademyGroup::Save(){
	FILE* fs = NULL;
	char* path = "AcademyGroup";

	fopen_s(&fs, path, "wb");
	if (fs == 0) exit(0);

	// Запись размера массива
	fwrite(&count, sizeof(count), 1, fs);

	int sizeCount; char* buf;
	double sizeTcount;
	for (int i = 0; i < count; i++){

		sizeCount = strlen(pSt[i]->getName()) + 1;
		fwrite(&sizeCount, sizeof(sizeCount), 1, fs);
		fwrite(pSt[i]->getName(), sizeof(char), sizeCount, fs);

		sizeCount = strlen(pSt[i]->getSurname()) + 1;
		fwrite(&sizeCount, sizeof(sizeCount), 1, fs);
		fwrite(pSt[i]->getSurname(), sizeof(char), sizeCount, fs);

		sizeCount = pSt[i]->getAge();
		fwrite(&sizeCount, sizeof(int), 1, fs);

		buf = pSt[i]->getPhone();
		fwrite(buf, sizeof(char), 12, fs);

		sizeTcount = pSt[i]->getAverage();
		fwrite(&sizeTcount, sizeof(double), 1, fs);
	}
	fclose(fs);
}

void AcademyGroup::Load(){
	FILE* fs = NULL;
	char* path = "AcademyGroup";
	fopen_s(&fs, path, "rb");	if (fs == 0) exit(0);

	int tmp, tmpCont;
	char buf[100];
	double tmpD;
	Student obj;
	fread(&tmpCont, sizeof(tmpCont), 1, fs);

	for (int i = 0; i < tmpCont; i++){

		fread(&tmp, sizeof(int), 1, fs);
		fread(buf, sizeof(char), tmp, fs);
		obj.setName(buf);

		fread(&tmp, sizeof(int), 1, fs);
		fread(buf, sizeof(char), tmp, fs);
		obj.setSurname(buf);

		fread(&tmp, sizeof(int), 1, fs);
		obj.setAge(tmp);

		fread(&buf, sizeof(char), 12, fs);
		obj.setPhone(buf);

		fread(&tmpD, sizeof(double), 1, fs);
		obj.setAverage(tmpD);

		this->AddStudents(obj);
	}

	fclose(fs);
}

Student* AcademyGroup::GetStudent(int n)
{
	if (n >= 0 && n < count)
		return pSt[n];
	return nullptr;
}

int AcademyGroup::GetCount() { 
	return count;
}


int AcademyGroup::SearchSurname(char *s){
	for (int i = 0; i < count; ++i)	{
		if (!strcmp(pSt[i]->getSurname(), s))
			return i;
	}

	return -1;
}

int AcademyGroup::SearchName(char *s){
	for (int i = 0; i < count; ++i)	{
		if (!strcmp(pSt[i]->getName(), s))
			return i;
	}

	return -1;
}

int AcademyGroup::SearchAge(int n){
	for (int i = 0; i < count; ++i)	{
		if (pSt[i]->getAge() == n)
			return i;
	}

	return -1;
}

int AcademyGroup::SearchAverage(double n){
	for (int i = 0; i < count; ++i)	{
		if (pSt[i]->getAverage() == n)
			return i;
	}

	return -1;
}

int AcademyGroup::SearchPhone(char *s){
	for (int i = 0; i < count; ++i)	{
		if (!strcmp(pSt[i]->getPhone(), s))
			return i;
	}

	return -1;
}