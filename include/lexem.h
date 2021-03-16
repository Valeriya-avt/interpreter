#ifndef LEXEM_H
#define LEXEM_H

#include "const.h"

using namespace std;

class Lexem {
	LEX_TYPE type;
public:
	Lexem();
	int getLexType();
	void setType(LEX_TYPE type);
	virtual int getType();
	virtual int getValue(int a = 1, int b = 1);
	virtual int getPriority();
	virtual void print();
	virtual string getName();
	virtual ~Lexem();
};

class Number: public Lexem {
	int value;
public:
	Number(int number);
	int getValue(int a = 1, int b = 1);
	void print();
};

class Oper: public Lexem {
	OPERATOR opertype;
public:
	Oper(int charCode);
	int getType();
	int getPriority();
	int getValue(int left = 1, int right = 1);
	void print();
};

class Variable: public Lexem {
	string name;
public:
	Variable(string str, int value = 0);
	void print();
	string getName();
};

#endif