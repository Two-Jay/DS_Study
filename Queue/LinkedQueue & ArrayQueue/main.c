// #include "../includes/linkeddeque.h"
// #include "../includes/arrayqueue.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

// enqueue : A B C D
// dequeue 1 time;
// peek : must be B;
// enqueue : E - must be B C D E;

char *setOutputFileName(int case_nbr) {
    char *output_file_name = "testCase_00_answer";
    output_file_name[9] = case_nbr / 10 + '0';
    output_file_name[9] = case_nbr % 10 + '0';
    return output_file_name;
};


// bool runTestcase_arrayQueue(const char *keyword, int case_nbr) {

//     if (strcmp(keyword, "enque") == 0) {
//         int output_fd = open(setOutputFileName(case_nbr), O_WRONLY, O_TRUNC);
//         ArrayQueue *qptr = createArrayQueue(5);
//         ArrayQueueNode nptr = (ArrayQueueNode *)calloc(sizeof(ArrayQueueNode), 1);
        
//         deleteArrayQueue(qptr);
//     }
//     if (strcmp(keyword, "deque") == 0) {

//     }
//     if (strcmp(keyword, "peek") == 0) {

//     }
//     if (strcmp(keyword, "deque_enque") == 0) {

//     }
//     if (strcmp(keyword, "size") == 0) {

//     }
//     if (strcmp(keyword, "delete") == 0)
//     return true;
// }

// bool runTestcase_linkedDeque(const char *keyword) {
//     return true;
// }

// void testfield_arrayQueue() {
// printf("arrayQueue .00 - 첫 선언 후 enqueue가 잘 진행되어야 합니다. : %s\n",
//     (runTestcase_arrayQueue("enque") ? "right" : "wrong"));
// printf("arrayQueue .01 - dequeue가 잘 진행되어야 합니다. : %s\n",
//     (runTestcase_arrayQueue("deque") ? "right" : "wrong"));
// printf("arrayQueue .02 - peek가 queue의 front를 가리키고 있어야 합니다. : %s\n",
//     (runTestcase_arrayQueue("peek") ? "right" : "wrong"));
// printf("arrayQueue .03 - dequeue를 하고 난 이후에도 enqueue가 잘 진행되어야 합니다. : %s\n",
//     (runTestcase_arrayQueue("deque_enque") ? "right" : "wrong"));
// printf("arrayQueue .04 - queue가 모두 차게 되면 enqueue를 하지 않아야 합니다. : %s\n",
//     (runTestcase_arrayQueue("size") ? "right" : "wrong"));
// printf("arrayQueue .05 - 해제를 적절하게 진행해야 합니다. : %s\n",
//     (runTestcase_arrayQueue("delete")) ? "right" : "wrong");
// };

// void testfield_linkedDeque(void) {
// printf("linkedDeque .00 - 첫 선언 후 enqueue가 잘 진행되어야 합니다. : %s\n",
//     (runTestcase_linkedDeque("enqueue") ? "right" : "wrong"));
// printf("linkedDeque .01 - dequeue가 잘 진행되어야 합니다. : %s\n",
//     (runTestcase_linkedDeque("enqueue") ? "right" : "wrong"));
// printf("linkedDeque .02 - peek가 queue의 front를 가리키고 있어야 합니다. : %s\n",
//     (runTestcase_linkedDeque("enqueue") ? "right" : "wrong"));
// printf("linkedDeque .03 - dequeue를 하고 난 이후에도 enqueue가 잘 진행되어야 합니다. : %s\n",
//     (runTestcase_linkedDeque("enqueue") ? "right" : "wrong"));
// printf("linkedDeque .04 - 해제를 적절하게 진행해야 합니다. : %s\n",
//     (runTestcase_linkedDeque("enqueue")) ? "right" : "wrong");
// };
    

int main(void) {
    // testfield_arrayQueue();
    for (int i = 0; i < 30; i++)
        printf("%s\n", setOutputFileName(i));
    system("leaks queueTester");
    return 0;
}
