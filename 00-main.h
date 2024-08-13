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
char *get_command_path(char *command, char **environ);
void execute_child_process(char *command_path, char **args, char **environ);
int shell_exit(char **args);


#endif /* MAIN_H */
