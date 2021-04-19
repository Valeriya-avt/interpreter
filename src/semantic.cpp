#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "lexem.h"
#include "variables.h"

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
	 	tmp = new ArrayElement(computationStack.top()->getName(), computationStack.top()->getIndex(), computationStack.top()->getValue());
	}
	computationStack.pop(); 
	return tmp;
}

// void deleteVector(vector<Lexem *> &vectorOfLexemes) {
// 	for (int i = vectorOfLexemes.size() - 1; i >= 0; i--) {
// 		cout << "i = " << i << endl;
// 		if (vectorOfLexemes[i] == nullptr)
// 			continue;
// 		// if (vectorOfLexemes[i]->getLexType() == ARRAY_ELEMENT) {
// 		// 	continue;
// 		// }
// 		else {
// 			delete vectorOfLexemes[i];
// 		}
// 	}
// }

void deleteVector(vector<Lexem *> &vectorOfLexemes) {
	for (int i = 0; i < vectorOfLexemes.size(); ++i) {
		delete vectorOfLexemes[i];
	}
}

void clearStack(stack <Lexem *> &stackOfLexemes) {
	for (int i = 0; i < stackOfLexemes.size(); i++)
		stackOfLexemes.pop();
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
					for (j = i - 1; j >= 0; j--) {
						if (prevLocals.top().computationStack.top()->getLexType() == NUMBER)
							space.variablesMap[poliz[j]->getName()] = prevLocals.top().computationStack.top()->getValue();
						if (prevLocals.top().computationStack.top()->getLexType() == VARIABLE)
							space.variablesMap[poliz[j]->getName()] = prevLocals.top().variablesMap[prevLocals.top().computationStack.top()->getName()];
						prevLocals.top().computationStack.pop();
					}
					locals.push(space);
					clearStack(locals.top().computationStack);
					*index = 0;
					return functionsMap[poliz[i]->getName()];
				}
				returnIndex.push(i + 1);
				returnAddresses.push(row); //
				*index = 0;
				return functionsMap[poliz[i]->getName()] - 1;
			}
			continue;
		}
		if (poliz[i]->getLexType() == OPER) {
			Oper *lexemop = (Oper *)poliz[i];
			if (lexemop->getType() == ENDFUNCTION) {
				int rowNumber = returnAddresses.top();
				returnAddresses.pop();
				if (i != 0) {
					if (locals.top().computationStack.top()->getLexType() == VARIABLE) {
						int value = locals.top().variablesMap[locals.top().computationStack.top()->getName()];
						Number *num = new Number(value);
						recycle.push_back(num);
						prevLocals.top().computationStack.push(num);
					}
					if (locals.top().computationStack.top()->getLexType() == NUMBER) {
						prevLocals.top().computationStack.push(locals.top().computationStack.top());
					}
				}
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
				int size = locals.top().computationStack.top()->getValue();
				locals.top().computationStack.pop();
				locals.top().computationStack.top()->createArray(size);
				locals.top().arraysMap[locals.top().computationStack.top()->getName()] = (Array *)locals.top().computationStack.top();
				locals.top().computationStack.top()->print();
				locals.top().computationStack.pop();
				continue;
			}

			if (poliz[i]->getType() == RET) {
				break;
			}
			if (poliz[i]->getType() == PRINT) {
				if (poliz[i - 1]->getLexType() == VARIABLE)
					cout << "PRINT " << locals.top().variablesMap[poliz[i - 1]->getName()] << " ";
				else if (poliz[i - 3]->getLexType() == ARRAY_ELEMENT) {
					int index;
					if (poliz[i - 2]->getLexType() == VARIABLE)
						index = locals.top().variablesMap[poliz[i - 2]->getName()];
					else
						index = poliz[i - 2]->getValue(); 
					cout << "PRINT " << locals.top().arraysMap[poliz[i - 3]->getName()]->getValue(index)->getValue() << " ";
				}
				continue;
			}
			if (poliz[i]->getType() == LVALUE || poliz[i]->getType() == RVALUE) {
				int index;
				if (locals.top().computationStack.top()->getLexType() == VARIABLE)
					index = locals.top().variablesMap[locals.top().computationStack.top()->getName()];
				else
					index = locals.top().computationStack.top()->getValue();
				locals.top().computationStack.pop();
				string name = locals.top().computationStack.top()->getName();
				locals.top().computationStack.pop();
				if (poliz[i]->getType() == LVALUE) {
					ArrayElement *element = locals.top().arraysMap[name]->getValue(index);
					locals.top().computationStack.push(element);
				} else {
					int number = locals.top().arraysMap[name]->getValue(index)->getValue();
					Number *num = new Number(number);
					recycle.push_back(num);
					locals.top().computationStack.push(num);
				}
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
				right = new Number(locals.top().arraysMap[right->getName()]->getValue(right->getIndex())->getValue());
				recycle.push_back(right);
			}

			if (poliz[i]->getType() == ASSIGN) {
				if (left->getLexType() == VARIABLE) {
					locals.top().variablesMap[left->getName()] = right->getValue();
					Number *num = new Number(right->getValue());
					recycle.push_back(num);
					locals.top().computationStack.push(num);
				} else if (left->getLexType() == ARRAY_ELEMENT) {
					locals.top().arraysMap[left->getName()]->getValue(left->getIndex())->setValue(right->getValue());
					Number *num = new Number(right->getValue());
					recycle.push_back(num);
					locals.top().computationStack.push(num);
				}
			} else if (left != nullptr && left->getLexType() == VARIABLE) {
				left = new Number(locals.top().variablesMap[left->getName()]);
				recycle.push_back(left);
			} else if (left != nullptr && left->getLexType() == ARRAY_ELEMENT) {
				left = new Number(locals.top().arraysMap[left->getName()]->getValue(left->getIndex())->getValue());
				//left = new Number(arraysMap[right->getName()]->getValue(right->getIndex())->getValue());
				recycle.push_back(left);
			}
			if (right != nullptr && left != nullptr) {
				int value = poliz[i]->getValue(left->getValue(), right->getValue());
				Number *num = new Number(value);
				locals.top().computationStack.push(num);
				recycle.push_back(num);
			}
		}
	}
	clearStack(locals.top().computationStack);
	*index = 0;
	return row + 1;
}