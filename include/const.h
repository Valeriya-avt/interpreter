#include <string>
#include <map>

enum LEX_TYPE {
	NUMBER,
	OPER,
	VARIABLE,
};

enum OPERATOR {
	LBRACKET, RBRACKET,
	EQ,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	SHL, SHR,
	ASSIGN, NEQ,
	LEQ, LT,
	GEQ, GT,
	PLUS, MINUS,
	MULT, DIV, MOD,
	GOTO, COLON
};

extern int PRIORITY[];
extern std::string OPERTEXT[];
extern int OP_NUM;
extern std::map<std::string, int> variablesMap;
extern std::map<std::string, int> labelsMap;