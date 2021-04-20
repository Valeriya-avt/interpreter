#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "lexem.h"
#include "variables.h"

bool checkBuild(int type, int prevPriority, int currentPriority) {
	return (((type == ASSIGN) && prevPriority > currentPriority) || 
			(type != ASSIGN && type != LVALUE && type != RVALUE && prevPriority >= currentPriority));
}

void joinGotoAndLabel(Variable *lexemvar, stack<Oper *> &opstack) {
	if (!opstack.empty() && opstack.top() != nullptr && opstack.top()->getType() == GOTO) {
		Goto *lexemgoto = (Goto*)opstack.top();
		lexemgoto->setRow(labelsMap[lexemvar->getName()]);
	}
}

vector<Lexem *> buildPostfix(const vector<Lexem *> &infix) {
	int i, j;
	stack<Oper *> opstack;
	stack<Variable *> functionsStack;
	vector<Lexem *> postfix;
	for (i = 0; i < infix.size(); i++) {
		cout << "i = " << i << endl;
		if (infix[i] == nullptr) {
			continue;
		}
		if (infix[i]->getLexType() == NUMBER || infix[i]->getLexType() == ARRAY || infix[i]->getLexType() == ARRAY_ELEMENT) {
			postfix.push_back(infix[i]);
			continue;
		}
		if (infix[i]->getLexType() == OPER) {
			if (infix[i]->getType() == ENDIF || infix[i]->getType() == THEN)
				continue;
			if (infix[i]->getType() == LBRACKET) {
				opstack.push((Oper *)infix[i]);
			} else if (infix[i]->getType() == RBRACKET || infix[i]->getType() == RSQUARE) {
				for (j = opstack.size(); j > 0 && !opstack.empty() && opstack.top()->getType() != LBRACKET; j--) {
					int type = opstack.top()->getType();
					postfix.push_back(opstack.top());
					opstack.pop();
					if (type == LVALUE || type == RVALUE) {
						break;
					}
				}
				if (infix[i]->getType() == RBRACKET && !functionsStack.empty()) {
					postfix.push_back(functionsStack.top());
					functionsStack.pop();
				}
				if (!opstack.empty() && opstack.top()->getType() == LBRACKET)
					opstack.pop();
			} else {
				while (!opstack.empty() && checkBuild(infix[i]->getType(), 
					    opstack.top()->getPriority(), infix[i]->getPriority())) {
					int type = opstack.top()->getType();
					postfix.push_back(opstack.top());
					opstack.pop();
				}
				opstack.push((Oper *)infix[i]);
			}
		}
		if (infix[i]->getLexType() == VARIABLE) {
			if (infix[i]->inLabelsMap())
				joinGotoAndLabel((Variable *)infix[i], opstack);
			else if (!infix[i]->inFunctionsMap())
				postfix.push_back(infix[i]);
			if (infix[i]->inFunctionsMap())
				functionsStack.push((Variable *)infix[i]);
		}
	}
	for (i = opstack.size(); i > 0; i--) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}