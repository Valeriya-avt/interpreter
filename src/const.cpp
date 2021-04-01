#include <string>
#include <map>

#include "const.h"

int PRIORITY[] = {
	-1, -1,
	0,
	1,
	2,
	3,
	4,
	5,
	6, 6,
	7, 7,
	8, 8,
	9, 9,
	10, 10, 10,
	11, 11
};

std::string OPERTEXT[] = {
	"(", ")",
	"==",
	"or",
	"and",
	"|",
	"^",
	"&",
	"<<", ">>",
	":=", "!=",
	"<=", "<",
	">=", ">",
	"+", "-",
	"*", "/", "%",
	"goto", ":"
};

int OP_NUM = sizeof(OPERTEXT) / sizeof(std::string);

std::map<std::string, int> varsAndLabelsMap;