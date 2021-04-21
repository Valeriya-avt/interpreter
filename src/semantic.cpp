#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "lexem.h"
#include "variables.h"
#include "print.h"

Lexem *checkForEvaluate(vector<Lexem *> &poliz, stack<Lexem *> &computationStack) {
	Lexem *tmp = nullptr;
	if (!computationStack.empty() && computationStack.top() != nullptr && 
		computationStack.top()->getLexType() == NUMBER) {
		tmp = new Number(computationStack.top()->getValue());
	} else if (!computationStack.empty() && computationStack.top() != nullptr && 
		computationStack.top()->getLexType() == VARIABLE) {
		tmp = new Variable(computationStack.top()->getName());
	} else if (!computationStack.empty() && computationStack.top() != nullptr && 
		computationStack.top()->getLexType() == ARRAY_ELEMENT) {
	 	tmp = new ArrayElement(computationStack.top()->getName(), computationStack.top()->getIndex());
	}
	computationStack.pop();  
	return tmp;
}

void deleteVector(vector<Lexem *> &vectorOfLexemes) {
	for (int i = 0; i < vectorOfLexemes.size(); ++i) {
		delete vectorOfLexemes[i];
	}
}

void clearStack(stack <Lexem *> &stackOfLexemes) {
	for (int i = 0; i < stackOfLexemes.size(); i++)
		stackOfLexemes.pop();
}

int inMap(string name, map<std::string, Array *> lexemsMap) {
	auto it = lexemsMap.find(name);
	if (it == lexemsMap.end())
		return 0;
	else
		return 1;
}

void takeArguments(vector<Lexem *> &poliz, Space &space, stack<Lexem *> &computationStack, int pos) {
	for (int j = pos - 1; j >= 0; j--) {
		string name = computationStack.top()->getName();
		int index = poliz[pos]->getIndex();
		int type = computationStack.top()->getLexType();
		if (type == ARRAY_ELEMENT)
			space.variablesMap[poliz[j]->getName()] = prevLocals.top().arraysMap[name]->getValue(index);
		if (type == NUMBER)
			space.variablesMap[poliz[j]->getName()] = computationStack.top()->getValue();
		if (type == VARIABLE && !inMap(name, prevLocals.top().arraysMap))
			space.variablesMap[poliz[j]->getName()] = prevLocals.top().variablesMap[name];
		else if (inMap(name, prevLocals.top().arraysMap))
			space.arraysMap[poliz[j]->getName()] = prevLocals.top().arraysMap[name];
		computationStack.pop();
	}
}



void returnValue(stack<Lexem *> &computationStack) {
	if (computationStack.top()->getLexType() == VARIABLE) {
		int value = locals.top().variablesMap[computationStack.top()->getName()];
		Number *num = new Number(value);
		recycle.push_back(num);
		prevLocals.top().computationStack.push(num);
	}
	if (computationStack.top()->getLexType() == NUMBER) {
		prevLocals.top().computationStack.push(computationStack.top());
	}
	if (computationStack.top()->getLexType() == ARRAY_ELEMENT) {
		int index = computationStack.top()->getIndex();
		int value = locals.top().arraysMap[computationStack.top()->getName()]->getValue(index);
		Number *num = new Number(value);
		recycle.push_back(num);
		prevLocals.top().computationStack.push(num);
	}
}


void addArrayElement(Lexem *lexem, stack<Lexem *> &computationStack) {
	int index;
	if (computationStack.top()->getLexType() == VARIABLE)
		index = locals.top().variablesMap[computationStack.top()->getName()];
	else
		index = computationStack.top()->getValue();
	computationStack.pop();
	string name = computationStack.top()->getName();
	computationStack.pop();
	if (lexem->getType() == LVALUE) {
		ArrayElement *element = new ArrayElement(name, index);
		recycle.push_back(element);
		computationStack.push(element);
	} else {
		int number = locals.top().arraysMap[name]->getValue(index);
		Number *num = new Number(number);
		recycle.push_back(num);
		computationStack.push(num);
	}
}

void processAssign(Lexem *left, Lexem *right) {
	if (left->getLexType() == VARIABLE) {
		locals.top().variablesMap[left->getName()] = right->getValue();
		Number *num = new Number(right->getValue());
		recycle.push_back(num);
		locals.top().computationStack.push(num);
	} else if (left->getLexType() == ARRAY_ELEMENT) {
		locals.top().arraysMap[left->getName()]->setValue(left->getIndex(), right->getValue());
		Number *num = new Number(right->getValue());
		recycle.push_back(num);
		locals.top().computationStack.push(num);
	}
}


