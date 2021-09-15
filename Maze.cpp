#include "Tool\include.h"


int main()
{
	setlocale(LC_ALL, "rus");

	get_info_game();

	while (1) 
	{
		string command;
		double var; // int var;

		cout << ">>> Введите команду: ";
		cin >> command;

		cout << ">>> Значение: ";
		cin >> var;

		SetValueFLOAT(command.c_str(), var); // SetValueINT(command.c_str(), var);
		system("cls");
	}
}