#include <string>
#include <map>

enum LEX_TYPE {
	NUMBER,
	OPER,
	VARIABLE,
};

enum OPERATOR {
	IF, THEN,
	ELSE, ENDIF,
	WHILE, ENDWHILE,
	GOTO, ASSIGN, COLON,
	LBRACKET, RBRACKET,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	EQ, NEQ,
	SHL, SHR,
	LEQ, LT, GEQ, GT,
	PLUS, MINUS,
	MULT, DIV, MOD
};

extern int PRIORITY[];
extern std::string OPERTEXT[];
extern int OP_NUM;
extern std::map<std::string, int> variablesMap;
extern std::map<std::string, int> labelsMap;