#include "ArithmExp.h"
#include "MyStack.h"
#include "math.h"
#include <iostream>
ArithmExp::ArithmExp(char *exp_) {
    int n;
    for (n=0; exp_[n] != 0; n++) {}
    exp = new char[n+1];
    for (int i=0; i < n+1; i++)
        exp[i] = exp_[i];
    parametr = 0;
    pvalue = 0;
    np = 0;
    rpn = 0;
}
ArithmExp::~ArithmExp(void) {
    delete []exp;
    delete []parametr;
    delete []pvalue;
}
void ArithmExp::InputParametr(char c,  int value) {
    np++;
    parametr = (char*)realloc(parametr,  (np+1)*sizeof(char));
    parametr[np-1] = c;
    parametr[np] = 0;
    pvalue = (int*)realloc(pvalue,  np*sizeof(int));
    pvalue[np-1] = value;
}
bool ArithmExp::IsOp(char c) {
    if ( (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '|') || ( c == '(') || (c == ')') )
        return true;
    else
        return false;
}
int ArithmExp::Priority(char op) {
    switch (op) {
    case '+':
    case '-': return 1; break;
    case '*':
    case '/': return 2; break;
    case '^':
    case '|': return 3; break;
    }
}
char* ArithmExp::ReversePolishNotation() {
    MyStack<char> st;
    int n,  k = 0;
    int f = 0,  br = 0;
    bool flag = 0,  fl = 0;
    for (n=0; exp[n] != 0; n++) {}
    for (int i=0; exp[i] != 0; i++) {
        fl = 0;
        if ( (i == 0) && (exp[i] == '-') ) {
            rpn = (char*)realloc(rpn,  (k+2)*sizeof(char));
            rpn[k++] = '-';
            rpn[k++] = ' ';
            continue;
        }
        if (i != 0) {
            if ( ( (exp[i-1] == '(') && (exp[i] == '-') ) || ( (exp[i-1] == '|') && (exp[i] == '-') ) ) {
                rpn = (char*)realloc(rpn,  (k+2)*sizeof(char));
                rpn[k++] = '-';
                rpn[k++] = ' ';
                continue;
            }
        }
        if (!IsOp(exp[i])) {
            if ( ( (exp[i] > 96) && (exp[i] < 123) ) ) {
                rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
                rpn[k++] = exp[i];
                } else {
                if ( (exp[i] > 47) && (exp[i] < 58) ) {
                    for (; ( (!IsOp(exp[i])) && (exp[i] != 0) ); i++) {
                        if (!( (exp[i] > 47) && (exp[i] < 58) ) )
                            throw 1;
                        rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
                        rpn[k++] = exp[i];
                    }
                rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
                rpn[k++] = ' ';
                i--;
                } else {
                    throw 1;
                }
              }
        } else {
            if ((st.IsEmpty()) || (exp[i] == '(') || ((st.GetTop() == '(') && (exp[i] != ')')) || ((exp[i] == '|') && (f == 0)) || ((st.GetTop() == '|') && (exp[i] != '|')) || ((exp[i] == '|') && (((exp[i-1] == '|') && (flag == 1)) || ((exp[i-1] == '+') || (exp[i-1] == '-') || (exp[i-1] == '*') || (exp[i-1] == '/') || (exp[i-1] == '^'))))) {
                st.push(exp[i]);
                flag = 1;
                if (exp[i] == '|')
                    f++;
                if (exp[i] == '(')
                    br++;
            } else {
                if (exp[i] == ')') {
                    br--;
                    while (st.GetTop() != '(') {
                        rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
                        rpn[k++] = st.GetTop();
                        st.pop();
                    }
                    st.pop();
                } else {
                    if ( (exp[i] == '|') && (f > 0) ) {
                        flag = 0;
                        while (st.GetTop() != '|') {
                        rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
                        rpn[k++] = st.GetTop();
                        st.pop();
                    }
                        st.pop();
                        rpn = (char*)realloc(rpn, (k+2)*sizeof(char));
                        rpn[k++] = '|';
                        rpn[k++] = '|';
                        f--;
                    } else {
                        if (exp[i] == '^') {
                                st.push(exp[i]);
                        } else {
                            if (Priority(st.GetTop()) < Priority(exp[i])) {
                                   st.push(exp[i]);
                            } else {
                                rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
                                rpn[k++] = st.GetTop();
                                st.pop();
                                st.push(exp[i]);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((br != 0) || (f != 0))
        throw 1;
    while (!st.IsEmpty()) {
        rpn = (char*)realloc(rpn, (k+1)*sizeof(char));
        rpn[k++] = st.GetTop();
        st.pop();
    }
    rpn[k] = 0;
    return rpn;
}
int ArithmExp::Calc() {
    if (rpn == 0)
        ReversePolishNotation();
    MyStack<int> st;
    int n;
    bool fl = 0;
    int res;
    if (rpn == 0)
        throw 1;
    for (int i=0; rpn[i] != 0; i++) {
        if (!IsOp(rpn[i])) {
            if ( ( (rpn[i] > 96) && (rpn[i] < 123) ) ) {
                if (parametr == 0) {
                    std::cout << "Input parametr" << std::endl;
                    throw 1;
                  }
                for (int j=0; j < np; j++) {
                    if (rpn[i] == parametr[j]) {
                        fl = 1;
                        st.push(pvalue[j]);
                    }
                }
                if (fl == 0) {
                    std::cout << "Input parametr" << std::endl;
                    throw 1;
                }
				fl = 0;
				continue;
            } 
            int operand = 0;
            for (n=0; rpn[i+n] != ' '; n++) {}
            for (int j=0; rpn[i] != ' '; i++,  j++)
                operand+=((rpn[i]-'0')*pow(10.0, n-1-j));
            st.push(operand);
        } else {
            if (rpn[i] == '^') {
                int r;
                double l;
                if (!st.IsEmpty()) {
                    r = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.IsEmpty()) {
                    l = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                st.push(pow(l,  r));
            }
            if (rpn[i] == '+') {
                int r,  l;
                if (!st.IsEmpty()) {
                    r = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.IsEmpty()) {
                l = st.GetTop();
                st.pop();
                } else {
                    throw 1;
                }
                st.push(l+r);
            }
            if (rpn[i] == '-') {
                if (rpn[i+1] == ' ') {
                    i+=2;
                    double operand = 0;
                    for (n=0; rpn[i+n] != ' '; n++) {}
                    for (int j=0; rpn[i] != ' '; i++,  j++)
                    operand+=((rpn[i]-'0')*pow(10.0, n-1-j));
                    st.push(-operand);
                } else {
                    int r, l;
                    if (!st.IsEmpty()) {
                        r = st.GetTop();
                        st.pop();
                    } else {
                        throw 1;
                    }
                    if (!st.IsEmpty()) {
                        l = st.GetTop();
                        st.pop();
                    } else {
                        throw 1;
                    }
                    st.push(l-r);
                }
            }
            if (rpn[i] == '*') {
                int r, l;
                if (!st.IsEmpty()) {
                    r = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.IsEmpty()) {
                    l = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                st.push(l*r);
            }
            if (rpn[i] == '/') {
                int r, l;
                if (!st.IsEmpty()) {
                    r = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.IsEmpty()) {
                    l = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                if (r == 0)
                    throw 1;
                else
                    st.push(l/r);
            }
            if (rpn[i] == '|') {
                int tmp;
                if (!st.IsEmpty()) {
                    tmp = st.GetTop();
                    st.pop();
                } else {
                    throw 1;
                }
                st.push(abs(tmp));
                i++;
            }
        }
    }
    res = st.GetTop();
    st.pop();
    if (st.IsEmpty()) {
        return res;
    } else {
        std::cout << "error expression";
        throw 1;
    }
}
