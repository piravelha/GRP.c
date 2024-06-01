#include <stdio.h>
#include "lib.h"
#include "tostring.h"
#include "operations.h"


int _var_Twice(Stack *_stack) {
    // symbol
    Data _var_x = pop(_stack);
    // symbol
    Data _var_f = pop(_stack);
    // symbol call
    push(_stack, _var_x);
    // splicing
    // symbol call
    push(_stack, _var_f);
    Data funcData0 = pop(_stack);
    if (funcData0.type == TYPE_FUNC) {
        funcData0.funcValue(_stack);
    }
    // splicing
    // symbol call
    push(_stack, _var_f);
    Data funcData1 = pop(_stack);
    if (funcData1.type == TYPE_FUNC) {
        funcData1.funcValue(_stack);
    }
}

int quote2(Stack *_stack) {
    // push 1
    pushInt(_stack, 1);
    // operator +
    plusOperation(_stack);
    return 0;
}
// start


int main() {
    Stack _stack;
    initStack(&_stack);
    // quoting
    Data funcData2 = createFunction();
    funcData2.funcValue = quote2;
    push(&_stack, funcData2);
    // push 10
    pushInt(&_stack, 10);
    trampoline(_var_Twice, &_stack);
    // operator <?
    printData(pop(&_stack));
    freeStack(&_stack);
}
