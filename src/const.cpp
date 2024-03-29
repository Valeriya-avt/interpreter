#include <string>
#include <map>

#include <const.h>

using std::string;

int PRIORITY[] = {
	-1, -1,
	0,
	1, 1,
	2, 2,
	3, 3, 3,
	4, 4, 4, 4, 4, 4,
	5,
	6,
	7,
	8,
	9,
	10, 10,
	11, 11,
	12, 12, 12, 12,
	13, 14,
	15, 15, 15,
	16, 0,
	0, 0
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
	"print", "return",
	"function", "global"
};

const string MAIN = "main";
const string DETAIL = "-detail";
const string VARIABLES = "Variables: ";
const string INFIX = "Infix:\n";
const string POSTFIX = "Postfix:\n";
const string LABELS = "Labels: ";
const string GLOBALS = "Globals:";

int OP_NUM = sizeof(OPERTEXT) / sizeof(std::string);

std::map<std::string, int> labelsMap;
std::map<std::string, int> functionsMap;
std::stack<int> returnAddresses;
std::stack<int> returnIndex;