#include "StarHeader.h"


/**
 * handle_builtin_commands - Handles built-in shell commands
 * @args: Array of command arguments
 * @input: The input string
 * @environ: The environment variables
 * @program_name: name of shell exec to print correct error output
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int handle_builtin_commands(char **args, char *input,
					char **environ, char *program_name)
{
	if (args == NULL || args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		shell_exit(args, input, program_name);
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
 * Return: 0 if success, -1 if error.
 */

int builtin_cd(char **args)
{
	char *dir, cwd[PATH_MAX];
	char *oldpwd = getenv("OLDPWD");

	if (args[1] == NULL || strcmp(args[1], "~") == 0
	|| strcmp(args[1], "$HOME") == 0)
	{
		dir = getenv("HOME");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (oldpwd == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (-1);
		}
		dir = oldpwd;
		printf("%s\n", dir);
	}
	else
	{
		dir = args[1];
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		return (-1);
	}
	if (chdir(dir) == -1)
	{
		perror("cd");
		return (-1);
	}
	setenv("OLDPWD", cwd, 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		return (-1);
	}
	setenv("PWD", cwd, 1);
	return (0);
}

/**
 * shell_exit - exit shell terminal
 * @args: Array of command arguments
 * @input: The input string
 * @program_name: name of shell exec to print correct error output
 * Return: EXIT_SUCCESS if no argument is given by user
 *			exit_code provided by user within args[1]
 */

int shell_exit(char **args, char *input, char *program_name)
{
	int exit_code;

	if (args[1] != NULL)
	{
		if (args[1][0] == '-' || !is_valid_number(args[1]))
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", program_name, args[1]);
			return (1);
		}
		exit_code = _atoi(args[1]);
	}
	else
	{
		exit_code = 2;
	}

	free(args);
	free(input);
	exit(exit_code);
}

