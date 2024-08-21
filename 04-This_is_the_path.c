#include "StarHeader.h"


/**
 * get_command_path - Determines the path of the command
 * @command: The command to find
 * @environ: The environment variables
 *
 * Return: The full path of the executable, or NULL if not found
 */
char *get_command_path(char *command, char **environ)
{
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
		{
			return (strdup(command));
		}
		return (NULL);
	}
	return (find_in_path(command, environ));
}

/**
 * find_in_path - Searches for an executable in the PATH directories
 * @command: The command to find
 * @environ: The environment variables
 *
 * Return: The full path of the executable, or NULL if not found
 */
char *find_in_path(char *command, char **environ)
{
	char *path, *path_copy, *dir, *full_path;
	int command_len, dir_len;
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = _getenv("PATH", environ);
	if (!path)
		return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	command_len = strlen(command);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + command_len + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * sigint_handler - avoid ctrl+c to quit program
 * @sig: keybordentry.
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	display_prompt();
	fflush(stdout);
}

/**
 * _getenv - Gets the value of an environment variable
 * @name: The name of the environment variable
 * @environ: The current environment variables
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *_getenv(const char *name, char **environ)
{
	size_t len = strlen(name); /* Length of the environment variable name */
	int i = 0; /* Index for iterating through the environment variables */

	/* Iterate through the environment variables */
	while (environ[i])
	{
		/* Check if the current variable matches the name */
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* Return the value of the environment variable */
			return (environ[i] + len + 1);
		}
		i++;
	}
	/* Return NULL if the environment variable is not found */
	return (NULL);
}

/**
 * print_env - Prints the current environment variables
 * @environ: The environment variables
 */
void print_env(char **environ)
{
	int i = 0; /* Index for iterating through the environment variables */

	/* Iterate through the environment variables */
	while (environ[i])
	{
		/* Print each environment variable */
		printf("%s\n", environ[i]);
		i++;
	}
}
