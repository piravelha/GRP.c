#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>
#include <math.h>
#include "lib.h"

int _var_Print(Stack *stack);
int _var_Plus(Stack *stack);
int _var_Minus(Stack *stack);
int _var_Times(Stack *stack);
int _var_Div(Stack *stack);
int _var_Conjuage(Stack *stack);
int _var_Negate(Stack *stack);
int _var_Signum(Stack *stack);
int _var_Reciprocal(Stack *stack);
int _var_Power(Stack *stack);
int _var_Exp(Stack *stack);
int _var_Sqrt(Stack *stack);
int _var_Root(Stack *stack);
int _var_Floor(Stack *stack);
int _var_Min(Stack *stack);
int _var_Ceil(Stack *stack);
int _var_Max(Stack *stack);
int _var_Abs(Stack *stack);
int _var_Mod(Stack *stack);
int _var_Depth(Stack *stack);
int _var_Eq(Stack *stack);
int _var_Lt(Stack *stack);
int _var_Gt(Stack *stack);
int _var_Lte(Stack *stack);
int _var_Gte(Stack *stack);
int _var_Dup(Stack *stack);
int _var_Flip(Stack *stack);
int _var_Map(Stack *stack);
int _var_Filter(Stack *stack);
int _var_Reduce(Stack *stack);
int _var_Concat(Stack *stack);
int _var_Cons(Stack *stack);
int _var_Head(Stack *stack);
int _var_Tail(Stack *stack);
int _var_Length(Stack *stack);
int _var_Show(Stack *stack);

#endif // OPERATIONS_H
