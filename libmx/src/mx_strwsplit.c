#include "../inc/libmx.h"
#include <stdlib.h>

char **mx_strwsplit(const char *s, const char *delim)
{
    void *data;
    char *_s = (char *)s;
    const char **ptrs;
    size_t
        ptrsSize,
        nbWords = 1,
        sLen = mx_strlen(s),
        delimLen = mx_strlen(delim);

    while ((_s = mx_strstr(_s, delim)))
    {
        _s += delimLen;
        ++nbWords;
    }
    ptrsSize = (nbWords + 1) * sizeof(char *);
    ptrs =
        data = malloc(ptrsSize + sLen + 1);
    if (data)
    {
        *ptrs =
            _s = mx_strcpy(((char *)data) + ptrsSize, s);
        if (nbWords > 1)
        {
            while ((_s = mx_strstr(_s, delim)))
            {
                *_s = '\0';
                _s += delimLen;
                *++ptrs = _s;
            }
        }
        *++ptrs = NULL;
    }
    return data;
}

