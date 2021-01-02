#include "../inc/libmx.h"
#include <stdlib.h>
#include <string.h>

char **mx_strsplit(const char *s, const char *delim)
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
	/* if (!s)
		return NULL;
	int count_words = mx_count_words(s, c);
	char **arr_words = (char **)malloc((count_words + 1) * sizeof(char *));
	int len_w = 0;

	for (int j = 0; *s != '\0'; s++)
	{
		if (*s != c)
		{
			len_w++;
			if (*(s + 1) == '\0')
			{
				arr_words[j] = mx_strncpy(mx_strnew(len_w), (s - len_w + 1), len_w);
				break;
			}
		}
		else if (*s == c)
		{
			if (len_w == 0)
				;
			else if (len_w != 0)
			{
				arr_words[j] = mx_strncpy(mx_strnew(len_w), (s - len_w), len_w);
				len_w = 0;
				j++;
			}
		}
	}
	arr_words[count_words] = NULL;
	return (arr_words) ? arr_words : NULL; */
}
