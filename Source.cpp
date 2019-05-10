#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

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
	WORKER* temp = new WORKER[size];

	for (i = 0; i < size; i++) temp[i] = Emp[i];

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - 1; j++)
			if (yearNow - temp[j].yearEmp < yearNow - temp[j + 1].yearEmp)
				swap(temp[j], temp[j + 1]);
	outPut(temp, size);

}


int main()
{
	setlocale(LC_ALL, "rus");
	ifstream file("File.txt");										// подключение файлового потока ввода-вывода
	if (!file.is_open()) cout << "File not found" << endl;			// проверка отсуствия файла
	else
	{
		int count(1), i(0);
		WORKER* list = new WORKER[count];													//структура работников
		file >> list[i].surname >> list[i].post >> list[i].yearEmp >>						// ввод данных из файла
			list[i].birthday.day >> list[i].birthday.month >> list[i].birthday.year;		//создания массива структуры

		while (!file.eof())
		{
			WORKER* temp = new WORKER[count];						//доп. массив для копирования

			for (i = 0; i < count; i++) temp[i] = list[i];
			delete[] list;
			i++;
			count++;
			list = new WORKER[count];								//резервирование новой памяти
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
			case 1:outPut(list, count); break;
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
			default: cout << "Неккоректное число" << endl; break;
			}
		}
	}
	system("pause");
	return 0;
}