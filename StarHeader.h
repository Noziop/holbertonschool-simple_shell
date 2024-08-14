#ifndef STARHEADER_H
#define STARHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <linux/limits.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
int execute_command(char **args, char **environ, char *program_name);
char **split_string(char *str);
char *_strdup(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(const char *name, char **environ);
char *find_in_path(char *command, char **environ);
char *get_command_path(char *command, char **environ);
void execute_child_process(char *command_path, char **args, char **environ);
void print_env(char **environ);
int handle_builtin_commands(char **args, char *input, char **environ);
void remove_newline(char *str);
void display_prompt(void);
void execute_command_(char **args);
int execute_ls_with_color(char **args);

#endif /* STARHEADER_H */
