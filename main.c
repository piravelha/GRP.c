#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "tostring.h"
#include "operations.h"





// top
int _var_Factorial(Stack *_stack);

int _var_Product(Stack *_stack);

int _var_Sum(Stack *_stack);

int _var_Iota(Stack *_stack);


int _var_Iota(Stack *_stack) {
    // symbol
    Data _var_acc = pop(_stack);
    // symbol
    Data _var_n = pop(_stack);
    // symbol call
    push(_stack, _var_n);
    // push 0
    pushInt(_stack, 0);
    // operator <=
    trampoline(_var_Lte, _stack);
    Data condition1 = pop(_stack);
    if (!condition1.type == TYPE_INT || condition1.intValue) {
        freeData(&condition1);
    // symbol call
    push(_stack, _var_acc);
    return 0;
    } else {
    // symbol call
    push(_stack, _var_n);
    // push 1
    pushInt(_stack, 1);
    // operator -
    trampoline(_var_Minus, _stack);
    // symbol call
    push(_stack, _var_acc);
    // push array
    // symbol call
    push(_stack, _var_n);
    pushArray(_stack, 1);
    // operator ++
    trampoline(_var_Concat, _stack);
    return 1;
    }
}



int quote2(Stack *_stack, Data *needed) {
    // operator +
    trampoline(_var_Plus, _stack);
    return 0;
}

int _var_Sum(Stack *_stack) {
    // quoting
    Data funcData2 = createFunction();
    Data *needed2 = malloc(0 * sizeof(Data));
    funcData2.quoteValue.needed = needed2;
    funcData2.quoteValue.funcValue = quote2;
    push(_stack, funcData2);
    // operator <.>
    trampoline(_var_Reduce, _stack);
    return 0;
}



int quote3(Stack *_stack, Data *needed) {
    // operator *
    trampoline(_var_Times, _stack);
    return 0;
}

int _var_Product(Stack *_stack) {
    // quoting
    Data funcData3 = createFunction();
    Data *needed3 = malloc(0 * sizeof(Data));
    funcData3.quoteValue.needed = needed3;
    funcData3.quoteValue.funcValue = quote3;
    push(_stack, funcData3);
    // operator <.>
    trampoline(_var_Reduce, _stack);
    return 0;
}


int _var_Factorial(Stack *_stack) {
    // operator .=
    trampoline(_var_Iota, _stack);
    // operator <*>
    trampoline(_var_Product, _stack);
    return 0;
}

// start




int main() {
    Stack _stack;
    initStack(&_stack);
    // push array
    // push 3
    pushInt(&_stack, 3);
    // push 2
    pushInt(&_stack, 2);
    // push 1
    pushInt(&_stack, 1);
    pushArray(&_stack, 3);
    // operator ?
    trampoline(_var_Show, &_stack);
    // push array
    // push '!'
    pushChar(&_stack, '!');
    // push 'y'
    pushChar(&_stack, 'y');
    // push 'a'
    pushChar(&_stack, 'a');
    // push 'r'
    pushChar(&_stack, 'r');
    // push 'r'
    pushChar(&_stack, 'r');
    // push 'a'
    pushChar(&_stack, 'a');
    // push ' '
    pushChar(&_stack, ' ');
    // push 'e'
    pushChar(&_stack, 'e');
    // push 't'
    pushChar(&_stack, 't');
    // push 'i'
    pushChar(&_stack, 'i');
    // push 'r'
    pushChar(&_stack, 'r');
    // push 'o'
    pushChar(&_stack, 'o');
    // push 'v'
    pushChar(&_stack, 'v');
    // push 'a'
    pushChar(&_stack, 'a');
    // push 'f'
    pushChar(&_stack, 'f');
    // push ' '
    pushChar(&_stack, ' ');
    // push 'y'
    pushChar(&_stack, 'y');
    // push 'm'
    pushChar(&_stack, 'm');
    // push ' '
    pushChar(&_stack, ' ');
    // push 's'
    pushChar(&_stack, 's');
    // push 'i'
    pushChar(&_stack, 'i');
    // push ' '
    pushChar(&_stack, ' ');
    pushArray(&_stack, 22);
    // operator ++
    trampoline(_var_Concat, &_stack);
    // operator <?
    trampoline(_var_Print, &_stack);
    freeStack(&_stack);
}
