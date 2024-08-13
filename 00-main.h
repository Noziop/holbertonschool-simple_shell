#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
int execute_command(char **args, char **environ);
char **split_string(char *str);
char *_strdup(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(const char *name, char **environ);
char	*find_in_path(char *command, char **environ);

void exec_command(char **args);
void wait_for_child(void);
int shell_exit(char **args);
int shell_env(char **args, char **environ);
void print_env(char **environ);
void print_path_directories(char **environ);

#endif /* MAIN_H */
