#include <iostream>
#include <string>
#include <map>

#include "lexem.h"
#include "variables.h"

void printMap(string lexemName, map<string, int> lexemesMap) {
	cout << lexemName;
	for (auto it = lexemesMap.begin(); it != lexemesMap.end(); ++it)
		cout << (*it).first << " = " << (*it).second << " | ";
	cout << "\n\n";
}

void printArraysMap(map<string, Array *> lexemesMap) {
	cout << "Arrays: \n";
	for (auto it = lexemesMap.begin(); it != lexemesMap.end(); ++it) {
		(*it).second->printArray();
		cout << endl;     
	}
	cout << endl;
}

void printVector(string vectorName, vector<vector<Lexem *>> lexemes) {
	cout << vectorName;
	for (int row = 0; row < lexemes.size(); ++row) {
		cout << row << ": ";
		for (int j = 0; j < lexemes[row].size(); j++) {   
			if (lexemes[row][j])
				lexemes[row][j]->print();     
		}
		cout << endl;            
	}
	cout << "\n\n";
}

void print(vector<Lexem *> &poliz, int index) {
	if (poliz[index - 1]->getLexType() == VARIABLE)
		cout << poliz[index - 1]->getName() << " = " << locals.top().variablesMap[poliz[index - 1]->getName()] << endl;
	else if (poliz[0]->getLexType() == ARRAY_ELEMENT) {
		int pos;
		if (poliz[index - 2]->getLexType() == VARIABLE)
			pos = locals.top().variablesMap[poliz[index - 2]->getName()];
		else
			pos = poliz[index - 2]->getValue(); 
		cout << poliz[index - 3]->getName() << "[" << pos << "]" << " = " << locals.top().arraysMap[poliz[index - 3]->getName()]->getValue(pos)->getValue() << endl;
	}
}