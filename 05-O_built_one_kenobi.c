#include "StarHeader.h"


/**
 * handle_builtin_commands - Handles built-in shell commands
 * @args: Array of command arguments
 * @input: The input string
 * @environ: The environment variables
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int handle_builtin_commands(char **args, char *input, char **environ)
{
	if (args == NULL || args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(input);
		exit(EXIT_SUCCESS);
	}

	if (strcmp(args[0], "env") == 0)
	{
		print_env(environ);
		return (0);
	}

	if (strcmp(args[0], "cd") == 0)
	{
		return (builtin_cd(args));
	}

	if (strcmp(args[0], "ls") == 0)
	{
		return (execute_ls_with_color(args));
	}

	return (1);
}

/**
 * builtin_cd - handle the cd cmd
 * @args: command and arguments
 *
 * Return: 0 if success.
 */

int builtin_cd(char **args)
{
	char *home_dir = getenv("HOME");
	char *old_pwd = getenv("OLDPWD");
	char cwd[PATH_MAX];

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (old_pwd)
		{
			if (chdir(old_pwd) != 0)
				perror("cd");
			else
				printf("%s\n", old_pwd);
		}
		else
			fprintf(stderr, "cd: OLDPWD not set\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	else
		perror("getcwd");

	return (0);
}
