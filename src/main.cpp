#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <fstream>

#include "lexem.h"
#include "variables.h"
#include "lexical.h"
#include "syntax.h"
#include "semantic.h"

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

int main(int argc, char **argv) {
	string codeline;
	std::ifstream file;            
	file.open(argv[1]);    
	vector<vector<Lexem *>> infixLines, postfixLines;
	int value, row;    
	while (std::getline(file, codeline)) {
		infixLines.push_back(parseLexem(codeline));          
	}
	for (row = 0; row < infixLines.size(); ++row)
		initLabels(infixLines[row], row);
	printVector("Infix:\n", infixLines);
	initJumps(infixLines);                

	for (const auto &infix: infixLines)
		postfixLines.push_back(buildPostfix(infix));
	printVector("Postfix:\n", postfixLines);
	Space space;
	locals.push(space);
	row = functionsMap["main"];
	int index = 0;
	cout << "Result:\n";  
	while (0 <= row && row < postfixLines.size()) {
		row = evaluatePostfix(postfixLines[row], row, &index);                               
		// if (!locals.empty()) {
		// 	printMap("Variables: ", locals.top().variablesMap);
		// 	printMap("Labels: ", labelsMap);   
		// }
	}
	//printArraysMap(locals.top().arraysMap);
	for (int i = 0; i < infixLines.size(); i++) {          
		deleteVector(infixLines[i]);  
	}
	deleteVector(recycle); 
	file.close(); 
	return 0;
}