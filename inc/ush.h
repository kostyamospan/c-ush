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
#include <stdlib.h>

typedef struct s_2d_arr
{
    void **data;
    int size;
} t_2d_arr;

typedef struct s_command
{
    char *name;    // arr[0] - name
    char **args;   // args without name
    int argc;      // args count
    char **argswn; // arguments and name
} t_command;

extern char **environ;

static char *builtins[] = {
    "exit",
    "export",
    "pwd",
    "echo",
};

char *mx_getline();
void mx_replace_char(char *str, const char which, const char whith);
t_2d_arr *mx_split_commands(const char *arg);
char **mx_str_split(char *a_str, const char a_delim);
t_2d_arr *mx_parse_commands(t_2d_arr *commands);
int mx_process_command(char *command_str);
t_command *mx_parse_str_command(char *command_str);

t_2d_arr *mx_create_2d_char_arr(void **arr, int size);
t_command *mx_create_command(char **args, int argc);
char **mx_command_to_array(t_command *command);

void mx_ush_loop(char **args);
int mx_launch_program(char **args);
int mx_builtins_count();

//builtins
int mx_exit_builtin(t_command *command);
int mx_export_builtin(t_command *command);
int mx_pwd_builtin(t_command *command);
int mx_echo_builtin(t_command *command);

//flags validation
bool mx_is_flag(const char *str);
bool mx_is_arguments_contains_flag(const char **args, int argc, const char flag);

static int (*builtins_funcs[])(t_command *) = {
    &mx_exit_builtin,
    &mx_export_builtin,
    &mx_pwd_builtin,
    &mx_echo_builtin,
};