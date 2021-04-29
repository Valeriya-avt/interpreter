#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <fstream>

#include <lexem.h>
#include <variables.h>
#include <lexical.h>
#include <syntax.h>
#include <semantic.h>
#include <print.h>

void evaluate(vector<vector<Lexem *>> &postfixLines) {
	int row = functionsMap[MAIN];
	int index = 0;
	cout << "Result:\n";                 
	while (0 <= row && row < postfixLines.size())
		row = evaluatePostfix(postfixLines[row], row, &index);
}

void detailEvaluate(vector<vector<Lexem *>> &postfixLines) {
	int row = functionsMap[MAIN];
	int index = 0;
	cout << "Result:\n";                 
	while (0 <= row && row < postfixLines.size()) {
		cout << row << ": ";
		printVector(postfixLines[row]);   
		row = evaluatePostfix(postfixLines[row], row, &index);
		if (!locals.empty())
			printMap(VARIABLES, locals.top().variablesMap);
		printMap(GLOBALS, globals.variablesMap);  
		printArraysMap(locals.top().arraysMap);
	}
}

void clear(vector<vector<Lexem *>> &infixLines) {
	for (int i = 0; i < infixLines.size(); i++)
		deleteVector(infixLines[i]);
	deleteVector(recycle); 
}

int main(int argc, char **argv) {
	string codeline;
	std::ifstream file;            
	file.open(argv[1]);    
	vector<vector<Lexem *>> infixLines, postfixLines;
	int value, row;
	while (std::getline(file, codeline))
		infixLines.push_back(parseLexem(codeline));
	for (row = 0; row < infixLines.size(); ++row)
		initLabels(infixLines[row], row);
	printVectors(INFIX, infixLines);

	initJumps(infixLines);
	initGlobals(infixLines);

	for (const auto &infix: infixLines)
		postfixLines.push_back(buildPostfix(infix));
	printVectors(POSTFIX, postfixLines);
	Space space;
	locals.push(space);
	if (argv[argc - 1] == DETAIL)
		detailEvaluate(postfixLines);
	else
		evaluate(postfixLines);
	clear(infixLines);
	file.close(); 
	return 0;
}