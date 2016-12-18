#include "ArithmExp.h"
#include <stack>
#include "math.h"
#include <iostream>
ArithmExp::ArithmExp(char *exp) {
    int n;
    for (n=0; exp[n] != 0; n++) {}
    s = new char[n+1];
    for (int i=0; i < n+1; i++)
        s[i] = exp[i];
    p = 0;
    vp = 0;
    np = 0;
}
ArithmExp::~ArithmExp(void) {
    delete []s;
    delete []p;
    delete []vp;
}
void ArithmExp::InputParametr(char c,  int value) {
    np++;
    p = (char*)realloc(p,  (np+1)*sizeof(char));
    p[np-1] = c;
    p[np] = 0;
    vp = (int*)realloc(vp,  np*sizeof(int));
    vp[np-1] = value;
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
    std::stack<char> st;
    int n,  k = 0;
    int f = 0,  br = 0;
    bool flag = 0,  fl = 0;
    for (n=0; s[n] != 0; n++) {}
    char *res = 0;
    for (int i=0; s[i] != 0; i++) {
        fl = 0;
        if ( (i == 0) && (s[i] == '-') ) {
            res = (char*)realloc(res,  (k+2)*sizeof(char));
            res[k++] = '-';
            res[k++] = ' ';
            continue;
        }
        if (i != 0) {
            if ( ( (s[i-1] == '(') && (s[i] == '-') ) || ( (s[i-1] == '|') && (s[i] == '-') ) ) {
                res = (char*)realloc(res,  (k+2)*sizeof(char));
                res[k++] = '-';
                res[k++] = ' ';
                continue;
            }
        }
        if (!IsOp(s[i])) {
            if ( ( (s[i] > 96) && (s[i] < 123) ) ) {
                if (p == 0) {
                    std::cout << "Input parametr" << std::endl;
                    return 0;
                }
                for (int j=0; p[j] != 0; j++) {
                    if (s[i] == p[j]) {
                        fl = 1;
                        int ns = 0;
                        if (vp[j] < 0) {
                            res = (char*)realloc(res,  (k+2)*sizeof(char));
                            res[k++] = '-';
                            res[k++] = ' ';
                        }
                        for (int tmp=abs(vp[j]); tmp != 0; ns++,  tmp=tmp/10) {}
                        int tmp = abs(vp[j]);
                        for (int l=ns-1; l >= 0; l--) {
                            res = (char*)realloc(res,  (k+1)*sizeof(char));
                            res[k++] = tmp / pow(10.0,  l) + '0';
                            tmp = tmp % (int)pow(10.0,  l);
                        }
                        res = (char*)realloc(res,  (k+1)*sizeof(char));
                        res[k++] = ' ';
                        break;
                    } else {
                        continue;
                    }
                }
                if (fl == 0) {
                    std::cout << "Input parametr" << std::endl;
                    return 0;
                }
            } else {
                if ( (s[i] > 47) && (s[i] < 58) ) {
                    for (; ( (!IsOp(s[i])) && (s[i] != 0) ); i++) {
                        if (!( (s[i] > 47) && (s[i] < 58) ) )
                            throw 1;
                        res = (char*)realloc(res, (k+1)*sizeof(char));
                        res[k++] = s[i];
                    }
                res = (char*)realloc(res, (k+1)*sizeof(char));
                res[k++] = ' ';
                i--;
                } else {
                    throw 1;
                }
              }
        } else {
            if ((st.empty()) || (s[i] == '(') || ((st.top() == '(') && (s[i] != ')')) || ((s[i] == '|') && (f == 0)) || ((st.top() == '|') && (s[i] != '|')) || ((s[i] == '|') && (((s[i-1] == '|') && (flag == 1)) || ((s[i-1] == '+') || (s[i-1] == '-') || (s[i-1] == '*') || (s[i-1] == '/') || (s[i-1] == '^'))))) {
                st.push(s[i]);
                flag = 1;
                if (s[i] == '|')
                    f++;
                if (s[i] == '(')
                    br++;
            } else {
                if (s[i] == ')') {
                    br--;
                    while (st.top() != '(') {
                        res = (char*)realloc(res, (k+1)*sizeof(char));
                        res[k++] = st.top();
                        st.pop();
                    }
                    st.pop();
                } else {
                    if ( (s[i] == '|') && (f > 0) ) {
                        flag = 0;
                        while (st.top() != '|') {
                        res = (char*)realloc(res, (k+1)*sizeof(char));
                        res[k++] = st.top();
                        st.pop();
                    }
                        st.pop();
                        res = (char*)realloc(res, (k+2)*sizeof(char));
                        res[k++] = '|';
                        res[k++] = '|';
                        f--;
                    } else {
                        if (s[i] == '^') {
                            if (Priority(st.top()) <= Priority(s[i])) {
                                st.push(s[i]);
                            } else {
                                res = (char*)realloc(res, (k+1)*sizeof(char));
                                res[k++] = st.top();
                                st.pop();
                                st.push(s[i]);
                            }
                        } else {
                            if (Priority(st.top()) < Priority(s[i])) {
                                   st.push(s[i]);
                            } else {
                                res = (char*)realloc(res, (k+1)*sizeof(char));
                                res[k++] = st.top();
                                st.pop();
                                st.push(s[i]);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((br != 0) || (f != 0))
        throw 1;
    while (!st.empty()) {
        res = (char*)realloc(res, (k+1)*sizeof(char));
        res[k++] = st.top();
        st.pop();
    }
    res[k] = 0;
    return res;
}
double ArithmExp::Calc() {
    char *rpn = ReversePolishNotation();
    std::stack<int> st;
    int n;
    int res;
    if (rpn == 0)
        throw 1;
    for (int i=0; rpn[i] != 0; i++) {
        if (!IsOp(rpn[i])) {
            int operand = 0;
            for (n=0; rpn[i+n] != ' '; n++) {}
            for (int j=0; rpn[i] != ' '; i++,  j++)
                operand+=((rpn[i]-'0')*pow(10.0, n-1-j));
            st.push(operand);
        } else {
            if (rpn[i] == '^') {
                int r;
                double l;
                if (!st.empty()) {
                    r = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.empty()) {
                    l = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                st.push(pow(l,  r));
            }
            if (rpn[i] == '+') {
                int r,  l;
                if (!st.empty()) {
                    r = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.empty()) {
                l = st.top();
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
                    if (!st.empty()) {
                        r = st.top();
                        st.pop();
                    } else {
                        throw 1;
                    }
                    if (!st.empty()) {
                        l = st.top();
                        st.pop();
                    } else {
                        throw 1;
                    }
                    st.push(l-r);
                }
            }
            if (rpn[i] == '*') {
                int r, l;
                if (!st.empty()) {
                    r = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.empty()) {
                    l = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                st.push(l*r);
            }
            if (rpn[i] == '/') {
                int r, l;
                if (!st.empty()) {
                    r = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                if (!st.empty()) {
                    l = st.top();
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
                if (!st.empty()) {
                    tmp = st.top();
                    st.pop();
                } else {
                    throw 1;
                }
                st.push(abs(tmp));
                i++;
            }
        }
    }
    res = st.top();
    st.pop();
    if (st.empty()) {
        return res;
    } else {
        std::cout << "error expression";
        throw 1;
    }
}
