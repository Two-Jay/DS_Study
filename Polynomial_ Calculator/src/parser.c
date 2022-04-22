#include "../includes/calculator.h"

bool strEqual(char *input, char *treat) {
    return strcmp(input, treat) ? false: true;
}

bool getExpressions(t_data *data) {
    char operator_buf[10];

    printf("Insert your first expression : ");
    scanf("%s", data->buffer_a);
    if (strEqual(data->buffer_a, "exit")) return false;
    printf("Insert your first expression : ");
    scanf("%s", operator_buf);
    if (strEqual(operator_buf, "exit")) return false;
    printf("Insert your second expression : ");
    scanf("%s", data->buffer_b);
    if (strEqual(data->buffer_b, "exit")) return false;
    printf("buffer_a : %s\n", data->buffer_a);
    printf("operator : %s\n", operator_buf);
    printf("buffer_b : %s\n", data->buffer_b);
    return true;
}