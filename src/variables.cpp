#include <string>
#include <map>

#include "lexem.h"
//int OP_NUM = sizeof(OPERTEXT) / sizeof(std::string);

std::map<std::string, int> variablesMap;
std::map<std::string, int> labelsMap;
std::map<std::string, Array *> arraysMap;
bool BEFORE_ASSIGN, LVALUE_FOUND;
