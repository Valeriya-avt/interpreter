#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "lexem.h"

Lexem *checkForEvaluate(vector<Lexem *> &poliz, stack<Lexem *> &computationStack) {
	Lexem *tmp = nullptr;
	if (!computationStack.empty() && computationStack.top() != nullptr && 
		computationStack.top()->getLexType() == NUMBER) {
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
			Oper *lexemop = (Oper *)poliz[i];
			if (lexemop->getType() == GOTO || lexemop->getType() == ELSE || 
				lexemop->getType() == ENDWHILE) {
				Goto *lexemgoto = (Goto *)lexemop;
				*row = lexemgoto->getRow();
				deleteVector(recycle);
				return *row;
			}
			// if (poliz[i]->getType() == GOTO || poliz[i]->getType() == ELSE || 
			// 	poliz[i]->getType() == ENDWHILE) {
			// 	*row = poliz[i]->getRow();
			// 	deleteVector(recycle);
			// 	return *row;
			// }
			// if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
			// 	if (!(computationStack.empty()) && computationStack.top() != nullptr &&
			// 		computationStack.top()->getValue() == 1) {
			// 		computationStack.pop();
			// 		*row = poliz[i]->getRow();
			// 		deleteVector(recycle);
			// 		return *row;
			// 	}
			// 	computationStack.pop();
			// }
			if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
					Goto *lexemgoto = (Goto *)lexemop;
					int rvalue = computationStack.top()->getValue();
					computationStack.pop();
					deleteVector(recycle);
					if (!rvalue) {
						*row = lexemgoto->getRow();
						return *row;
					} else {
						*row = *row + 1;
						return *row;
					}
			}
			right = checkForEvaluate(poliz, computationStack);
			left = checkForEvaluate(poliz, computationStack);
			if (right != nullptr)
				recycle.push_back(right);
			if (left != nullptr)
				recycle.push_back(left);
			if (right != nullptr && right->getLexType() == VARIABLE) {
				right = new Number(variablesMap[right->getName()]);
				recycle.push_back(right);
			}
			if (poliz[i]->getType() == ASSIGN) {
				variablesMap[left->getName()] = right->getValue();
				Number *num = new Number(right->getValue());
				recycle.push_back(num);
				computationStack.push(num);
			} else if (left != nullptr && left->getLexType() == VARIABLE) {
				left = new Number(variablesMap[left->getName()]);
				recycle.push_back(left);
			}
			if (right != nullptr && left != nullptr) {
				value = poliz[i]->getValue(left->getValue(), right->getValue());
				Number *num = new Number(value);
				computationStack.push(num);
				recycle.push_back(num);
			}
		}
	}
	deleteVector(recycle);
	*row = *row + 1;
	return value;
}