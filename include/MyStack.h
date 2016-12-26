#ifndef C__GIT_PALINDROM_IMPLEMENTATION_PALINDROM_IMPLEMENTATION_INCLUDE_MYSTACK_H_
#define C__GIT_PALINDROM_IMPLEMENTATION_PALINDROM_IMPLEMENTATION_INCLUDE_MYSTACK_H_
#include "StructCNode.h"
template <class ValType>
 class MyStack {
     CNode<ValType> *top;
  public:
     MyStack(void);
     ~MyStack(void);
     ValType& GetTop();
     bool pop();
     bool push(ValType x);
     bool IsEmpty();
};

template <class ValType>
MyStack<ValType> :: MyStack(void) {
    top = 0;
}
template <class ValType>
MyStack<ValType> :: ~MyStack(void) {
    while ( top != 0 ) {
        CNode<ValType> *tmp = top;
        top = top->next;
        delete tmp;
    }
}
template <class ValType>
ValType& MyStack<ValType> :: GetTop() {
    if ( top != 0 )
        return top->data;
    else
        throw 1;
}
template <class ValType>
bool MyStack<ValType> :: push(ValType x) {
    CNode<ValType> *node = new CNode<ValType>;
    node->data = x;
    node->next = top;
    top = node;
    return true;
}
template <class ValType>
bool MyStack<ValType> :: pop() {
    if ( top != 0 ) {
        CNode<ValType> *tmp = top;
        top = top->next;
        delete tmp;
        return true;
    } else {
        return false;
    }
}
template <class ValType>
bool MyStack<ValType> :: IsEmpty() {
    if (top == 0)
        return true;
    else
        return false;
}
#endif  // C__GIT_PALINDROM_IMPLEMENTATION_PALINDROM_IMPLEMENTATION_INCLUDE_MYSTACK_H_
