#include "../inc/libmx.h"
#include <stdlib.h>

char *mx_nbr_to_hex(unsigned long nbr) {
	if (nbr < 0)
		return 0;
	unsigned long quotient = nbr;
	int remainder, j = 0, size = 0;
	unsigned long temp = nbr;
	while (temp != 0) {
		size++;
		temp /= 16;
	}
	char *hexadecimal = (char *)malloc(size + 1);
	for (int i = 0; i <= size; i++)
		hexadecimal[i] = '\0';
	while (quotient != 0) {
		remainder = quotient % 16;
		if (remainder < 10)
			hexadecimal[j] = 48 + remainder;
		else
			hexadecimal[j] = 87 + remainder;
		j++;
		quotient /= 16;
	}
	j--;
	for (int i = 0; i < j; i++, j--) {
		char tmp = hexadecimal[i];
		hexadecimal[i] = hexadecimal[j];
		hexadecimal[j] = tmp;
	}
	return hexadecimal;
}
