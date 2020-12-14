#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) return -1;
    int l = left;
    int r = right;
    int m = mx_strlen(arr[(l + r) >> 1]);
    int swaps = 0;
    char* temp;
    while (l <= r) {
        while (mx_strlen(arr[l]) < m) l++;
        while (mx_strlen(arr[r]) > m) r--;
        if (l <= r) {
            if (mx_strlen(arr[l]) != mx_strlen(arr[r])) {
                temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
                swaps++;
            }
            l++;
            r--;
        }
    }
    if (left < r) swaps += mx_quicksort(arr, left, r);
    if (right > l) swaps += mx_quicksort(arr, l, right);
    return swaps;
}
