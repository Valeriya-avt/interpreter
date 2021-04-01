#include <iostream>
#include "lexem.h"
//#include "const.h"
//using namespace std;

Lexem::Lexem() { }
int Lexem::getLexType() {return type;}
void Lexem::setType(LEX_TYPE type) {Lexem::type = type;}
int Lexem::getType() {return 0;}
int Lexem::getValue(int a, int b) {return 0;}
int Lexem::getPriority() {return 0;}
void Lexem::print() { }
string Lexem::getName() {return "";}
int Lexem::getRow() { }
int Lexem::inLabelsMap() { }
Lexem::~Lexem() { }

int Number::getValue(int a, int b) {return value;}

Number::Number(int number) {
	value = number;
	this->setType(NUMBER);
}

void Number::print() {cout << "[" << value << "] ";}

Oper::Oper(int index = 0) {
	this->setType(OPER);
	opertype = (OPERATOR)index;
}

int Oper::getType() {return opertype;}
int Oper::getPriority() {return PRIORITY[opertype];}

int Oper::getValue(int left, int right) {
	switch (this->getType()) {
		case ASSIGN: return right;
		case OR: return left || right;
		case AND: return left && right;
		case BITOR: return left | right;
		case XOR: return left ^ right;
		case BITAND: return left & right;
		case EQ: return left == right;
		case NEQ: return left != right;
		case LEQ: return left <= right;
		case LT: return left < right;
		case GEQ: return left >= right;
		case GT: return left > right;
		case SHL: return left << right;
		case SHR: return left >> right;
		case PLUS: return left + right;
		case MINUS: return left - right;
		case MULT: return left * right;
		case DIV: return left / right;
		case MOD: return left % right;
	}
}

void Oper::print() {
	switch (this->getType()) {
		case PLUS: cout << "[+] "; break;
		case MINUS: cout << "[-] "; break;
		case MULT: cout << "[*] "; break;
		case ASSIGN: cout << "[:=] "; break;
		case OR: cout << "[or] "; break;
		case AND: cout << "[and] "; break;
		case BITOR: cout << "[|] "; break;
		case XOR: cout << "[^] "; break;
		case BITAND: cout << "[&] "; break;
		case EQ: cout << "[==] "; break;
		case NEQ: cout << "[!=] "; break;
		case LEQ: cout << "[<=] "; break;
		case LT: cout << "[<] "; break;
		case GEQ: cout << "[>=] "; break;
		case GT: cout << "[>] "; break;
		case SHL: cout << "[<<] "; break;
		case SHR: cout << "[>>] "; break;
		case DIV: cout << "[/] "; break;
		case MOD: cout << "[%] "; break;
	}
}

Variable::Variable(string str, int value) {
	name = str;
	this->setType(VARIABLE);
}

void Variable::print() { cout << "[" << name << "] "; }

string Variable::getName() {return name;}

int Variable::inLabelsMap() {
	auto it = labelsMap.find(name);
	if (it == labelsMap.end())
		return 0;
	else
		return 1;
}

Goto::Goto(int optype): Oper(optype) {
	row = UNDEFINED;
}

void Goto::setRow(int row) { Goto::row = row; }

int Goto::getRow() { return row; }

void Goto::print() {
	cout << "[<row " << row << ">]\n";
}