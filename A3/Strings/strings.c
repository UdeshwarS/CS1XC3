#include <stdbool.h>
#include <stdlib.h>
#include "strings.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int str2int(char *str) {
    int sign = 1;
    int value = 0;
    char *p = str;

    if (*p == '\0') {
        return 0;
    }

    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    if (*p == '\0') {
        return 0;
    }

    while (*p != '\0') {
        if (!isDigit(*p)) {
            return 0;
        }
        value = value * 10 + (*p - '0');
        p++;
    }

    return sign * value;
}

int evaluate(char expr[]) {
    char *p = expr + 1;
    char *op = NULL;
    char operator;
    int left;
    int right;

    while (*p != '\0') {
        if (*p == '+' || *p == '-' || *p == '*') {
            op = p;
            break;
        }
        p++;
    }

    if (op == NULL) {
        return 0;
    }

    operator = *op;
    *op = '\0';

    left = str2int(expr);
    right = str2int(op + 1);

    *op = operator;

    if (operator == '+') {
        return left + right;
    }
    if (operator == '-') {
        return left - right;
    }
    return left * right;
}