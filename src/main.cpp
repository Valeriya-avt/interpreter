#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "lexem.h"
#include "lexical.h"
#include "syntax.h"
#include "semantic.h"

using namespace std;

int main() {
	string codeline;
	vector<vector<Lexem *>> infixLines, postfixLines;
	int value, row;  
	while (std::getline(std::cin, codeline) && codeline != "ret") {
		infixLines.push_back(parseLexem(codeline));
	}
	for (row = 0; row < infixLines.size(); ++row) {
		initLabels(infixLines[row], row);
	}
	for (const auto &infix: infixLines) {
		postfixLines.push_back(buildPostfix(infix));
	}
	row = 0;
	while (0 <= row && row < postfixLines.size()) {
		cout << row << ": ";
		for (int j = 0; j < postfixLines[row].size(); j++)
			postfixLines[row][j]->print();
		cout << endl;
		value = evaluatePostfix(postfixLines[row], &row);
		cout << "Variables: ";
		for (auto it = variablesMap.begin(); it != variablesMap.end(); ++it)
			cout << (*it).first << " = " << (*it).second << " | ";
		cout << "\n\n";
	}
	for (int i = 0; i < infixLines.size(); i++) {
		deleteVector(infixLines[i]);
	}
	return 0;
}