//#ifndef CONST_H
//#define CONST_H

#include <string>
#include <map>
#include <iostream>
#include <stack>

//#include "lexem.h"

enum LEX_TYPE {
	NUMBER,
	OPER,
	VARIABLE,
	ARRAY,
	ARRAY_ELEMENT
};

enum OPERATOR {
	IF, THEN,
	SIZE,
	ELSE, ENDIF,
	WHILE, ENDWHILE,
	GOTO, ASSIGN, COLON,
	LBRACKET, RBRACKET, LSQUARE, RSQUARE, LVALUE, RVALUE,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	EQ, NEQ,
	SHL, SHR,
	LEQ, LT, GEQ, GT,
	PLUS, MINUS,
	MULT, DIV, MOD,
	PRINT, RET,
	FUNCTION, ENDFUNCTION
};

extern int PRIORITY[];
extern std::string OPERTEXT[];
extern int OP_NUM;
extern std::map<std::string, int> labelsMap;
extern std::map<std::string, int> functionsMap;
extern std::stack<int> returnAddresses;

//#endif