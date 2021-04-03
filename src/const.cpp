#include <string>
#include <map>

#include "const.h"

int PRIORITY[] = {
	-1, -1,
	1, 1,
	2, 2,
	3, 3, 3,
	4, 4,
	5,
	6,
	7,
	8,
	9,
	10, 10,
	11, 11,
	12, 12, 12, 12,
	13, 13,
	14, 14, 14
};

std::string OPERTEXT[] = {
	"if", "then",
	"else", "endif",
	"while", "endwhile",
	"goto", ":=", ":",
	"(", ")",
	"or",
	"and",
	"|",
	"^",
	"&",
	"==", "!=",
	"<<", ">>",
	"<=", "<", ">=", ">",
	"+", "-",
	"*", "/", "%"
};

int OP_NUM = sizeof(OPERTEXT) / sizeof(std::string);

std::map<std::string, int> variablesMap;
std::map<std::string, int> labelsMap;