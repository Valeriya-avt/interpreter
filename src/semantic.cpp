#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "lexem.h"

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

void deleteVector(vector<Lexem *> vectorOfLexemes) {
	for (int i = 0; i < vectorOfLexemes.size(); ++i) {
		delete vectorOfLexemes[i];
	}
}

int evaluatePostfix(vector<Lexem *> &poliz) {
	int value;
	Lexem *left, *right;
	stack<Lexem *> computationStack;
	vector <Lexem *> recycle;
	for (int i = 0; i < poliz.size(); i++) {
		if (poliz[i]->getLexType() == NUMBER || poliz[i]->getLexType() == VARIABLE) {
			computationStack.push(poliz[i]);
		}
		if (poliz[i]->getLexType() == OPER) {
			right = checkForEvaluate(poliz, computationStack);
			left = checkForEvaluate(poliz, computationStack);
			recycle.push_back(right);
			recycle.push_back(left);
			if (right->getLexType() == VARIABLE) {
				right = new Number(variableMap[right->getName()]);
				recycle.push_back(right);
			}
			if (poliz[i]->getType() == ASSIGN) {
				variableMap[left->getName()] = right->getValue();
				Number *num = new Number(right->getValue());
				recycle.push_back(num);
				computationStack.push(num);
			} else if (left->getLexType() == VARIABLE) {
				left = new Number(variableMap[left->getName()]);
				recycle.push_back(left);
			}
				value = poliz[i]->getValue(left->getValue(), right->getValue());
				Number *num = new Number(value);
				computationStack.push(num);
				recycle.push_back(num);
		}
	}
	deleteVector(recycle);
	return value;
}