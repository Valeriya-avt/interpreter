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
	int getLexType() {return type;}
	virtual int getType() { };
	virtual int getValue(int a = 1, int b = 1) { };
};

class Number: public Lexem {
	int value;
public:
	Number(int number);
	int getValue(int, int);
};

Number::Number(int number) {
	value = number;
	type = NUMBER;
}

int Number::getValue(int a = 1, int b = 1) {
//	cout << "num_get_value\n";
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
	int getType();
	int getPriority();
	int getValue(int left, int right);
};

Oper::Oper(int charCode = 0) {
	type = OPER;
	switch(charCode) {
		case '(': opertype = LBRACKET; break;
		case ')': opertype = RBRACKET; break;
		case '+': cout << PLUS << endl; opertype = PLUS; break;
		case '-': opertype = MINUS; break;
		case '*': opertype = MULTIPLY; break;
	}
}

int Oper::getType() {
	return opertype;
}

int Oper::getPriority() {
	return PRIORITY[opertype - 1];
}

int Oper::getValue(int left = 1, int right = 1) {
	switch (this->getType()) {
		case PLUS: return left + right;
		case MINUS: return left - right;
		case MULTIPLY: return left * right;
	}
}

int getValue(int type, int left, int right) {
//	cout << "getValue\n";
//	cout << type << PLUS << endl;
	switch (type) {
		case PLUS: cout << "PLUS\n"; return left + right;
		case MINUS: cout << "MINUS\n"; return left - right;
		case MULTIPLY: cout << "MULTIPLY\n"; return left * right;
	}
}

vector<Lexem *> parseLexem(string codeline) {
	vector<Lexem *> infix;
	int i, j, number = 0;
	for (i = 0; i < codeline.size(); ++i) {
		number = 0;
		for (j = i; codeline[j] >= '0' && codeline[j] <= '9'; ++j) {
			number = number * 10 + codeline[j] - '0';
		}
		if (i != j) {
			Number *num = new Number(number);
			infix.push_back(num);
	//		cout << "num == " << number << endl;
			i = j - 1;
		} else {
			if (codeline[i] != ' ' && codeline[i] != '\t' && codeline[i] != '\n') {
				Oper *op = new Oper(codeline[i]);
	//			cout << "op == " << codeline[i] << endl;
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
		if (infix[i]->getLexType() == NUMBER) {
			postfix.push_back(infix[i]);
	//		cout << "IS_NUMBER\n";
		}
		if (infix[i]->getLexType() == OPER) {
			opstack.push((Oper *)infix[i]);
	//		cout << "IS_OPER\n";
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
		if (poliz[i]->getLexType() == OPER) {
		//	cout << poliz[i - 2]->getValue() << " " << poliz[i - 2]->getValue() << endl;
		//	value = getValue(poliz[i]->getType(), poliz[i - 2]->getValue(), poliz[i - 1]->getValue());
			value = poliz[i]->getValue(poliz[i - 2]->getValue(), poliz[i - 1]->getValue());
		}
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