#include <string>
#include <map>
#include <iostream>
#include <stack>

using std::string;

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
	PRINT, RETURN,
	FUNCTION, GLOBAL
};

extern const string MAIN;
extern const string DETAIL;
extern const string VARIABLES;
extern const string INFIX;
extern const string POSTFIX;
extern const string LABELS;
extern const string GLOBALS;

extern int PRIORITY[];
extern std::string OPERTEXT[];
extern int OP_NUM;
extern std::map<std::string, int> labelsMap;
extern std::map<std::string, int> functionsMap;
extern std::stack<int> returnAddresses;
extern std::stack<int> returnIndex;