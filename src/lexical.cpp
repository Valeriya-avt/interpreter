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

Oper *getOper(string codeline, int pos, int &next) {
	for (int op = 0; op < OP_NUM; op++) {
		string subcodeline = codeline.substr(pos, OPERTEXT[op].size());
		if (OPERTEXT[op] == subcodeline) {
			next = pos + OPERTEXT[op].size();
			if (OPERTEXT[op] == "goto") {
				return new Goto(op);
			}
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