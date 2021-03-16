vector<Lexem *> parseLexem(string codeline);
bool checkOperator(char ch);
bool checkVariable(char ch);
Oper *getOper(string codeline, int pos, int &next);
Number *getNumber(string codeline, int pos, int &next);
Variable *getVariable(string codeline, int pos, int &next);
bool checkSeparators(char ch);