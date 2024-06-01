#include <stdlib.h>
#include <stdio.h>
#include "operations.h"
#include "tostring.h"

int plusOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (right.type == TYPE_INT && left.type == TYPE_INT) {
        int sum = left.intValue + right.intValue;
        pushInt(stack, sum);
        return 0;
    } else {
        char* leftRepr = dataToString(&left);
        char* rightRepr = dataToString(&right);
        printf("Attempting to perform arithmethic (+) on non-integer values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        exit(1);
    }
}

int minusOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (right.type == TYPE_INT && left.type == TYPE_INT) {
        int sum = left.intValue - right.intValue;
        pushInt(stack, sum);
        return 0;
    } else {
        char* leftRepr = dataToString(&left);
        char* rightRepr = dataToString(&right);
        printf("Attempting to perform arithmethic (-) on non-integer values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        exit(1);
    }
}

int timesOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (right.type == TYPE_INT && left.type == TYPE_INT) {
        int sum = left.intValue * right.intValue;
        pushInt(stack, sum);
        return 0;
    } else {
        char* leftRepr = dataToString(&left);
        char* rightRepr = dataToString(&right);
        printf("Attempting to perform arithmethic (*) on non-integer values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        exit(1);
    }
}

int divOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (right.type == TYPE_INT && left.type == TYPE_INT) {
        int sum = left.intValue / right.intValue;
        pushInt(stack, sum);
        return 0;
    } else {
        char* leftRepr = dataToString(&left);
        char* rightRepr = dataToString(&right);
        printf("Attempting to perform arithmethic (/) on non-integer values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        exit(1);
    }
}

int eq(Data left, Data right) {
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        return left.intValue == right.intValue;
    } else if (left.type == TYPE_ARRAY && right.type == TYPE_ARRAY) {
        size_t leftLength = left.arrayValue->length;
        size_t rightLength = right.arrayValue->length;
        if (leftLength != rightLength) {
            return 0;
        }
        for (size_t i = 0; i < leftLength; i++) {
            Data leftElem = left.arrayValue->elements[i];
            Data rightElem = right.arrayValue->elements[i];
            int result = eq(leftElem, rightElem);
            if (result == 0) {
                return 0;
            }
        }
    } else if (left.type == TYPE_FUNC && right.type == TYPE_FUNC) {
        return 0;
    }

    return 1;
}

int eqOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    pushInt(stack, eq(left, right));
    return 0;
}

int ltOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        pushInt(stack, left.intValue < right.intValue);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempt to perform comparison (<) on non-integer values: '%s', and '%s'", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        exit(1);
    }
}

int gtOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        pushInt(stack, left.intValue > right.intValue);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempt to perform comparison (>) on non-integer values: '%s', and '%s'", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        exit(1);
    }
}

int lteOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        pushInt(stack, left.intValue <= right.intValue);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempt to perform comparison (<=) on non-integer values: '%s', and '%s'", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        exit(1);
    }
}

int gteOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        pushInt(stack, left.intValue >= right.intValue);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempt to perform comparison (>=) on non-integer values: '%s', and '%s'", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        exit(1);
    }
}


int duplicateOperation(Stack *stack) {
    Data top = pop(stack);
    push(stack, top);
    push(stack, top);
    return 0;
}

int mapOperation(Stack *stack) {
    Data func = pop(stack);
    Data arr = pop(stack);
    if (arr.type == TYPE_ARRAY && func.type == TYPE_FUNC) {
        size_t length = arr.arrayValue->length;
        Array *newArray = createArray(length);
        Data dataArray;
        dataArray.type = TYPE_ARRAY;
        dataArray.arrayValue = newArray;
        for (size_t i = 0; i < length; i++) {
            Data elem = arr.arrayValue->elements[i];
            push(stack, elem);
            func.funcValue(stack);
            Data newElem = pop(stack);
            dataArray.arrayValue->elements[i] = newElem;
        }
        push(stack, dataArray);
        return 0;
    } else {
        char *arrRepr = dataToString(&arr);
        char *funcRepr = dataToString(&func);
        printf("Attempting to perform Map operation on invalid values: '%s', and '%s'\n", arrRepr, funcRepr);
        free(arrRepr);
        free(funcRepr);
        freeStack(stack);
        exit(1);
    }
}

int concatOperation(Stack *stack) {
    Data rightArr = pop(stack);
    Data leftArr = pop(stack);
    if (rightArr.type == TYPE_ARRAY && leftArr.type == TYPE_ARRAY) {
        size_t rightLength = rightArr.arrayValue->length;
        size_t leftLength = leftArr.arrayValue->length;
        Array *newArray = createArray(leftLength + rightLength);
        Data dataArray;
        dataArray.type = TYPE_ARRAY;
        dataArray.arrayValue = newArray;

        for (size_t i = 0; i < leftLength; i++) {
            Data elem = leftArr.arrayValue->elements[i];
            dataArray.arrayValue->elements[i] = elem;
        }

        for (size_t i = 0; i < rightLength; i++) {
            Data elem = rightArr.arrayValue->elements[i];
            dataArray.arrayValue->elements[leftLength + i] = elem;
        }

        push(stack, dataArray);

        freeData(&leftArr);
        freeData(&rightArr);
        return 0;
    } else {
        char *leftRepr = dataToString(&leftArr);
        char *rightRepr = dataToString(&rightArr);
        printf("Attempting to perform Concat (++) operation on invalid values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        exit(1);
    }
}