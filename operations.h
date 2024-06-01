#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>
#include "lib.h"

int plusOperation(Stack *stack);
int minusOperation(Stack *stack);
int timesOperation(Stack *stack);
int divOperation(Stack *stack);
int eqOperation(Stack *stack);
int ltOperation(Stack *stack);
int gtOperation(Stack *stack);
int lteOperation(Stack *stack);
int gteOperation(Stack *stack);
int duplicateOperation(Stack *stack);
int mapOperation(Stack *stack);
int concatOperation(Stack *stack);

#endif // OPERATIONS_H
