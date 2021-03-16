int evaluatePostfix(vector<Lexem *> &poliz);
Lexem *checkForEvaluate(vector<Lexem *> poliz, stack<Lexem *> &computationStack);
void deleteVector(vector<Lexem *> vectorOfLexemes);