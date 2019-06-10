#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int IndexMenu;


struct WORKER
{
	char surname[20];
	char post[20];
	int yearEmp;
	struct { unsigned int day, month, year; } birthday;
};

void outPutForExp(WORKER* Emp, int yearNow, int i)
{
	
		cout << setw(3) << left << i + 1 << setw(14) << left << Emp[i].surname << setw(14) << left << Emp[i].post << setw(14) <<
			left << Emp[i].yearEmp << left << Emp[i].birthday.day << "." << Emp[i].birthday.month << "." << Emp[i].birthday.year << setw(5) << right << "\t" << yearNow - Emp[i].yearEmp << " years" << endl;
	
}

void outPutForMonth(WORKER* Emp, int i)
{

	cout << setw(3) << left << i + 1 << setw(14) << left << Emp[i].surname << setw(14) << left << Emp[i].post << setw(14) <<
		left << Emp[i].yearEmp << left << Emp[i].birthday.day << "." << Emp[i].birthday.month << "." << Emp[i].birthday.year << endl;

}


void outPut(WORKER* Emp, int size)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	int yearNow = st.wYear;

	cout << setw(3) << "№ " << setw(14) << left << "Surname" << left << setw(10) << "Post" << setw(13) << left << "YearEmploye" << setw(14) << left << "Birthday";
	if (IndexMenu == 5)
		cout << "\t" << setw(13) << left << "Age";
	cout << "\n-------------------------------------------------------------------------------------" << endl;

	if (IndexMenu == 5)
	{
		for (int i = 0; i < size - 1; i++)
			cout << setw(3) << i + 1 << setw(14) << Emp[i].surname << setw(10) << Emp[i].post << setw(8) << Emp[i].yearEmp << "\t"
			<< Emp[i].birthday.day << "." << Emp[i].birthday.month << "." << Emp[i].birthday.year << "\t"  << setw(13) << left   << yearNow - Emp[i].birthday.year << endl;
	}
	else
	for (int i = 0; i < size - 1; i++)
		cout << setw(3) << i + 1 << setw(14) << Emp[i].surname << setw(10) << Emp[i].post << setw(8) << Emp[i].yearEmp << "\t"
		<< Emp[i].birthday.day << "." << Emp[i].birthday.month << "." << Emp[i].birthday.year << endl;

	cout << "-------------------------------------------------------------------------------------" << endl;

	cout << endl;
	cout << endl;
}

void sortByMonth(WORKER* Emp, int size)
{
	int i, j;
	int monthCin;
	char Ch;
	WORKER* temp = new WORKER[size];

	for (i = 0; i < size; i++) temp[i] = Emp[i];


	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - 1; j++)
			if ( temp[j].birthday.day < temp[j+1].birthday.day)
				swap(temp[j], temp[j+1]);

	while (1)
	{
		cout << endl;
		cout << "Enter the month: ";
		cin >> monthCin;
		system("cls");
		cout << setw(3) << "№ " << setw(14) << left << "Surname" << left << setw(10) << "Post" << setw(13) << left << "YearEmploye" << setw(14) << left << "Birthday";
		cout << "\n-------------------------------------------------------------------------------------" << endl;
		for (i = 0; i < size; i++)
			if (temp[i].birthday.month == monthCin)
				outPutForMonth(temp, i);
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << endl;

		cout << "Повторить?[Y/N]"<< endl;
		cin >> Ch;
		if (Ch == 'N' || Ch == 'n')
		{
			system("cls");
			break;
		}

	}
}

void sortByAge(WORKER* Emp, int size, int yearNow)
{
	int i, j;
	WORKER* temp = new WORKER[size];
	for (i = 0; i < size; i++) temp[i] = Emp[i];

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size; j++)
			if (yearNow - temp[i].birthday.year > yearNow - temp[j].birthday.year)
				swap(temp[i], temp[j]);

	outPut(temp, size);

	delete[] temp;
}

void sortBySurname(WORKER* Emp, int size)
{
	int i, j;
	WORKER* temp = new WORKER[size];
	for (i = 0; i < size; i++) temp[i] = Emp[i];

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size; j++)
			if (strcmp(temp[i].surname, temp[j].surname) < 0)
				swap(temp[i], temp[j]);

	outPut(temp,size);

	delete [] temp;
}

void sortByExp(WORKER* Emp, int size, int yearNow)
{
	int i, j;
	char range[4];

	WORKER* temp = new WORKER[size];

	for (i = 0; i < size; i++) temp[i] = Emp[i];

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - 1; j++)
			if (yearNow - temp[j].yearEmp < yearNow - temp[j+1].yearEmp)
				swap(temp[j], temp[j+1]);

	while (1)
	{
		cout << "N - Back to menu" << endl;
		cout << endl;

		cout << "Take format: \n " << "<=X \n " << ">=X \n " << "X" << endl;
		cout << "...And enter the experience range: ";
		cin >> range; 
		system("cls");

		if (range[0] == 'N' || range[0] == 'n') { system("cls");  break; }


		if (range[0] != '<' && range[0] != '>' && !isdigit(range[0]))
		{
			cout << endl;
			cout << "Incorrect range!" << endl;
			cout << endl;
			continue;
		}

		cout << "The range is: " << range[0] << range[1] << range[2] << range[3] << endl;
		cout << endl;

		cout << setw(3) << left << "№" << setw(14) << left << "Surname" << setw(14) << left << "Post \t" << setw(14) << left << "YearEmploye"
			<< setw(14) << left << "Birthday" << setw(14) << left << "Experience" << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;

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
				if (yearNow - temp[i].yearEmp == digit1) outPutForExp(temp, yearNow, i);
		}
		else if (range[1] != '=' || !isdigit(range[2]))
		{
			cout << endl;
			cout << "Incorrect range!" << endl;
			cout << endl;
			continue;
		}		
		else if (range[0] == '<')
		{
			digit1 = range[2] - '0';
			if (isdigit(range[3]))
			{
				int digit2 = range[3] - '0';
				digit1 = digit1 * 10 + digit2;
			}

			for (int i = 0; i < size - 1; i++)
				if (yearNow - temp[i].yearEmp <= digit1) outPutForExp(temp, yearNow, i);
		}
		else
		{
			digit1 = range[2] - '0';
			if (isdigit(range[3]))
			{
				int digit2 = range[3] - '0';
				digit1 = digit1 * 10 + digit2;
			}
			for (int i = 0; i < size - 1; i++)
				if (yearNow - temp[i].yearEmp >= digit1) outPutForExp(temp, yearNow, i);
		}
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << endl;
		cout << endl;
	}
	delete [] temp;
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

		file.close();
		SYSTEMTIME st;
		GetSystemTime(&st);
		int yearNow = st.wYear;

		while (1)
		{
			cout << "File is found!" << endl;
			cout << "Menu: " << endl;
			cout << "1 - Full Info" << endl;
			cout << "2 - Sort by surname" << endl;
			cout << "3 - by experience" << endl;
			cout << "4 - by date of birth" << endl;
			cout << "5 - by age" << endl;
			cout << endl;
			cout << "6 - Exit" << endl;
			cout << endl;
			cout << endl;
			cin >> IndexMenu;
			system("cls");

			switch (IndexMenu)
			{
			case 1: {outPut(list, count); break; }
			case 2: {sortBySurname(list, count); break; }
			case 3: {sortByExp(list, count, yearNow); break;}
			case 4: {sortByMonth(list, count); break; }
			case 5: {sortByAge(list, count, yearNow); break; }
			case 6: return 0;
			default: {cout << "Incorrect number!" << endl; break; }
			}
		}
	}
	system("pause");
	return 0;
}