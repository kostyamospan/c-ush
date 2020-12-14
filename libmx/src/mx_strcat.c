#include "../inc/libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int i, counter = 0;
    while (s1[counter] != 0) counter++;
    for (i = 0; i < mx_strlen(s2); i++) s1[i+counter] = s2[i];
    s1[i+counter] = '\0';
    return s1; 
}
