#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#define output cout << setw(3) << left << i + 1 << setw(14) << left << temp[i].surname << setw(14) << left << temp[i].post << setw(14) << left << temp[i].yearEmp << left << temp[i].birthday.day << "." << temp[i].birthday.month << "." << temp[i].birthday.year << setw(5) << right << yearNow - temp[i].yearEmp << " years" << endl;



using namespace std;


struct WORKER
{
	char surname[20];
	char post[20];
	int yearEmp;
	struct { unsigned int day, month, year; } birthday;
};


void outPut(WORKER* Emp, int size)
{
	cout << setw(3) << "№ " << setw(14) << left << "Surname" << left << setw(10) << "Post" << setw(13) << left << "YearEmploye" << "Birthday" << endl;
	for (int i = 0; i < size - 1; i++)
		cout << setw(3) << i + 1 << setw(14) << Emp[i].surname << setw(10) << Emp[i].post << setw(8) << Emp[i].yearEmp << "\t"
		<< Emp[i].birthday.day << "." << Emp[i].birthday.month << "." << Emp[i].birthday.year << endl;

	cout << endl;
	cout << endl;
}

void sortByExp(WORKER* Emp, int size, int yearNow)
{
	int i, j;
	bool isDigit;
	char range[4];
	

	WORKER* temp = new WORKER[size];

	for (i = 0; i < size; i++) temp[i] = Emp[i];

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - 1; j++)
			if (yearNow - temp[j].yearEmp < yearNow - temp[j + 1].yearEmp)
				swap(temp[j], temp[j + 1]);

	while(1)
	{ 
		cout << "N - Back to menu" << endl;
		cout << endl;

		cout << "Take format: \n " << "<=X \n " <<">=X \n " << "X" << endl;
		cout << "...And enter the experience range: ";
		cin >> range;
		system("cls");
		cout << "The range is: " << range[0] << range[1] << range[2]  << range[3] << endl;

		if (range[0] == 'N' || range[0] == 'n') { system("cls");  break; }

		cout << setw(3) << left << "№" << setw(14) << left << "Surname" << setw(14) << left << "Post" << setw(14) << left << "YearEmploye"
			<< setw(14) << left << "Birthday" << setw(14) << left << "Experience" << endl;
		
		int digit1;

		if (isdigit(range[0])) 
		{	
			digit1 = range[0] - '0'; 

			if (isdigit(range[1])) 
			{
				int digit2 = range[1] - '0'; 
				digit1 = digit1 * 10 + digit2; 
			}
			
			for (int i = 0; i < size - 1; i++)
				if (yearNow - temp[i].yearEmp == digit1) output;
		}
		else if (range[0] == '<')
		{
			digit1 = range[2] - '0';

			for (int i = 0; i < size - 1; i++)
				if (yearNow - temp[i].yearEmp <= digit1) output;
		}
		else 
		{
			digit1 = range[2] - '0';
			for (int i = 0; i < size - 1; i++)
			if (yearNow - temp[i].yearEmp >= digit1) output;
			
		}
		cout << endl; 
		cout << endl;

	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	ifstream file("File.txt");										
	if (!file.is_open()) cout << "File not found" << endl;			
	else
	{
		int count(1), i(0);
		WORKER* list = new WORKER[count];													
		file >> list[i].surname >> list[i].post >> list[i].yearEmp >>						
			list[i].birthday.day >> list[i].birthday.month >> list[i].birthday.year;		

		while (!file.eof())
		{
			WORKER* temp = new WORKER[count];						

			for (i = 0; i < count; i++) temp[i] = list[i];
			delete[] list;
			count++;
			list = new WORKER[count];								
			for (i = 0; i < count - 1; i++) list[i] = temp[i];

			file >> list[count - 1].surname >> list[count - 1].post >> list[count - 1].yearEmp >>
				list[count - 1].birthday.day >> list[count - 1].birthday.month >> list[count - 1].birthday.year;
		}

		while (1)
		{
			int IndexMenu;
			cout << "File is found!" << endl;
			cout << "Menu: " << endl;
			cout << "1 - Full Info" << endl;
			cout << "2 - Sort by Last Name" << endl;
			cout << "3 - by experience" << endl;
			cout << "4 - by date of birth" << endl;
			cout << endl;
			cout << "5 - Exit" << endl;
			cout << endl;
			cout << endl;
			cin >> IndexMenu;
			system("cls");

			switch (IndexMenu)
			{
			case 1: { outPut(list, count); break; }
			case 2:
			case 3: {
				SYSTEMTIME st;
				GetSystemTime(&st);
				int yearNow = st.wYear;
				sortByExp(list, count, yearNow);
				break;
				}
			case 4:
			case 5: return 0;
			default: {cout << "Неккоректное число" << endl; break; }
			}
		}
	}
	system("pause");
	return 0;
}