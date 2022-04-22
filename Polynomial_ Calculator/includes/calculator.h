#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "PolynomialList.h"

typedef struct t_singleton {
    PolynomialList  *a;
    PolynomialList  *b;
    PolynomialList  *answer;
    char            buffer_a[512];
    char            buffer_b[512];
    int             operator;
}       t_data;

#define OPERATOR_PLUS 2
#define OPERATOR_MINUS 4

PolynomialList* parseExpression(char *input);
bool parseInput(t_data *data);
PolynomialList* calculate(PolynomialList *a, PolynomialList* b, int operator);
void printAnswer(PolynomialList *answer);
void clearData(t_data *data);

#endif // CALCULATOR_H