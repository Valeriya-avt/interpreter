#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "lexem.h"

Lexem *checkForEvaluate(vector<Lexem *> &poliz, stack<Lexem *> &computationStack) {
	Lexem *tmp;
	if (computationStack.top()->getLexType() == NUMBER) {
		tmp = new Number(computationStack.top()->getValue());
	} else {
		tmp = new Variable(computationStack.top()->getName());
	}
	computationStack.pop();
	return tmp;
}

void deleteVector(vector<Lexem *> &vectorOfLexemes) {
	for (int i = 0; i < vectorOfLexemes.size(); ++i) {
		delete vectorOfLexemes[i];
	}
}

void initLabels(vector<Lexem *> &infix, int row) {
	for (int i = 1; i < infix.size(); i++) {
		if (infix[i - 1]->getLexType() == VARIABLE && infix[i]->getLexType() == OPER) {
			Variable *lexemvar = (Variable *)infix[i - 1];
			Oper *lexemop = (Oper *)infix[i];
			if (lexemop->getType() == COLON) {
				varsAndLabelsMap[lexemvar->getName()] = row;
				delete infix[i - 1];
				delete infix[i];
				infix[i - 1] = nullptr;
				infix[i] = nullptr;
				i++;
			}
		}
	}
}

int evaluatePostfix(vector<Lexem *> &poliz, int *row) {
	int value;
	Lexem *left, *right;
	stack<Lexem *> computationStack;
	vector <Lexem *> recycle;
	for (int i = 0; i < poliz.size(); i++) {
		if (poliz[i]->getLexType() == NUMBER || poliz[i]->getLexType() == VARIABLE) {
			computationStack.push(poliz[i]);
		}
		if (poliz[i]->getLexType() == OPER) {
			if (poliz[i]->getType() == GOTO) {
			//	cout << "poliz[i]->getRow() == " << poliz[i]->getRow() << endl;
				*row = poliz[i]->getRow();
				return poliz[i]->getRow();
			}
			right = checkForEvaluate(poliz, computationStack);
			left = checkForEvaluate(poliz, computationStack);
			recycle.push_back(right);
			recycle.push_back(left);
			if (right->getLexType() == VARIABLE) {
				right = new Number(varsAndLabelsMap[right->getName()]);
				recycle.push_back(right);
			}
			if (poliz[i]->getType() == ASSIGN) {
				varsAndLabelsMap[left->getName()] = right->getValue();
				Number *num = new Number(right->getValue());
				recycle.push_back(num);
				computationStack.push(num);
			} else if (left->getLexType() == VARIABLE) {
				left = new Number(varsAndLabelsMap[left->getName()]);
				recycle.push_back(left);
			}
				value = poliz[i]->getValue(left->getValue(), right->getValue());
				Number *num = new Number(value);
				computationStack.push(num);
				recycle.push_back(num);
		}
	}
	deleteVector(recycle);
	*row = *row + 1;
	return value;
}