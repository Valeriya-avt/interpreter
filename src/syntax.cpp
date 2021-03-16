#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "lexem.h"

bool checkBuild(int type, int prevPriority, int currentPriority) {
	return ((type == ASSIGN && prevPriority > currentPriority) || 
			(type != ASSIGN && prevPriority >= currentPriority));
}

vector<Lexem *> buildPostfix(vector<Lexem *> &infix) {
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
			} else if (infix[i]->getType() == RBRACKET) {
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
		if (infix[i]->getLexType() == VARIABLE) {
			postfix.push_back(infix[i]);
		//	if (variableMap.count(infix[i]->getName()) == 0)
		//		variableMap[infix[i]->getName()] = infix[i]->getValue();
		}
	}
	for (i = opstack.size(); i > 0; i--) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}