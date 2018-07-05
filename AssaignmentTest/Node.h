#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <variant>
#include <Windows.h>
#include <exception>
using namespace std;
typedef std::variant<int, string, double> vr;

class MyElement // Класс узла бинарного дерева
{
public:
	MyElement();
	MyElement(const vr &d);

	inline void print_Tree(int level);//Функция вывода дерева на экран
	inline void serialize(ofstream  *fp);//Функция сериализации дерева
	inline void deSerialize(ifstream *fp);
	MyElement* left;
	MyElement* right;
	MyElement* middle;
	vr data;
	int n = 0;
};
MyElement::MyElement(){
	this->left = this->middle = this->right = NULL;
}

MyElement::MyElement(const vr &d)
{
	data = d;
	this->left = this->middle = this->right = NULL;
}

inline void MyElement::print_Tree(int level)
{
	//Начиная с самого левого узла дерева, функция выводит значания узлов на экран. 
	//При этом выставляет отступ в зависимости от уровня узла.
	if (this)
	{
		(this->left)->print_Tree(level + 1);
		for (int i = 0; i < level; i++) cout << "         ";
		try {
			double f = get<double>(this->data);
			cout << f << endl;
			
		}
		catch (std::bad_variant_access&) {}
		try {
			int i = get<int>(this->data);
			cout << i << endl;

		}
		catch (std::bad_variant_access&) {}
		try {
			string s = get<string>(this->data);
			cout << s << endl;

		}
		catch (std::bad_variant_access&) {}
		(this->middle)->print_Tree(level + 1);
		(this->right)->print_Tree(level + 1);
	}
}

inline void MyElement::serialize(ofstream *fp)
{
	//Функция записывает каждый узел, начиная от корня в текстовый файл.
	//Формат записи: s~c~n, где s - значение, записанное в узле,
	// с - тип данных этого значения, n - количество дочерних узлов.
	//После записи значения, функция рекурсивно переходит к записи левого/среднего/правого дочерних узлов.
	if (this == NULL) return;
		
	try {
		double f = get<double>(this->data);
		*fp << f;
	}
	catch (std::bad_variant_access&) {}
	try {
		int i = get<int>(this->data);
		*fp << i;
	}
	catch (std::bad_variant_access&) {}
	try {
		string s = get<string>(this->data);
		*fp << s;
	}
	catch (std::bad_variant_access&) {}
	*fp << "~";

	*fp << (this->data).index() << "~" << this->n << " ";
	if (this->left)
			(this->left)->serialize(fp);
	if (this->middle)
			(this->middle)->serialize(fp);
	if (this->right)
			(this->right)->serialize(fp);
}

inline void MyElement::deSerialize(ifstream *fp)
{	
	//Функция читает из текстового файла каждый узел, начиная от корня.
	//Формат чтения: s~c~n, где s - значение узла,
	//с - тип данных этого значения, n - количество дочерних узлов.
	//После чтения значения, функция рекурсивно переходит к чтению левого/среднего/правого дочерних узлов.

	vr val;
	char s[10] = "\0";
	char c,v = 0;
	try {
		fp->getline(s, 10, '~');
		fp->get(c);
		fp->get(v);
		if (v !='~') throw invalid_argument("");
		this->n = fp->get() - 48;
	}
	catch (exception ex) {
		throw invalid_argument("");
	}
	switch (c)
	{
	case '0':
		this->data.operator=(atoi(s));
		fp->get(c);
		break;
	case '2':
		this->data.operator=(atof(s));
		fp->get(c);
		break;
	case '1':
		this->data.operator=(s);
		fp->get(c);
	}
	if (this->n > 0) {
		this->left = new MyElement();
		this->left->deSerialize(fp);
	}
	if (this->n > 1) {
		this->middle = new MyElement();
		this->middle->deSerialize(fp);
	}
	if (this->n > 2) {
		this->right = new MyElement();
		this->right->deSerialize(fp);
	}
}