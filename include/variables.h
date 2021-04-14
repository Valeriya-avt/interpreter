#include <string>
#include <map>
#include <iostream>

#include "lexem.h"

extern std::map<std::string, int> variablesMap;
//extern std::map<std::string, int> labelsMap;
extern std::map<std::string, Array *> arraysMap;
extern bool BEFORE_ASSIGN, LVALUE_FOUND;