#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "tostring.h"
#include "operations.h"

// start
int main() {
    Stack _stack;
    initStack(&_stack);
    // push 34
    pushInt(&_stack, 34);
    // push 35
    pushInt(&_stack, 35);
    // operator +
    plusOperation(&_stack);
    // operator <?
    printData(pop(&_stack));
    freeStack(&_stack);
}
