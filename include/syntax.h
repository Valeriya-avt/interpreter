vector<Lexem *> buildPostfix(const vector<Lexem *> &infix);
bool checkBuild(int type, int prevPriority, int currentPriority);
void joinGotoAndLabel(Variable *lexemvar, stack<Oper *> &opstack);