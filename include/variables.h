#include <string>
#include <map>
#include <iostream>

#include "lexem.h"

// extern std::map<std::string, int> variablesMap;
// extern std::map<std::string, Array *> arraysMap;
extern bool BEFORE_ASSIGN, LVALUE_FOUND;
extern Space globalVariables;
extern std::stack<Space> locals;