#ifndef C__GIT_ARITHMETICEXPRESSIONS_ARITHMETICEXPRESSIONS_INCLUDE_ARITHMEXP_H_
#define C__GIT_ARITHMETICEXPRESSIONS_ARITHMETICEXPRESSIONS_INCLUDE_ARITHMEXP_H_
class ArithmExp {
    char *exp;
    char *parametr;
    int *pvalue;
    int np;
    char *rpn;
    bool IsOp(char c);
    int Priority(char op);
 public:
    ArithmExp(char *exp);
    ~ArithmExp(void);
    void InputParametr(char c, int value);
    char* ReversePolishNotation();
    int Calc();
};
#endif  // C__GIT_ARITHMETICEXPRESSIONS_ARITHMETICEXPRESSIONS_INCLUDE_ARITHMEXP_H_
