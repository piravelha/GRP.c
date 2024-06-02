#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "operations.h"
#include "tostring.h"

int _var_Print(Stack *stack) {
    printData(pop(stack));
    return 0;
}

int isNumber(Data data) {
    return data.type == TYPE_INT || data.type == TYPE_FLOAT;
}

int anyIsFloat(Data left, Data right) {
    return left.type == TYPE_FLOAT || right.type == TYPE_FLOAT;
}

int _var_Plus(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue + right.intValue;
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = left.floatValue + right.intValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = left.intValue + right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = left.floatValue + right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Plus (+) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Conjuage(Stack *stack) {
    Data x = pop(stack);
    if (isNumber(x)) {
        push(stack, x);
        return 0;
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Conjuage (^+) operation on non-numeric value: '%s'", xRepr);
        free(xRepr);
        freeStack(stack);
        freeData(&x);
        exit(1);
    }
}

int _var_Minus(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue - right.intValue;
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = left.floatValue - right.intValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = left.intValue - right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = left.floatValue - right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Minus (-) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Negate(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        pushInt(stack, -x.intValue);
        return 0;
    } else if (x.type == TYPE_FLOAT) {
        pushFloat(stack, -x.floatValue);
        return 0;
    } else {
        char *xRepr = dataToString(&x);
        printf("Attemting to perform Negate (^-) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Times(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue * right.intValue;
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = left.floatValue * right.intValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = left.intValue * right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = left.floatValue * right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Times (*) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Signum(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        if (x.intValue > 0) {
            pushInt(stack, 1);
            return 0;
        } else if (x.intValue < 0) {
            pushInt(stack, -1);
            return 0;
        } else {
            pushInt(stack, 0);
            return 0;
        }
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Signum (^*) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Div(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue / right.intValue;
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = left.floatValue / right.intValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = left.intValue / right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = left.floatValue / right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Div (/) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Reciprocal(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        pushFloat(stack, 1 / x.intValue);
        return 0;
    } else if (x.type == TYPE_FLOAT) {
        pushFloat(stack, 1 / x.floatValue);
        return 0;
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Reciprocal (^/) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Mod(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue % right.intValue;
        pushInt(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Mod (%%) operation on non-integer values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Power(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = (int)round(pow(left.intValue, right.intValue));
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = pow(left.floatValue, right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = pow(left.floatValue, right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = pow(left.floatValue, right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Power (**) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Exp(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        int res = (int)round(exp(x.intValue));
        pushFloat(stack, res);
        return 0;
    } else if (x.type == TYPE_FLOAT) {
        pushFloat(stack, exp(x.floatValue));
        return 0;
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Exp (^**) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Root(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        double sum = pow(left.intValue, 1 / right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = pow(left.intValue, 1 / right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = pow(left.intValue, 1 / right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = pow(left.intValue, 1 / right.intValue);
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Root (//) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Sqrt(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        pushFloat(stack, sqrt(x.intValue));
        return 0;
    } else if (x.type == TYPE_FLOAT) {
        pushFloat(stack, sqrt(x.floatValue));
        return 0;
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Sqrt (^//) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Floor(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        pushInt(stack, x.intValue);
    } else if (x.type == TYPE_FLOAT) {
        pushInt(stack, (int)floor(x.floatValue));
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Floor (-|) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Min(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue < right.intValue ? left.intValue : right.intValue;
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = left.floatValue < right.intValue ? left.floatValue : right.intValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = left.intValue < right.floatValue ? left.intValue : right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = left.floatValue < right.floatValue ? left.floatValue : right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Min (=-=) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int _var_Ceil(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        pushInt(stack, x.intValue);
    } else if (x.type == TYPE_FLOAT) {
        pushInt(stack, (int)ceil(x.floatValue));
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Ceil (+|) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int _var_Max(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        int sum = left.intValue > right.intValue ? left.intValue : right.intValue;
        pushInt(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        double sum = left.floatValue > right.intValue ? left.floatValue : right.intValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        double sum = left.intValue > right.floatValue ? left.intValue : right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        double sum = left.floatValue > right.floatValue ? left.floatValue : right.floatValue;
        pushFloat(stack, sum);
        return 0;
    } else {
        char *leftRepr = dataToString(&left);
        char *rightRepr = dataToString(&right);
        printf("Attempting to perform Max (=+=) operation on non-numeric values: '%s', and '%s'\n", leftRepr, rightRepr);
        free(leftRepr);
        free(rightRepr);
        freeStack(stack);
        freeData(&left);
        freeData(&right);
        exit(1);
    }
}

int findMaxDepth(Array *array) {
    int maxDepth = 1;
    for (size_t i = 0; i < array->length; i++) {
        Data elem = array->elements[i];
        if (elem.type == TYPE_ARRAY) {
            int currentDepth = 1 + findMaxDepth(elem.arrayValue);
            if (currentDepth > maxDepth) {
                maxDepth = currentDepth;
            }
        }
    }
    return maxDepth;
}

int _var_Depth(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_ARRAY) {
        int depth = findMaxDepth(x.arrayValue);
        pushInt(stack, depth);
    } else {
        pushInt(stack, 0);
    }
}

int _var_Abs(Stack *stack) {
    Data x = pop(stack);
    if (x.type == TYPE_INT) {
        if (x.intValue < 0) {
            pushInt(stack, -x.intValue);
        } else {
            pushInt(stack, x.intValue);
        }
    } else if (x.type == TYPE_FLOAT) {
        if (x.floatValue < 0) {
            pushFloat(stack, -x.floatValue);
        } else {
            pushFloat(stack, x.floatValue);
        }
    } else {
        char *xRepr = dataToString(&x);
        printf("Attempting to perform Abs (|^|) operation on non-numeric value: '%s'", xRepr);
        freeStack(stack);
        free(xRepr);
        freeData(&x);
        exit(1);
    }
}

int eq(Data left, Data right) {
    if (left.type == TYPE_INT && right.type == TYPE_INT) {
        return left.intValue == right.intValue;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
        return left.floatValue == right.intValue;
    } else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
        return left.intValue == right.floatValue;
    } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
        return left.floatValue == right.floatValue;
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

int _var_Eq(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    pushInt(stack, eq(left, right));
    return 0;
}

int _var_Lt(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (isNumber(right) && isNumber(left)) {
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

int _var_Gt(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (isNumber(right) && isNumber(left)) {
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

int _var_Lte(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (isNumber(right) && isNumber(left)) {
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

int _var_Gte(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    if (isNumber(right) && isNumber(left)) {
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


int _var_Dup(Stack *stack) {
    Data top = pop(stack);
    push(stack, top);
    push(stack, top);
    return 0;
}

int _var_Flip(Stack *stack) {
    Data right = pop(stack);
    Data left = pop(stack);
    push(stack, right);
    push(stack, left);
    return 0;
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

int _var_Map(Stack *stack) {
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
            if (newElem.type == TYPE_ARRAY) {
                Array *copy = deepCopyArray(newElem.arrayValue);
                Data dataCopy;
                dataCopy.type = TYPE_ARRAY;
                dataCopy.arrayValue = copy;
                dataArray.arrayValue->elements[i] = dataCopy; 
            } else {
                dataArray.arrayValue->elements[i] = newElem;
            }
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

int _var_Filter(Stack *stack) {
    Data p = pop(stack);
    Data arr = pop(stack);

    if (p.type == TYPE_FUNC && arr.type == TYPE_ARRAY) {
        size_t length = 0;
        Data filtered[arr.arrayValue->length];
        for (size_t i = 0; i < arr.arrayValue->length; i++) {
            push(stack, arr.arrayValue->elements[i]);
            p.quoteValue.funcValue(stack, p.quoteValue.needed);
            Data res = pop(stack);
            if (res.type == TYPE_INT && !res.intValue) {
                continue;
            }
            filtered[length] = arr.arrayValue->elements[i];
            length++;
        }
        Array *newArray = createArray(length);
        for (size_t i = 0; i < length; i++) {
            if (filtered[i].type == TYPE_ARRAY) {
                Array *copy = deepCopyArray(filtered[i].arrayValue);
                Data elem;
                elem.type = TYPE_ARRAY;
                elem.arrayValue = copy;
                newArray->elements[i] = elem;
            } else {
                newArray->elements[i] = filtered[i];
            }
            newArray->elements[i] = filtered[i];
        }
        Data dataArray;
        dataArray.type = TYPE_ARRAY;
        dataArray.arrayValue = newArray;
        push(stack, dataArray);
        return 0;
    } else {
        char *pRepr = dataToString(&p);
        char *arrRepr = dataToString(&arr);
        printf("Attempting to perform Filter (<&>) operation on invalid values: '%s', and '%s'", arrRepr, pRepr);
        freeStack(stack);
        free(pRepr);
        free(arrRepr);
        freeData(&p);
        freeData(&arr);
        exit(1);
    }
}

int _var_Reduce(Stack *stack) {
    Data op = pop(stack);
    Data arr = pop(stack);

    if (op.type == TYPE_FUNC && arr.type == TYPE_ARRAY) {
        if (arr.arrayValue->length < 1) {
            printf("Attempting to reduce an empty array");
            freeStack(stack);
            freeData(&op);
            freeData(&arr);
            exit(1);
        }

        Data acc;
        for (size_t i = 0; i < arr.arrayValue->length; i++) {
            if (i == 0) {
                acc = arr.arrayValue->elements[i];
                continue;
            }
            push(stack, acc);
            push(stack, arr.arrayValue->elements[i]);
            op.quoteValue.funcValue(stack, op.quoteValue.needed);
            acc = pop(stack);
        }
        push(stack, acc);
        return 0;
    } else {
        char *opRepr = dataToString(&op);
        char *arrRepr = dataToString(&arr);
        printf("Attempting to perform Reduce (<.>) operation on invalid values: '%s', and '%s'", arrRepr, opRepr);
        freeStack(stack);
        free(opRepr);
        free(arrRepr);
        freeData(&op);
        freeData(&arr);
        exit(1);
    }
}

int _var_Concat(Stack *stack) {
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

int _var_Cons(Stack *stack) {
    Data arr = pop(stack);
    Data x = pop(stack);
    if (arr.type == TYPE_ARRAY) {
        size_t arrLength = arr.arrayValue->length;
        Array *newArray = createArray(arrLength + 1);
        Data dataArray;
        dataArray.type = TYPE_ARRAY;
        dataArray.arrayValue = newArray;

        dataArray.arrayValue->elements[0] = x;

        for (size_t i = 0; i < arrLength; i++) {
            Data elem = arr.arrayValue->elements[i];
            char *elemRepr = dataToString(&elem);
            if (elem.type == TYPE_ARRAY) {
                Array *elemArr = deepCopyArray(elem.arrayValue);
                Data elemData;
                elemData.type = TYPE_ARRAY;
                elemData.arrayValue = elemArr;
                dataArray.arrayValue->elements[i + 1] = elemData;
            } else {
                dataArray.arrayValue->elements[i + 1] = elem;
            }
        }

        push(stack, dataArray);

        freeData(&x);
        freeData(&arr);
        return 0;
    } else {
        char *arrRepr = dataToString(&x);
        printf("Attempting to perform Cons (:>) operation on non-array tail: '%s'\n", arrRepr);
        free(arrRepr);
        freeStack(stack);
        exit(1);
    }
}

int _var_Head(Stack *stack) {
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

int _var_Tail(Stack *stack) {
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
            Data elem = arr.arrayValue->elements[i];
            if (elem.type == TYPE_ARRAY) {
                Data elemData;
                elemData.type = TYPE_ARRAY;
                elemData.arrayValue = deepCopyArray(elem.arrayValue);
                tailData.arrayValue->elements[i - 1] = elemData;
            } else {
                tailData.arrayValue->elements[i - 1] = elem;
            }
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

int _var_Length(Stack *stack) {
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

int _var_Show(Stack *stack) {
    Data x = pop(stack);
    char *xRepr = dataToString(&x);
    Array *reprArray = createArray(strlen(xRepr));
    for (size_t i = 0; i < strlen(xRepr); i++) {
        Data c;
        c.type = TYPE_CHAR;
        c.charValue = xRepr[i];
        reprArray->elements[i] = c;
    }
    Data dataArray;
    dataArray.type = TYPE_ARRAY;
    dataArray.arrayValue = reprArray;
    push(stack, dataArray);
    return 0;
}