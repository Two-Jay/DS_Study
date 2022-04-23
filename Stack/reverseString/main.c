#include "./includes/revstr.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) return 0;
    else {
        printf("inserted input : [%s] :)\n", argv[1]);
        char *reversed = strrev((const char *)argv[1], strlen(argv[1]));
        printf("reversed input : [%s] :D\n", reversed);
        free(reversed);
    }
    system("leaks reverseString");
    return 0;
}