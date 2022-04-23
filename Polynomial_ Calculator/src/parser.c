#include "../includes/calculator.h"

bool strEqual(char *input, char *treat) {
    return strcmp(input, treat) ? false: true;
}

int str2int(const char* str, int len) {
    int i;
    int ret = 0;
    for(i = 0; i < len; ++i) {
        ret = ret * 10 + (str[i] - '0');
    }
    return ret;
}

int parseOperator(const char *operator_buf) {
    if (!operator_buf[0]) return 0;
    if (operator_buf[0] == '+') return OPERATOR_PLUS;
    if (operator_buf[0] == '-') return OPERATOR_MINUS;
    return 0;
}

char *tokenizer(char *input, char *indexed, size_t i) {
    size_t len = i - (indexed - input);
    char *ret = (char *)malloc(sizeof(char) * (len + 1));
    ret[len] = '\0';
    for (size_t i = 0; i < len; i++) {
        ret[i] = indexed[i];
    }
    return ret;
}

PolynomialListNode *createParsedNode(char *buf) {
    for (size_t i = 0, len = strlen(buf); i < len; i++) {
        // if (buf[i] == ) /// 콰고ㅓㅏㅏㅏㅇ!!!!!!!!!!!!!!
    }
    return NULL;
}

PolynomialList* parseExpression(char *input) {
    char *cptr = input;
    char *buf;
    for (size_t i = 0, len = strlen(input); i < len; i++) {
        if (i == len - 1) {
            buf = tokenizer(input, cptr, i + 1);
        } else if (input[i] == '+' || input[i] == '-') {
            buf = tokenizer(input, cptr, i);
            if (i != len - 1) cptr = input + i + 1;
        }
    }
    return NULL;
}

bool parseInput(t_data *data) {
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
    data->a = parseExpression(data->buffer_a);
    data->b = parseExpression(data->buffer_b);
    data->operator = parseOperator(operator_buf);
    if (!data->operator) {
        printf("Usage : insert input as \'[expression 1] +or- [expresstion 2]\'"); 
        return false;
    };
    return true;
}
