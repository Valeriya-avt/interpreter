#include <string>
#include <map>
#include <iostream>

#include <lexem.h>

extern bool BEFORE_ASSIGN, LVALUE_FOUND, IN_PARSE;
extern Space globals;
extern std::stack<Space> locals;
extern std::stack<Space> prevLocals;
extern vector<Lexem *> recycle;
extern stack<Lexem *> arguments;