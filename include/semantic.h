int evaluatePostfix(vector<Lexem *> &poliz, int row, int *index);
Lexem *checkForEvaluate(vector<Lexem *> &poliz, stack<Lexem *> &computationStack);
void deleteVector(vector<Lexem *> &vectorOfLexemes);