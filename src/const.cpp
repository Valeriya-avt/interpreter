#include <string>
#include <map>

//#include "lexem.h"
#include "const.h"

int PRIORITY[] = {
	-1, -1,
	0,
	1, 1,
	2, 2,
	3, 3, 3,
	4, 4, 4, 4, 4, 5,
	5,
	6,
	7,
	8,
	9,
	10, 10,
	11, 11,
	12, 12, 12, 12,
	13, 13,
	14, 14, 14,
	15, 15
};

std::string OPERTEXT[] = {
	"if", "then",
	"size",
	"else", "endif",
	"while", "endwhile",
	"goto", ":=", ":",
	"(", ")", "[", "]", "lvalue", "rvalue",
	"or",
	"and",
	"|",
	"^",
	"&",
	"==", "!=",
	"<<", ">>",
	"<=", "<", ">=", ">",
	"+", "-",
	"*", "/", "%",
	"print", "ret"
};

int OP_NUM = sizeof(OPERTEXT) / sizeof(std::string);

// std::map<std::string, int> variablesMap;
// std::map<std::string, int> labelsMap;
// std::map<std::string, Array> arraysMap;
// bool BEFORE_ASSIGN, LVALUE_FOUND;
