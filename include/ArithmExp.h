#ifndef C__GIT_ARITHMETICEXPRESSIONS_ARITHMETICEXPRESSIONS_INCLUDE_ARITHMEXP_H_
#define C__GIT_ARITHMETICEXPRESSIONS_ARITHMETICEXPRESSIONS_INCLUDE_ARITHMEXP_H_
class ArithmExp {
    char *s;
    char *p;
    int *vp;
    int np;
 public:
    ArithmExp(char *exp);
    ~ArithmExp(void);
    void InputParametr(char c, int value);
    bool IsOp(char c);
    int Priority(char op);
    char* ReversePolishNotation();
    double Calc();
};
#endif  // C__GIT_ARITHMETICEXPRESSIONS_ARITHMETICEXPRESSIONS_INCLUDE_ARITHMEXP_H_
