#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub) return -2;
    for (int i = 0; str[i]; i++) {
        if (str[i] == sub[0]) 
            for (int j = 1; sub[j]; j++) {
                if(str[i + j] != sub[j]) break;
                if(!sub[j + 1]) return i;
            }
    }
    return -1;
}
