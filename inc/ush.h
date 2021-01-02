#pragma once

#include <features.h>

// #define __USE_XOPEN2K8
// #define __USE_XOPEN2K
// #define __USE_POSIX199506 1
// #define _POSIX_C_SOURCE 199309L
#define _POSIX_VERSION 200809L

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE
#endif

#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef __USE_XOPEN_EXTENDED
#define __USE_XOPEN_EXTENDED
#endif

// __USE_POSIX199506
#ifndef WCONTINUED
#define WCONTINUED 8
#endif

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
#include <signal.h>
#include <sys/stat.h>
#include <glob.h>
#include <fcntl.h>
#include <pwd.h>
#include <limits.h>
#include <dirent.h>

#define NR_JOBS 20
#define PATH_BUFSIZE 1024
#define COMMAND_BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

#define BACKGROUND_EXECUTION 0
#define FOREGROUND_EXECUTION 1
#define PIPELINE_EXECUTION 2

#define COMMAND_EXTERNAL 0
#define COMMAND_BUILTIN 1

#define STATUS_RUNNING 0
#define STATUS_DONE 1
#define STATUS_SUSPENDED 2
#define STATUS_CONTINUED 3
#define STATUS_TERMINATED 4

#define PROC_FILTER_ALL 0
#define PROC_FILTER_DONE 1
#define PROC_FILTER_REMAINING 2

#define COLOR_NONE "\033[m"
#define COLOR_RED "\033[1;37;41m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_GREEN "\033[0;32;32m"
#define COLOR_GRAY "\033[1;30m"

static const char *STATUS_STRING[] = {
    "running",
    "done",
    "suspended",
    "continued",
    "terminated"};
typedef struct s_process t_process;

struct s_process
{
    t_process *next;
    char *command;
    int argc;
    char **argv;
    char *input_path;
    char *output_path;
    pid_t pid;
    int type;
    int status;
};

struct s_job
{
    t_process *root;
    int id;
    char *command;
    pid_t pgid;
    int mode;
};

typedef struct s_job t_job;

struct s_shell_info
{
    t_job *jobs[NR_JOBS + 1];
    char cur_user[TOKEN_BUFSIZE];
    char cur_dir[PATH_BUFSIZE];
    char pw_dir[PATH_BUFSIZE];
};

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

extern struct s_shell_info *shell;
struct s_shell_info *shell;

typedef struct s_shell_info t_shell_info;

extern char **environ;

static char *builtins[] = {
    "exit",
    "pwd",
    "echo",
    "cd",
    "which",
    "fg",
    // #ifdef __USE_XOPEN2K
    "env",
    "export",
    "unset",
    // #endif
};

static bool have_child_proccess = false;

char *mx_getline();
void mx_replace_char(char *str, const char which, const char whith);
t_2d_arr *mx_split_commands(const char *arg);
char **mx_str_split(char *a_str, const char a_delim);
t_2d_arr *mx_parse_commands(t_2d_arr *commands);
t_command *mx_parse_str_command(char *command_str);

t_2d_arr *mx_create_2d_char_arr(void **arr, int size);
t_command *mx_create_command(char **args, int argc);
char **mx_command_to_array(t_command *command);

int mx_builtins_count();

//builtins
int mx_exit_builtin(t_process *);
int mx_pwd_builtin(t_process *);
int mx_cd_builtin(t_process *);
int mx_echo_builtin(t_process *);
int mx_which_builtin(t_process *);
int mx_fg_builtin(t_process *);

// #ifdef __USE_XOPEN2K
int mx_env_builtin(t_process *);
int mx_export_builtin(t_process *);
int mx_unset_builtin(t_process *);
// #endif

//flags validation
bool mx_is_flag(const char *str);
bool mx_is_arguments_contains_flag(const char **args, int argc, const char flag);
//signal handlers
void mx_ctrl_c_handler(int id);

static int (*builtins_funcs[])(t_process *) = {
    &mx_exit_builtin,
    &mx_pwd_builtin,
    &mx_echo_builtin,
    &mx_cd_builtin,
    &mx_which_builtin,
    &mx_fg_builtin,
    // #ifdef __USE_XOPEN2K
    &mx_env_builtin,
    &mx_export_builtin,
    &mx_unset_builtin,
    // #endif
};

char *mx_str_replace(char *orig, char *rep, char *with);
void mx_replace_exp(char **str);
char *mx_search_exp(char *str);

char *mx_strconcant_new(const char *str1, const char *str2);
void mx_which_print_res(t_list *head, bool a_flag);
bool mx_env_valid_format(const char *env);
char *mx_str_arr_to_str(const char **arr, int argc);

int mx_get_command_type(char *name);
void check_zombie();
int ush_execute_builtin_command(t_process *proc);
int get_job_id_by_pid(int pid);
t_job *get_job_by_id(int id);
int get_pgid_by_job_id(int id);
int get_proc_count(int id, int filter);
int get_next_job_id();
int print_processes_of_job(int id);
int print_job_status(int id);
int release_job(int id);
int insert_job(t_job *job);
int remove_job(int id);
int is_job_completed(int id);
int set_process_status(int pid, int status);
int set_job_status(int id, int status);
int wait_for_pid(int pid);
int wait_for_job(int id);
int ush_launch_process(t_job *job, t_process *proc, int in_fd, int out_fd, int mode);
int ush_launch_job(t_job *job);
t_process *ush_parse_command_segment(char *segment);
t_job *ush_parse_command(char *line);
void ush_print_promt();
char *ush_read_line();
void ush_init();
void ush_loop();
void sigint_handler(int signal);
char *helper_strtrim(char *line);
void ush_update_cwd_info();