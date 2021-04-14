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


int main(int argc, char **argv) {
	string codeline;
	std::ifstream file;            
	file.open(argv[1]);    
	vector<vector<Lexem *>> infixLines, postfixLines;
	int value, row;    
	while (std::getline(file, codeline)) {
		infixLines.push_back(parseLexem(codeline));
	}
	for (row = 0; row < infixLines.size(); ++row) {
		initLabels(infixLines[row], row);
		cout << row << ": ";
		for (int j = 0; j < infixLines[row].size(); j++) {
			if (infixLines[row][j])
				infixLines[row][j]->print(); 
		}
		cout << "\n\n";   
	} 

	initJumps(infixLines);

	for (const auto &infix: infixLines) {
		postfixLines.push_back(buildPostfix(infix));
	}
	
	for (row = 0; row < postfixLines.size(); ++row) {
		cout << row << ": ";
		for (int j = 0; j < postfixLines[row].size(); j++) {   
			if (postfixLines[row][j])
				postfixLines[row][j]->print();     
		}
		cout << "\n\n";   
	}
	row = 0;
	while (0 <= row && row < postfixLines.size()) {
		cout << row << ": ";   
		for (int j = 0; j < postfixLines[row].size(); j++) {
			if (postfixLines[row][j])
				postfixLines[row][j]->print();
			else
				cout << "NULLPTR\n";                         
		}
		cout << endl;
	//}  
	 	value = evaluatePostfix(postfixLines[row], &row);                    
		cout << "Variables: ";     
		for (auto it = variablesMap.begin(); it != variablesMap.end(); ++it)
			cout << (*it).first << " = " << (*it).second << " | ";
		cout << "\n\n";    
		cout << "Labels: ";     
		for (auto it = labelsMap.begin(); it != labelsMap.end(); ++it)
			cout << (*it).first << " = " << (*it).second << " | ";
		cout << "Arrays:\n";     
		for (auto it = arraysMap.begin(); it != arraysMap.end(); ++it)
			(*it).second->printArray();
	 }
	// for (int i = infixLines.size() - 1; i >= 0; i--) {          
	// 	deleteVector(infixLines[i]);          
	// }
	 for (int i = 0; i < infixLines.size(); i++) {          
		deleteVector(infixLines[i]);     
	}
	//for (auto it = arraysMap.begin(); it != arraysMap.end(); ++it) 
	//	(*it).second->~Array();
	file.close(); 
	return 0;
}