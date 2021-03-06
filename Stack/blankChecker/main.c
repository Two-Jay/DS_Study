#include "./includes/blankChecker.h"
#include <stdio.h>
#include <unistd.h>
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

int fail_tracker;

bool fail_checker(bool result, bool expected) {
    if (result == expected) return true;
    fail_tracker = 1;
    return false;
}

int printLastResult(void) {
    return (fail_tracker == 0)
        ? printf("\n_____________________________________________________________________\n\n                   당신의 괄호 체커는 Safe! LOL \n\n_____________________________________________________________________\n\n")
        : printf("\n_____________________________________________________________________\n\n                   당신의 괄호 체커는 운사페! 더 분발핫씨오! \n\n_____________________________________________________________________\n\n");
}

void testSpace(char *str, bool expected) {
    static int testNumber;
    
    printf("testCase No.%3d | ", testNumber++);
    bool checker = isClosedBlank((const char *)str, strlen(str));
    printf("result : [%6s] | ", (checker == true) ? "true" : "false");
    printf("is the answer correct? : %s \n", fail_checker(checker, expected) ? "✅ " : "❌ ");
}

int main(void) {
    printf("_____________________________________________________________________\n");
    printf("__            <괄호 체커 : (your 문장 == '운사페')?>               __\n");
    printf("=====================================================================\n");

    testSpace("", true);
    testSpace("1234", true);
    testSpace("(12)34", true);
    testSpace("(12)3)4", false);
    testSpace("(1234", false);
    testSpace("(1234)", true);
    testSpace("1234)", false);
    testSpace("Hello World !", true);
    testSpace("1{23}4", true);
    testSpace("{123}4", true);
    testSpace("1{234", false);
    testSpace("123}4", false);
    testSpace("[1234]", true);
    testSpace("1234]", false);
    testSpace("[1234", false);
    testSpace("2022-04-26 (Thus)", true);
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
    printLastResult();
    return 0;
}