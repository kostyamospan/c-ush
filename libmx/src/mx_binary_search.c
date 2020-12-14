#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int l = 0, r = size - 1;
    while (l <= r) {
        *count+=1;
        int m = l + (r - l) / 2;
        if (mx_strcmp(arr[m], s) == 0) return m;
        if (mx_strcmp(arr[m], s) < 0) l = m + 1;
        else r = m - 1;
    }
    *count = 0;
    return -1;
}
