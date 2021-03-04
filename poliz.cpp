#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

enum LEX_TYPE {
	NUMBER,
	OPER
};

class Lexem {
public:
	LEX_TYPE type;
	Lexem() { };
	int getType() {return type;}
	virtual int getValue() { };
};

class Number: public Lexem {
	int value;
public:
	Number(int number);
	int getValue() const;
};

Number::Number(int number) {
	value = number;
	type = NUMBER;
}

int Number::getValue() const {
	return value;
}

enum OPERATOR {
	LBRACKET, RBRACKET,
	PLUS, MINUS,
	MULTIPLY
};

int PRIORITY[] = {
	-1, -1,
	0, 0,
	1
};

class Oper: public Lexem {
	OPERATOR opertype;
public:
	Oper(int charCode);
	OPERATOR getType();
	int getPriority();
	int getValue(int left, int right);
};

Oper::Oper(int charCode = 0) {
	type = OPER;
	switch(charCode) {
		case '(': opertype = LBRACKET; break;
		case ')': opertype = RBRACKET; break;
		case '+': opertype = PLUS; break;
		case '-': opertype = MINUS; break;
		case '*': opertype = MULTIPLY; break;
	}
}

OPERATOR Oper::getType() {
	return opertype;
}

int Oper::getPriority() {
	return PRIORITY[opertype];
}

int Oper::getValue(int left, int right) {
	switch (this->getType()) {
		case PLUS: return left + right;
		case MINUS: return left - right;
		case MULTIPLY: return left * right;
	}
}

int getValue(int type, int left, int right) {
	switch (type) {
		case PLUS: return left + right;
		case MINUS: return left - right;
		case MULTIPLY: return left * right;
	}
}

vector<Lexem *> parseLexem(string codeline) {
	vector<Lexem *> infix;
	int i, j, number = 0;
	for (i = 0; i < codeline.size(); i++) {
		number = 0;
		for (j = i; codeline[j] >= 0 && codeline[j] <= '9'; j++) {
			number = number * 10 + codeline[j] - '0';
		}
		if (i != j) {
			Number *num = new Number(number);
			infix.push_back(num);
			i = j;
		}
		else {
			if (codeline[i] != ' ' && codeline[i] != '\t') {
				Oper *op = new Oper(codeline[i]);
				infix.push_back(op);
			}
		}
	}
	return infix;
}

vector<Lexem *> buildPostfix(vector<Lexem *> infix) {
	stack<Oper *> opstack;
	vector<Lexem *> postfix;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i]->getType() == NUMBER)
			postfix.push_back(infix[i]);
		if (infix[i]->getType() == OPER) {
			opstack.push((Oper *)infix[i]);
		}
	}
	for (int i = opstack.size() - 1; i >= 0; i--) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}

int evaluatePostfix(vector<Lexem *> poliz) {
	int value;
	for (int i = 0; i < poliz.size(); i++) {
		if (poliz[i]->getType() == OPER)
			value = getValue(poliz[i]->getType(), poliz[i - 2]->getValue(), poliz[i - 1]->getValue());
	}
	return value;
}

int main() {
	string codeline;
	vector<Lexem *> infix;
	vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix = parseLexem(codeline);
		postfix = buildPostfix(infix);
		value = evaluatePostfix(postfix);
		cout << value << endl;
	}
}