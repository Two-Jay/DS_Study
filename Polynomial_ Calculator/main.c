#include "../includes/calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    t_data *data = (t_data *)calloc(sizeof(t_data), 1);

    printf("| Polynomial Calculator v.0.0.1|\n");
    while (1) {
        if (parseInput(data) == false) break ;
    }
    system("leaks Calculator");
    return 0;
}
