int evaluatePostfix(const vector<Lexem *> &poliz, int row, int *index);
Lexem *checkForEvaluate(const vector<Lexem *> &poliz, stack<Lexem *> &computationStack);
void deleteVector(vector<Lexem *> &vectorOfLexemes);