void evaluateExpression(Lexem *lexem, Lexem *left, Lexem *right) {
	if (left != nullptr && left->getLexType() == VARIABLE) {
		left = new Number(locals.top().variablesMap[left->getName()]);
		recycle.push_back(left);
	} else if (left != nullptr && left->getLexType() == ARRAY_ELEMENT) {
		left = new Number(locals.top().arraysMap[left->getName()]->getValue(left->getIndex()));
		recycle.push_back(left);
	}
	if (right != nullptr && left != nullptr) {
		int value = lexem->getValue(left->getValue(), right->getValue());
		Number *num = new Number(value);
		locals.top().computationStack.push(num);
		recycle.push_back(num);
	}
}


void createArray() {
	int size = locals.top().computationStack.top()->getValue();
	locals.top().computationStack.pop();
	locals.top().computationStack.top()->createArray(size);
	string name = locals.top().computationStack.top()->getName();
	locals.top().arraysMap[name] = (Array *)locals.top().computationStack.top();
	locals.top().computationStack.pop();
}


int evaluatePostfix(vector<Lexem *> &poliz, int row, int *index) {
	int i, j;
	Lexem *left, *right;
	Space prevSpace = locals.top();
	for (i = *index; i < poliz.size(); i++) {
		if (poliz[i]->getLexType() == NUMBER || poliz[i]->getLexType() == VARIABLE || 
			poliz[i]->getLexType() == ARRAY || poliz[i]->getLexType() == ARRAY_ELEMENT) {
			locals.top().computationStack.push(poliz[i]);
			if (poliz[i]->getLexType() == VARIABLE && poliz[i]->inFunctionsMap()) {
				if (poliz[poliz.size() - 1]->getLexType() == OPER && poliz[poliz.size() - 1]->getType() == FUNCTION) {
					prevLocals.push(prevSpace);
					Space space;
					prevLocals.top().computationStack.pop();

					takeArguments(poliz, space, prevLocals.top().computationStack, i);

					locals.push(space);
					clearStack(locals.top().computationStack);
					*index = 0;
					return functionsMap[poliz[i]->getName()];
				}
				returnIndex.push(i + 1);
				returnAddresses.push(row);
				*index = 0;
				return functionsMap[poliz[i]->getName()] - 1;
			}
			continue;
		}
		if (poliz[i]->getLexType() == OPER) {
			Oper *lexemop = (Oper *)poliz[i];
			if (lexemop->getType() == RETURN) {
				if (returnAddresses.empty())
					return row + 1;
				int rowNumber = returnAddresses.top();
				returnAddresses.pop();
				if (i != 0)
					returnValue(locals.top().computationStack);
				locals.pop();
				locals.pop();
				locals.push(prevLocals.top());
				prevLocals.pop();
				*index = returnIndex.top();
				returnIndex.pop();
				return rowNumber;
			}
			if (lexemop->getType() == GOTO || lexemop->getType() == ELSE || 
				lexemop->getType() == ENDWHILE) {
				Goto *lexemgoto = (Goto *)lexemop;
				clearStack(locals.top().computationStack);
				*index = 0;
				return lexemgoto->getRow();
			}
			if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
				Goto *lexemgoto = (Goto *)lexemop;
				int rvalue = locals.top().computationStack.top()->getValue();
				locals.top().computationStack.pop();
				if (!rvalue) {
					clearStack(locals.top().computationStack);
					*index = 0;
					return lexemgoto->getRow();
				} else {
					clearStack(locals.top().computationStack);
					*index = 0;
					return row + 1;
				}
			}
			if (poliz[i]->getType() == SIZE) {
				createArray();
				continue;
			}
			if (poliz[i]->getType() == PRINT) {
				print(poliz, i);
				continue;
			}
			if (poliz[i]->getType() == LVALUE || poliz[i]->getType() == RVALUE) {
				addArrayElement(poliz[i], locals.top().computationStack);
				continue;
			}
			right = checkForEvaluate(poliz, locals.top().computationStack);
			left = checkForEvaluate(poliz, locals.top().computationStack);
			recycle.push_back(right);
			recycle.push_back(left);
			if (right != nullptr && right->getLexType() == VARIABLE) {
				right = new Number(locals.top().variablesMap[right->getName()]);
				recycle.push_back(right);
			}
			if (right != nullptr && right->getLexType() == ARRAY_ELEMENT) {
				right = new Number(locals.top().arraysMap[right->getName()]->getValue(right->getIndex()));
				recycle.push_back(right);
			}
			if (poliz[i]->getType() == ASSIGN)
				processAssign(left, right);
			else
				evaluateExpression(poliz[i], left, right); 
		}
	}
	clearStack(locals.top().computationStack);
	*index = 0;
	return row + 1;
}