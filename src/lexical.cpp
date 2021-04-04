#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "lexem.h"

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

bool isGoTo(OPERATOR numOfOper) {
	return  numOfOper == GOTO || numOfOper == IF ||
			numOfOper == ELSE || numOfOper == WHILE ||
			numOfOper == ENDWHILE;
}

Oper *getOper(string codeline, int pos, int &next) {
	for (int op = 0; op < OP_NUM; op++) {
		string subcodeline = codeline.substr(pos, OPERTEXT[op].size());
		if (OPERTEXT[op] == subcodeline) {
			next = pos + OPERTEXT[op].size();
			if (isGoTo((OPERATOR)op))
				return new Goto(op);
			else
				return new Oper(op);
		}
	}
	return nullptr;
}

Number *getNumber(string codeline, int pos, int &next) {
	int i, number = 0;
	int n = codeline.size();
	for (i = pos; i < n && (codeline[i] >= '0' && codeline[i] <= '9');) {
		number = number * 10 + codeline[i] - '0';
		i++;
	}
	if (i != pos) {
		next = i;
		return new Number(number);
	} else {
		return nullptr;
	}
}

Variable *getVariable(string codeline, int pos, int &next) {
	string subcodestring;
	int i, n = codeline.size();
	for (i = pos; checkVariable(codeline[i]) && i < n;) {
		subcodestring.insert(subcodestring.size(), 1, codeline[i]);
		i++;
	}
	if (i != pos) {
		next = i;
		return new Variable(subcodestring);
	} else {
		return nullptr;
	}
}

bool checkSeparators(char ch) {
	return ch == ' ' || ch == '\t' || ch == '\n';
}

vector<Lexem *> parseLexem(string codeline) {
	vector<Lexem *> infix;
	Lexem *lexem;
	int pos, next = 0;
	for (pos = 0; pos < codeline.size();) {
		if (checkSeparators(codeline[pos])) {
			pos++;
			continue;
		} 
		lexem = getOper(codeline, pos, next);
		if (lexem != nullptr) {
			infix.push_back(lexem);
			pos = next;
			continue;
		}
		lexem = getNumber(codeline, pos, next);
		if (lexem != nullptr)
			infix.push_back(lexem);
		lexem = getVariable(codeline, pos, next);
		if (lexem != nullptr)
			infix.push_back(lexem);
		pos = next;
	}
	return infix;
}

void initLabels(vector<Lexem *> &infix, int row) {
	for (int i = 1; i < infix.size(); i++) {
		if (infix[i - 1]->getLexType() == VARIABLE && infix[i]->getLexType() == OPER) {
			Variable *lexemvar = (Variable *)infix[i - 1];
			Oper *lexemop = (Oper *)infix[i];
			if (lexemop->getType() == COLON) {
				labelsMap[lexemvar->getName()] = row;
				delete infix[i - 1];
				delete infix[i];
				infix[i - 1] = nullptr;
				infix[i] = nullptr;
				i++;
			}
		}
	}
}

void initJumps(vector<vector<Lexem *>> &infixes) {
	stack<Goto *> stackIfElse;
	stack<Goto *> stackWhile;
	for (int row = 0; row < infixes.size(); row++) {
		for (int i = 0; i < infixes[row].size(); i++) {
			if (infixes[row][i] != nullptr && infixes[row][i]->getLexType() == OPER) {
				if (infixes[row][i]->getType() == IF) {
					stackIfElse.push((Goto *)infixes[row][i]);
				}
				if (infixes[row][i]->getType() == ELSE) {
					stackIfElse.top()->setRow(row + 1);
					stackIfElse.pop();
					stackIfElse.push((Goto *)infixes[row][i]);
					labelsMap[OPERTEXT[infixes[row][i]->getType()]] = row + 1;
				}
				if (infixes[row][i]->getType() == ENDIF) {
					stackIfElse.top()->setRow(row + 1);
					stackIfElse.pop();
					labelsMap[OPERTEXT[infixes[row][i]->getType()]] = row + 1;
				}
				if (infixes[row][i]->getType() == WHILE) {
					infixes[row][i]->setRow(row);
					stackWhile.push((Goto *)infixes[row][i]);
					labelsMap[OPERTEXT[infixes[row][i]->getType()]] = row;
				}
				if (infixes[row][i]->getType() == ENDWHILE) {
					infixes[row][i]->setRow(stackWhile.top()->getRow());
					stackWhile.top()->setRow(row + 1);
					stackWhile.pop();
					labelsMap[OPERTEXT[infixes[row][i]->getType()]] = row + 1;
				}
			}
		}
	}
}