#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "lexem.h"
//#include "const.h"
#include "lexical.h"
#include "syntax.h"
#include "semantic.h"

int main() {
	string codeline;
	vector<Lexem *> infix;
	vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix = parseLexem(codeline);
		postfix = buildPostfix(infix);
		// cout << "Postfix: ";
		// for (int i = 0; i < postfix.size(); ++i) {
		// 	postfix[i]->print();
		// }
		cout << '\n';
		value = evaluatePostfix(postfix);
		cout << "Result: " << value << '\n';
		cout << "Variable map:\n";
		for (auto it = variableMap.begin(); it != variableMap.end(); ++it)
			cout << (*it).first << " = " << (*it).second << endl;
		cout << endl;
		deleteVector(infix);
	}
	return 0;
}