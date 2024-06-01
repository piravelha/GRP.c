#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

void initStack(Stack *stack) {
    stack->capacity = 10;
    stack->top = 0;
    stack->items = malloc(stack->capacity * sizeof(Data));
    if (!stack->items) {
        exit(1);
    }
}

void push(Stack *stack, Data item) {
    if (stack->top >= stack->capacity) {
        stack->capacity *= 2;
        Data *newItems = realloc(stack->items, stack->capacity * sizeof(Data));
        if (!newItems) {
            exit(1);
        }
        stack->items = newItems;
    }
    stack->items[stack->top++] = item;
}

Data pop(Stack *stack) {
    if (stack->top == 0) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[--stack->top];
}

Array *createArray(size_t length) {
    Array *array = malloc(sizeof(Array));
    array->length = length;
    array->elements = malloc(length * sizeof(Data));
    return array;
}

void destroyArray(Array *array) {
    for (size_t i = 0; i < array->length; i++) {
        freeData(&array->elements[i]);
    }
    free(array->elements);
    free(array);
}


void freeStack(Stack *stack) {
    for (size_t i = 0; i < stack->top; i++) {
        freeData(&stack->items[i]);
    }
    free(stack->items);
    stack->items = NULL;
}

void freeData(Data *data) {
    if (data->type == TYPE_ARRAY) {
        destroyArray(data->arrayValue);
    }
}

void pushInt(Stack *stack, int item) {
    Data data = {TYPE_INT, item};
    push(stack, data);
}

void pushArray(Stack *stack, size_t length) {
    Array *array = createArray(length);

    for (size_t i = 0; i < length; i++) {
        array->elements[i] = pop(stack);
    }

    Data dataArray;
    dataArray.type = TYPE_ARRAY;
    dataArray.arrayValue = array;

    push(stack, dataArray);
}

Data createFunction() {
    Data funcData;
    funcData.type = TYPE_FUNC;
    return funcData;
}

void trampoline(int (*func)(Stack *), Stack *stack) {
    while (func(stack)) {};
}