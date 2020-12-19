#pragma once

#include "../libmx/inc/libmx.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_2d_arr
{
    void **data;
    int size;
} t_2d_arr;

typedef struct s_command
{
    char *name;
    char **args;
    int argc;
} t_command;

static char *builtins[] = {
    "cd",
    "help",
    "exit",
};

char *mx_getline();
void mx_replace_char(char *str, const char which, const char whith);
t_2d_arr *mx_split_commands(const char *arg);
char **mx_str_split(char *a_str, const char a_delim);
t_2d_arr *mx_parse_commands(t_2d_arr *commands);
int mx_process_command(char *command_str);
t_command *mx_parse_str_command(char *command_str);

t_2d_arr *mx_create_2d_char_arr(void **arr, int size);
t_command *mx_create_command(char *name, char **args, int argc);
char **mx_command_to_array(t_command *command);

int mx_builtins_count();
int mx_launch_program(char **args);
int mx_execute_command(char **args);

//builtins

int mx_exit_builtin(char **args);

static int (*builtins_funcs[])(char **) = {
    &mx_exit_builtin,
};