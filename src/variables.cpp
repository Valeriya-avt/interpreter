#include <string>
#include <map>

#include "lexem.h"

// std::map<std::string, int> variablesMap;
// std::map<std::string, Array *> arraysMap;
bool BEFORE_ASSIGN, LVALUE_FOUND;
Space globalVariables;
std::stack<Space> locals;
std::stack<Space> prevLocals;
vector<Lexem *> recycle;
stack<Lexem *> arguments;