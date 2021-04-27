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
	printVectors("Infix:\n", infixLines);

	initJumps(infixLines);  

	for (const auto &infix: infixLines)
		postfixLines.push_back(buildPostfix(infix));
	printVectors("Postfix:\n", postfixLines);
	Space space;
	locals.push(space);
	row = functionsMap["main"];
	int index = 0;
	cout << "Result:\n";                 
	while (0 <= row && row < postfixLines.size()) {
		//cout << row << ": ";
		//printVector(postfixLines[row]);   
		row = evaluatePostfix(postfixLines[row], row, &index);
		// if (!locals.empty()) {
		// 	printMap("Variables: ", locals.top().variablesMap);
		// 	printMap("Labels: ", labelsMap);                
		// }
	//printArraysMap(locals.top().arraysMap);  
	} 
	//printArraysMap(locals.top().arraysMap);
	for (int i = 0; i < infixLines.size(); i++)
		deleteVector(infixLines[i]);
	deleteVector(recycle); 
	file.close(); 
	return 0;
}