#include <iostream>

#include <lexem.h>
#include <variables.h>

Lexem::Lexem() { }
int Lexem::getLexType() {return type;}
void Lexem::setType(LEX_TYPE type) {Lexem::type = type;}
int Lexem::getType() {return 0;}
int Lexem::getValue(int a, int b) {return 0;}
int Lexem::getPriority() {return 0;}
void Lexem::print() { }
void Lexem::printArray() { }
string Lexem::getName() {return "";}
void Lexem::setRow(int row) { }
int Lexem::getRow() { }
int Lexem::inLabelsMap() { }
int Lexem::inFunctionsMap() { }
int Lexem::getIndex() { }
void Lexem::createArray(int _size) { }
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
		case LVALUE: cout << "[lvalue] "; break;
		case RVALUE: cout << "[rvalue] "; break;
		case LBRACKET: cout << "[ ( ] "; break;
		case RBRACKET: cout << "[ ) ] "; break;
		case IF: cout <<"[if] "; break;
		case THEN: cout <<"[then] "; break;
		case ELSE: cout <<"[else] "; break;
		case ENDIF: cout <<"[endif] "; break;
		case WHILE: cout <<"[while] "; break;
		case ENDWHILE: cout <<"[endwhile] "; break;
		case COLON: cout <<"[:] "; break;
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
		case PRINT: cout << "[print] "; break;
		case LSQUARE: cout << "[ [ ] "; break;
		case RSQUARE: cout << "[ ] ] "; break;
		case SIZE: cout << "[size] "; break;
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

int Variable::inFunctionsMap() {
	auto it = functionsMap.find(name);
	if (it == functionsMap.end())
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
	cout << "[GOTO<row " << row << ">" << OPERTEXT[this->getType()] << "] ";
}

ArrayElement::ArrayElement(string _name, int _index) {
	name = _name;
	index = _index;
	this->setType(ARRAY_ELEMENT);  
}

int ArrayElement::getIndex() {
	return index;
}

void ArrayElement::print() {
	cout << "[element of array " << name << "] ";
}

Array::Array(string _name) {
	name = _name;
	this->setType(ARRAY);
}

void Array::setValue(int index, int value) {
	data[index] = value;
}

Array::Array() {
	this->setType(ARRAY);
}

void Array::createArray(int _size) {
	size = _size;
	for (int i = 0; i < size; i++) {
		int element = 0;
		data.push_back(element);
	}
}

int Array::getValue(int _index) {
	return data[_index];
}

string ArrayElement::getName() {return name;}
 
string Array::getName() {return name;}

void Array::print() {
	cout << "[array " << name << " size " << size << "] ";
}

void Array::printArray() {
	for (int i = 0; i < size; i++)
		cout << name << "[" << i << "] = " << data[i] << endl;
}