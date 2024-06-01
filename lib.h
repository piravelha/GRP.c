#ifndef LIB_H
#define LIB_H

#include <stddef.h>

struct Array;

typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_ARRAY,
    TYPE_FUNC
} DataType;

typedef struct {
    DataType type;
    union {
        int intValue;
        char charValue;
        struct Array *arrayValue;
        int (*funcValue)();
    };
} Data;

typedef struct Array {
    Data *elements;
    size_t length;
} Array;

typedef struct {
    Data *items;
    size_t capacity;
    size_t top;
} Stack;

void initStack(Stack *stack);
void push(Stack *stack, Data item);
Data pop(Stack *stack);
Array *createArray(size_t length);
void destroyArray(Array *array);
void freeStack(Stack *stack);
void freeData(Data *data);
void pushInt(Stack *stack, int item);
void pushArray(Stack *stack, size_t length);
Data createFunction(void);
void trampoline(int (*func)(Stack *), Stack *stack);

#endif // LIB_H
