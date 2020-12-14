#pragma once

#include "../libmx/inc/libmx.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>

char *mx_getline();
void mx_replace_char(char *str, const char which, const char whith);
