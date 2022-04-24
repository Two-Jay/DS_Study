#ifndef _EXPRESSION_PARSER_
#define _EXPRESSION_PARSER_

#include <stdbool.h>
#include "farraystack.h"

char *convertInfixToPostFix(const char *expression, size_t expression_len);
bool isClosedBlank(const char *str, size_t len);

// bool isOpenerBlank(const char input);
// bool isCloserBlank(const char input);
// bool isTwinBlank(const char openned, const char closed);

#endif // _EXPRESSION_PARSER_