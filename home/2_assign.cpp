#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

enum LEX_TYPE {
	NUMBER,
	OPER,
	VARIABLE
};

class Lexem {
	LEX_TYPE type;
public:
	Lexem() { };
	int getLexType() {return type;}
	void setType(LEX_TYPE type) {Lexem::type = type;}
	virtual int getType() { };
	virtual int getValue(int a = 1, int b = 1) { };
	virtual int getPriority() { }
	virtual void print() { }
	virtual string getName() { }
};

class Number: public Lexem {
	int value;
public:
	Number(int number);
	int getValue(int a = 1, int b = 1) {return value;}
	void print();
};

Number::Number(int number) {
	value = number;
	this->setType(NUMBER);
}

void Number::print() {
	cout << value << " ";
}

enum OPERATOR {
	LBRACKET, RBRACKET,
	ASSIGN,
	PLUS, MINUS,
	MULTIPLY
};

int PRIORITY[] = {
	-1, -1,
	0,
	1, 1,
	2
};

class Oper: public Lexem {
	OPERATOR opertype;
public:
	Oper(int charCode);
	int getType() {return opertype;}
	int getPriority() {return PRIORITY[opertype];}
	int getValue(int left = 1, int right = 1);
	void print();
};

Oper::Oper(int charCode = 0) {
	this->setType(OPER);
	switch(charCode) {
		case '(': opertype = LBRACKET; break;
		case ')': opertype = RBRACKET; break;
		case '+': opertype = PLUS; break;
		case '-': opertype = MINUS; break;
		case '*': opertype = MULTIPLY; break;
		case '=': opertype = ASSIGN; break;
	}
}

int Oper::getValue(int left, int right) {
	switch (this->getType()) {
		case PLUS: return left + right;
		case MINUS: return left - right;
		case MULTIPLY: return left * right;
		case ASSIGN: return right;
	}
}

void Oper::print() {
	switch (this->getType()) {
		case PLUS: cout << "+ "; break;
		case MINUS: cout << "- "; break;
		case MULTIPLY: cout << "* "; break;
		case ASSIGN: cout << "= "; break;
	}
}

class Variable: public Lexem {
	string name;
public:
	Variable(string str, int value = 0);
	void print();
	string getName() {return name;}
};

Variable::Variable(string str, int value) {
	name = str;
	this->setType(VARIABLE);
}

void Variable::print() {
	cout << name << " ";
}

std::map<std::string, int> m;

bool checkOperator(char ch) {
	return (ch == '+' || ch == '-' ||
			ch == '*' || ch == '=' ||
			ch == '(' || ch == ')');
}

bool checkVariable(char ch) {
	return ((ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			 ch == '_');
}

vector<Lexem *> parseLexem(string codeline) {
	vector<Lexem *> infix;
	int i, j, number = 0;
	for (i = 0; i < codeline.size(); ++i) {
		string tmp;
		number = 0;
		if (codeline[i] == ' ' || codeline[i] == '\n' || codeline[i] == '\t')
			continue;
		for (j = i; codeline[j] >= '0' && codeline[j] <= '9'; ++j) {
			number = number * 10 + codeline[j] - '0';
		}
		if (i != j) {
			Number *num = new Number(number);
			infix.push_back(num);
			i = j - 1;
		} else {
			if (checkOperator(codeline[i])) {
				Oper *op = new Oper(codeline[i]);
				infix.push_back(op);
			} else {
				for (j = i; checkVariable(codeline[j]) && j < codeline.size(); ++j) {
					tmp.insert(tmp.size(), 1, codeline[j]);
				}
				Variable *variable = new Variable(tmp);
				infix.push_back(variable);
				if (i != j)
					i = j - 1;
			}
		}
	}
	return infix;
}

bool checkBuild (int type, int prevPriority, int currentPriority) {
	return ((type == ASSIGN && prevPriority > currentPriority) || 
			(type != ASSIGN && prevPriority >= currentPriority));
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
					while (!opstack.empty() && checkBuild(infix[i]->getType(), 
						    opstack.top()->getPriority(), infix[i]->getPriority())) {
						postfix.push_back(opstack.top());
						opstack.pop();
					}
					opstack.push((Oper *)infix[i]);
				}
			}
		}
		if (infix[i]->getLexType() == VARIABLE) {
			postfix.push_back(infix[i]);
		//	if (m.count(infix[i]->getName()) == 0)
		//		m[infix[i]->getName()] = infix[i]->getValue();
		}
	}
	for (i = opstack.size(); i > 0; i--) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}

Lexem *checkForEvaluate(vector<Lexem *> poliz, stack<Lexem *> &computationStack) {
	Lexem *tmp;
	if (computationStack.top()->getLexType() == NUMBER) {
		tmp = new Number(computationStack.top()->getValue());
	} else {
		tmp = new Variable(computationStack.top()->getName());
	}
	computationStack.pop();
	return tmp;
}

int evaluatePostfix(vector<Lexem *> poliz) {
	int value;
	Lexem *left, *right;
	stack<Lexem *> computationStack;
	for (int i = 0; i < poliz.size(); i++) {
		if (poliz[i]->getLexType() == NUMBER || poliz[i]->getLexType() == VARIABLE) {
			computationStack.push(poliz[i]);
		}
		if (poliz[i]->getLexType() == OPER) {
			right = checkForEvaluate(poliz, computationStack);
			left = checkForEvaluate(poliz, computationStack);
			if (poliz[i]->getType() == ASSIGN) {
				if (right->getLexType() == VARIABLE) {
					right = new Number(m[right->getName()]);
				}
				m[left->getName()] = right->getValue();
				Number *num = new Number(right->getValue());
				computationStack.push(num);
			} else {
				if (right->getLexType() == VARIABLE) {
					right = new Number(m[right->getName()]);
				}
				if (left->getLexType() == VARIABLE) {
					left = new Number(m[left->getName()]);
				}
				value = poliz[i]->getValue(left->getValue(), right->getValue());
				Number *num = new Number(value);
				computationStack.push(num);
			}
		}
	}
	return computationStack.top()->getValue();
}

int main() {
	string codeline;
	vector<Lexem *> infix;
	vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix = parseLexem(codeline);
		postfix = buildPostfix(infix);
		cout << "Postfix: ";
		for (int i = 0; i < postfix.size(); ++i) {
			postfix[i]->print();
		}
		cout << '\n';
		value = evaluatePostfix(postfix);
		cout << "Result: " << value << '\n';
		cout << "Variable map:\n";
		for (auto it = m.begin(); it != m.end(); ++it)
			cout << (*it).first << " = " << (*it).second << endl;
		cout << endl;
	}
	return 0;
}