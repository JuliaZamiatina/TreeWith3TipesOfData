// AssaignmentTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Node.h"
#include <exception>
using namespace std;


int main(int argc, char* argv[])
{
	//При запуске программы обязателен следующий список аргументов: -i input_file -o output_file,
	//где input_file - полное имя файла для чтения,
	//output_file - полное имя файла для записи.
	setlocale(LC_ALL, "");
	ifstream f_in;
	ofstream f_out;
	if (argc < 5) {
		cout << "Вы ввели недостаточно аргументов.\n";
		system("pause");
		return 0;
	}
	for (int i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-i", 3) == 0)
			f_in.open(argv[i+1]);
		if (strncmp(argv[i], "-o", 3) == 0)
			f_out.open(argv[i+1]);
	}

	if (!f_in) {
		cout << "Не указан файл для чтения или у него неверный формат\n";
		system("pause");
		return 0;
	}

	if (!f_out) {
		cout << "Не указан файл для записи или у него неверный формат\n";
		system("pause");
		return 0;
	}
	MyElement *Tree1 = new MyElement();
	try {
		Tree1->deSerialize(&f_in);
		Tree1->print_Tree(0);
		Tree1->serialize(&f_out);
		cout << endl;
	}
	catch (exception ex){
		cout << "Информация во входном файле не соответсвует дереву.\n";
	}
	system("pause");
	return 1;
}

