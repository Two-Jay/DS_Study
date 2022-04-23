#include "./includes/blankChecker.h"
#include <stdio.h>
#include <string.h>

// int main(int argc, char **argv) {
//     if (argc != 2) return 0;
//     else {
//         printf("inserted input : [%s] :)\n", argv[1]);
//         bool checker = isClosedBlank((const char *)argv[1], strlen(argv[1]));
//         printf("result : [%s] :D\n", (checker == true) ? "true" : "false");
//     }
//     return 0;
// }

void testSpace(char *str, bool expected) {
    static int testNumber;
    printf("testCase No.%d | ", testNumber++);
    bool checker = isClosedBlank((const char *)str, strlen(str));
    printf("result : [%s] | ", (checker == true) ? "true" : "false");
    printf("is the answer correct? : [%s ]\n", (checker == expected) ? "✅ :)" : "❌ :(");
}

int main(void) {
    testSpace("1234", true);

    testSpace("(12)34", true);
    testSpace("(12)3)4", false);
    testSpace("(1234", false);
    testSpace("(1234)", true);
    testSpace("1234)", false);

    testSpace("1{23}4", true);
    testSpace("{123}4", true);
    testSpace("1{234", false);
    testSpace("123}4", false);

    testSpace("[1234]", true);
    testSpace("1234]", false);
    testSpace("[1234", false);

    testSpace("1(23}4", false);
    testSpace("1(2]3}4", false);
    testSpace("[1(23}4]", false);
    testSpace("[1{(23)}4]", true);

    testSpace("((((((((", false);
    testSpace("((())))", false);
    testSpace("()()({}})", false);
    testSpace("{{(([[([1{(23)}4])]]))}}", true);


    testSpace("m(a + b)", true);
    testSpace("{(a + b)(a - b)}^2", true);
    testSpace("2x[{(ax + by + c)(dx + ey + f)}^2]", true);
    testSpace("(a + b)^2", true);
    testSpace("2{(a^2 + ab + b^2)(a^2 - ab + b^2)}", true);
    return 0;
}