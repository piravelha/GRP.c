#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

char* intToString(int value) {
    char *buffer = malloc(12);
    snprintf(buffer, 12, "%d", value);
    return buffer;
}

char* floatToString(double value) {
    char *buffer = malloc(24);

    if (value < 0.0000001 && value > -0.0000001) {
        snprintf(buffer, 24, "0.0");
    } else {
        snprintf(buffer, 24, "%.15g", value);
    }
    
    if (strchr(buffer, '.') == NULL) {
        size_t len = strlen(buffer);
        buffer[len] = '.';
        buffer[len + 1] = '0';
        buffer[len + 2] = '\0';
    }

    return buffer;
}

char* charToString(char value) {
    char *buffer = malloc(2);
    buffer[0] = value;
    buffer[1] = '\0';
    return buffer;
}

char* arrayToString(const Array *array);

char* dataToString(const Data *data) {
    char *result = NULL;

    switch (data->type) {
        case TYPE_INT:
            result = intToString(data->intValue);
            break;
        case TYPE_CHAR:
            result = charToString(data->charValue);
            break;
        case TYPE_FLOAT:
            result = floatToString(data->floatValue);
            break;
        case TYPE_ARRAY:
            result = arrayToString(data->arrayValue);
            break;
        case TYPE_FUNC:
            result = strdup("<quote>");
            break;
        default:
            result = strdup("<unknown>");
            break;
    }

    return result;
}

char* arrayToString(const Array *array) {
    // Check if the array consists solely of characters
    int isCharArray = 1;
    for (size_t i = 0; i < array->length; ++i) {
        if (array->elements[i].type != TYPE_CHAR) {
            isCharArray = 0;
            break;
        }
    }

    if (isCharArray) {
        // If it's an array of characters, print it as a string
        char *result = malloc(array->length + 1);
        for (size_t i = 0; i < array->length; ++i) {
            result[i] = array->elements[i].charValue;
        }
        result[array->length] = '\0';
        return result;
    } else {
        // Otherwise, print it as an array
        size_t totalLength = 2;
        char **elementStrings = malloc(array->length * sizeof(char*));

        for (size_t i = 0; i < array->length; ++i) {
            elementStrings[i] = dataToString(&array->elements[i]);
            totalLength += strlen(elementStrings[i]) + 2;
        }

        char *result = malloc(totalLength);
        strcpy(result, "[");

        for (size_t i = 0; i < array->length; ++i) {
            strcat(result, elementStrings[i]);
            if (i < array->length - 1) {
                strcat(result, " ");
            }
            free(elementStrings[i]);
        }

        free(elementStrings);
        strcat(result, "]");
        return result;
    }
}

void printData(Data data) {
    char* repr = dataToString(&data);
    printf("%s\n", repr);
    free(repr);
}