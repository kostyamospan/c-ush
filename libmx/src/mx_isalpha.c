#include <stdbool.h>
#include "../inc/libmx.h"

bool mx_isalpha(int c) {
    return mx_isupper(c) || mx_islower(c);
}
