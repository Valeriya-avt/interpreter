#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include <lexem.h>
#include <variables.h>

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

bool processOper(Lexem *lexem, vector<Lexem *> &postfix, stack<Oper *> &opstack, 
                 stack<Variable *> &functionsStack) {
	if (lexem->getType() == ENDIF || lexem->getType() == THEN || lexem->getType() == GLOBAL)
		return false;
	if (lexem->getType() == LBRACKET) {
		opstack.push((Oper *)lexem);
	} else if (lexem->getType() == RBRACKET || lexem->getType() == RSQUARE) {
		while (!opstack.empty() && opstack.top()->getType() != LBRACKET) {
			int type = opstack.top()->getType();
			postfix.push_back(opstack.top());
			opstack.pop();
			if (type == LVALUE || type == RVALUE)
				break;
		}
		if (lexem->getType() == RBRACKET && !functionsStack.empty()) {
			postfix.push_back(functionsStack.top());
			functionsStack.pop();
		}
		if (!opstack.empty() && opstack.top()->getType() == LBRACKET)
			opstack.pop();
	} else {
		while (!opstack.empty() && checkBuild(lexem->getType(), 
			    opstack.top()->getPriority(), lexem->getPriority())) {
			int type = opstack.top()->getType();
			postfix.push_back(opstack.top());
			opstack.pop();
		}
		opstack.push((Oper *)lexem);
	}
	return true;
}

vector<Lexem *> buildPostfix(const vector<Lexem *> &infix) {
	stack<Oper *> opstack;
	stack<Variable *> functionsStack;
	vector<Lexem *> postfix;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == nullptr)
			continue;
		if (infix[i]->getLexType() == NUMBER || infix[i]->getLexType() == ARRAY || infix[i]->getLexType() == ARRAY_ELEMENT) {
			postfix.push_back(infix[i]);
			continue;
		}
		if (infix[i]->getLexType() == OPER) {
			if (!processOper(infix[i], postfix, opstack, functionsStack))
				continue;
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
	for (int i = opstack.size(); i > 0; i--) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}