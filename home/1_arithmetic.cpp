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
	virtual int getPriority() { }
	virtual void print() { }
};

class Number: public Lexem {
	int value;
public:
	Number(int number);
	int getValue(int, int);
	void print() {cout << value << " ";}
};

Number::Number(int number) {
	value = number;
	type = NUMBER;
}

int Number::getValue(int a = 1, int b = 1) {
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
	void print();
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
	return PRIORITY[opertype];
}

int Oper::getValue(int left = 1, int right = 1) {
	switch (this->getType()) {
		case PLUS: return left + right;
		case MINUS: return left - right;
		case MULTIPLY: return left * right;
	}
}

void Oper::print() {
	switch (this->getType()) {
		case PLUS: cout << "+ "; break;
		case MINUS: cout << "- "; break;
		case MULTIPLY: cout << "* "; break;
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
			i = j - 1;
		} else {
			if (codeline[i] != ' ' && codeline[i] != '\t' && codeline[i] != '\n') {
				Oper *op = new Oper(codeline[i]);
				infix.push_back(op);
			}
		}
	}
	return infix;
}

vector<Lexem *> buildPostfix(vector<Lexem *> infix) {
	int i, j;
	stack<Oper *> opstack;
	vector<Lexem *> postfix;
	for (i = 0; i < infix.size(); i++) {
		if (infix[i]->getLexType() == NUMBER) {
			postfix.push_back(infix[i]);
		}
		if (infix[i]->getLexType() == OPER) {
			if (infix[i]->getType() == LBRACKET) {
				opstack.push((Oper *)infix[i]);
			} else {
				if (infix[i]->getType() == RBRACKET) {
					for (j = opstack.size(); j > 0 && opstack.top()->getType() != LBRACKET; j--) {
						postfix.push_back(opstack.top());
						opstack.pop();
					}
					opstack.pop();
				} else {
					while (!opstack.empty() && opstack.top()->getPriority() > infix[i]->getPriority()) {
						postfix.push_back(opstack.top());
						opstack.pop();
					}
					opstack.push((Oper *)infix[i]);
				}
			}
		}
	}
	for (i = opstack.size(); i > 0; i--) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}

int evaluatePostfix(vector<Lexem *> poliz) {
	int value, left, right;
	stack<int> computationStack;
	for (int i = 0; i < poliz.size(); i++) {
		if (poliz[i]->getLexType() == NUMBER) {
			computationStack.push(poliz[i]->getValue());
		}
		if (poliz[i]->getLexType() == OPER) {
			right = computationStack.top();
			computationStack.pop();
			left = computationStack.top();
			computationStack.pop();
			value = poliz[i]->getValue(left, right);
			computationStack.push(value);
		}
	}
	return computationStack.top();
}

int main() {
	string codeline;
	vector<Lexem *> infix;
	vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix = parseLexem(codeline);
		postfix = buildPostfix(infix);
		for (int i = 0; i < postfix.size(); ++i) {
			postfix[i]->print();
		}
		cout << '\n';
		value = evaluatePostfix(postfix);
		cout << "Answer: " << value << endl;
	}
}