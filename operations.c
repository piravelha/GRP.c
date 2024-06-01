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

int flipOperation(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    push(stack, right);
    push(stack, left);
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
            func.quoteValue.funcValue(stack, func.quoteValue.needed);
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


Array *deepCopyArray(Array *array) {
    if (array == NULL) return NULL;

    Array *copy = createArray(array->length);
    for (size_t i = 0; i < array->length; i++) {
        Data *srcElem = &array->elements[i];
        Data *destElem = &copy->elements[i];

        destElem->type = srcElem->type;
        switch (srcElem->type) {
            case TYPE_INT:
                destElem->intValue = srcElem->intValue;
                break;
            case TYPE_ARRAY:
                destElem->arrayValue = deepCopyArray(srcElem->arrayValue);
                break;
            // Handle other types as needed
            default:
                break;
        }
    }
    return copy;
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
            char *elemRepr = dataToString(&elem);
            if (elem.type == TYPE_ARRAY) {
                Array *elemArr = deepCopyArray(elem.arrayValue);
                Data elemData;
                elemData.type = TYPE_ARRAY;
                elemData.arrayValue = elemArr;
                dataArray.arrayValue->elements[i] = elemData;
            } else {
                dataArray.arrayValue->elements[i] = elem;
            }
        }

        for (size_t i = 0; i < rightLength; i++) {
            Data elem = rightArr.arrayValue->elements[i];
            char *elemRepr = dataToString(&elem);
            if (elem.type == TYPE_ARRAY) {
                Array *elemArr = deepCopyArray(elem.arrayValue);
                Data elemData;
                elemData.type = TYPE_ARRAY;
                elemData.arrayValue = elemArr;
                dataArray.arrayValue->elements[leftLength + i] = elemData;
            } else {
                dataArray.arrayValue->elements[leftLength + i] = elem;
            }
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

int headOperation(Stack *stack) {
    Data arr = pop(stack);
    if (arr.type == TYPE_ARRAY) {
        size_t length = arr.arrayValue->length;
        if (length < 1) {
            printf("Attempting to extract the head of an empty list\n");
            freeStack(stack);
            freeData(&arr);
            exit(1);
        }
        Data head = arr.arrayValue->elements[0];
        push(stack, head);
        return 0;
    } else {
        char *arrRepr = dataToString(&arr);
        printf("Attempting to extract the head of a non-list value: '%s'", arrRepr);
        freeStack(stack);
        freeData(&arr);
        free(arrRepr);
        exit(1);
    }
}

int tailOperation(Stack *stack) {
    Data arr = pop(stack);
    if (arr.type == TYPE_ARRAY) {
        size_t length = arr.arrayValue->length;
        if (length < 1) {
            printf("Attempting to extract the tail of an empty list\n");
            freeStack(stack);
            freeData(&arr);
            exit(1);
        }
        Array *tail = createArray(length - 1);
        Data tailData;
        tailData.type = TYPE_ARRAY;
        tailData.arrayValue = tail;
        
        for (size_t i = 1; i < length; i++) {
            tailData.arrayValue->elements[i - 1] = arr.arrayValue->elements[i];
        }

        push(stack, tailData);
        return 0;
    } else {
        char *arrRepr = dataToString(&arr);
        printf("Attempting to extract the head of a non-list value: '%s'", arrRepr);
        freeStack(stack);
        freeData(&arr);
        free(arrRepr);
        exit(1);
    }
}

int lengthOperation(Stack *stack) {
    Data arr = pop(stack);
    if (arr.type == TYPE_ARRAY) {
        size_t length = arr.arrayValue->length;
        pushInt(stack, (int)length);
        return 0;
    } else {
        char *arrRepr = dataToString(&arr);
        printf("Attempting to get length of a non-array value: '%s'", arrRepr);
        freeStack(stack);
        free(arrRepr);
        freeData(&arr);
        exit(1);
    }
}