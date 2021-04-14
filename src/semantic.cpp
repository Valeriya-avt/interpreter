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

int evaluatePostfix(vector<Lexem *> &poliz, int *row) {
	int value;
	Lexem *left, *right;
	stack<Lexem *> computationStack;
	vector <Lexem *> recycle;
	for (int i = 0; i < poliz.size(); i++) {
		cout << "i = " << i << endl;
		if (poliz[i]->getLexType() == NUMBER || poliz[i]->getLexType() == VARIABLE || 
			poliz[i]->getLexType() == ARRAY || poliz[i]->getLexType() == ARRAY_ELEMENT) {
			cout << "IT'S ARRAY_ELEMENT1\n";
			if (poliz[i] == nullptr)
				cout << "IT'S NULLPTR\n";
			else
				cout << poliz[i]->getValue() << endl;
			//poliz[i]->print();
			computationStack.push(poliz[i]);
			cout << "IT'S ARRAY_ELEMENT2\n";
			continue;
			//poliz[i]->print();
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

			if (poliz[i]->getType() == SIZE) {
			//	cout << "IT'S SIZE1\n";
				int size = computationStack.top()->getValue();
				cout << "size = " << size << endl;
				computationStack.pop();
			//	cout << "IT'S SIZE2\n";
			//	cout << computationStack.top()->getLexType() << " " << ARRAY_ELEMENT << endl;
				computationStack.top()->createArray(size);
				arraysMap[computationStack.top()->getName()] = (Array *)computationStack.top();
			//	cout << "IT'S SIZE3\n";
				computationStack.top()->print();
			//	cout << "IT'S SIZE4\n";
				computationStack.pop();
			//	cout << "IT'S SIZE5\n";
				continue;
			}

			if (poliz[i]->getType() == RET) {
				break;
			}
			if (poliz[i]->getType() == PRINT) {
				cout << variablesMap[poliz[i - 1]->getName()] << " ";
				continue;
			}

			if (poliz[i]->getType() == LVALUE) {
				cout << "IT'S LVALUE\n";
				
				int index = computationStack.top()->getValue();
				computationStack.pop();
				//cout << "hey1\n";
				string name = computationStack.top()->getName();
				//cout << "hey2\n";
				computationStack.pop();
				//cout << "hey3\n";
				ArrayElement *element = arraysMap[name]->getValue(index);
				//cout << "hey4\n";
				//recycle.push_back(element);
				computationStack.push(element);
				//cout << "hey5\n";
				continue;
			}
			// if (poliz[i]->getType() == RVALUE) {
			// 	string name = computationStack.top()->getName();
			// 	computationStack.pop();
			// 	int index = computationStack.top()->getValue();
			// 	computationStack.pop();
			// 	int number = arraysMap[name]->getValue(index)->getValue();
			// 	Number *num = new Number(number);
			// 	recycle.push_back(num);
			// 	computationStack.push(num);
			// }

			if (poliz[i]->getType() == RVALUE) {
				int index = computationStack.top()->getValue();
				computationStack.pop();
				string name = computationStack.top()->getName();
				computationStack.pop();
				int number = arraysMap[name]->getValue(index)->getValue();
				Number *num = new Number(number);
				recycle.push_back(num);
				computationStack.push(num);
				continue;
			}

			right = checkForEvaluate(poliz, computationStack);
			left = checkForEvaluate(poliz, computationStack);
			//if (right != nullptr)
				recycle.push_back(right);
			//if (left != nullptr)
				recycle.push_back(left);
			if (right != nullptr && right->getLexType() == VARIABLE) {
				right = new Number(variablesMap[right->getName()]);
				recycle.push_back(right);
			}
			if (right != nullptr && right->getLexType() == ARRAY_ELEMENT) {
				right = new Number(arraysMap[right->getName()]->getValue(right->getIndex())->getValue());
				recycle.push_back(right);
			}
			// if (poliz[i]->getType() == ASSIGN) {
			// 	cout << "IT'S ASSING\n";
			// 	if (left->getLexType() == VARIABLE)
			// 		left = new Number(variablesMap[left->getName()]);

			// 	if (left->getLexType() == ARRAY_ELEMENT) {
			// 		//cout << "IT'S ASSING FOR ARRAY_ELEMENT1\n";
			// 		left = new Number(arraysMap[left->getName()]->getValue(left->getIndex())->getValue());//
			// 		arraysMap[left->getName()]->getValue(left->getIndex())->setValue(right->getValue());
			// 		//cout << "IT'S ASSING FOR ARRAY_ELEMENT2\n";
			// 	}

			// 	Number *num = new Number(right->getValue());
			// 	recycle.push_back(num);
			// 	computationStack.push(num);
			// } else if (left != nullptr && left->getLexType() == VARIABLE) {
			// 	left = new Number(variablesMap[left->getName()]);
			// 	recycle.push_back(left);
			// } else if (left != nullptr && left->getLexType() == ARRAY_ELEMENT) {
			// 	left = new Number(arraysMap[right->getName()]->getValue(right->getIndex())->getValue());
			// 	recycle.push_back(right);
			// }
			// if (right != nullptr && left != nullptr) {
			// 	value = poliz[i]->getValue(left->getValue(), right->getValue());
			// 	Number *num = new Number(value);
			// 	computationStack.push(num);
			// 	recycle.push_back(num);
			// }

			if (poliz[i]->getType() == ASSIGN) {
				if (left->getLexType() == VARIABLE) {
					variablesMap[left->getName()] = right->getValue();
					Number *num = new Number(right->getValue());
					recycle.push_back(num);
					computationStack.push(num);
				} else if (left->getLexType() == ARRAY_ELEMENT) {
					arraysMap[left->getName()]->getValue(left->getIndex())->setValue(right->getValue());
					Number *num = new Number(right->getValue());
					recycle.push_back(num);
					computationStack.push(num);
				}
			} else if (left != nullptr && left->getLexType() == VARIABLE) {
				left = new Number(variablesMap[left->getName()]);
				recycle.push_back(left);
			} else if (left != nullptr && left->getLexType() == ARRAY_ELEMENT) {
				left = new Number(arraysMap[left->getName()]->getValue(left->getIndex())->getValue());
				//left = new Number(arraysMap[right->getName()]->getValue(right->getIndex())->getValue());
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