#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include "PolynomialList.h"

typedef struct t_singleton {
    PolynomialList  *a;
    char buffer_a[512];
    PolynomialList  *b;
    char buffer_b[512];
    int             operator;
    PolynomialList  *answer;
}       t_data;

PolynomialList* parse(const char *input);
PolynomialList* calculate(PolynomialList *a, PolynomialList* b, int operator);
void printAnswer(PolynomialList *answer);
void clearData(t_data *data);

#endif // CALCULATOR_H