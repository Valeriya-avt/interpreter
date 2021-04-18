#ifndef LEXEM_H
#define LEXEM_H

#include "const.h"
#include <vector>
#include <map>
#include <string>

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
	virtual void printArray();
	virtual string getName();
	virtual void setRow(int row);
	virtual int getRow();
	virtual int getIndex();
	virtual int inLabelsMap();
	virtual int inFunctionsMap();
	virtual void createArray(int _size);
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

class Goto : public Oper {
	int row;
public: 
	enum { UNDEFINED = -INT32_MAX };
	Goto(int optype);
	void setRow(int row);
	int getRow();
	void print();
};

class Variable: public Lexem {
	string name;
public:
	Variable(string str, int value = 0);
	void print();
	string getName();
	int inLabelsMap();
	int inFunctionsMap();
};

class ArrayElement;

class Array: public Lexem {
	vector <ArrayElement *> data;
	int size;
	string name;
public:
	Array();
	Array(string _name);
	ArrayElement *getValue(int index);
	void createArray(int _size);
	string getName();
	void print();
	void printArray();
	virtual ~Array();
};

class ArrayElement: public Array {
	int data;
	int index;
	string name;
public:
	ArrayElement(string name, int _index = 0, int value = 0);
	int getValue();
	int getIndex();
	void setValue(int value);
	string getName();
	void print();
	~ArrayElement();
};

struct Space {
	map<string, int> variablesMap;
	map<string, Array *> arraysMap;
	stack<Lexem *> computationStack;
};

#endif