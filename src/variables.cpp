#include <string>
#include <map>

#include "lexem.h"

bool BEFORE_ASSIGN, LVALUE_FOUND, IN_PARSE = true;
Space globalVariables;
std::stack<Space> locals;
std::stack<Space> prevLocals;
vector<Lexem *> recycle;
stack<Lexem *> arguments;