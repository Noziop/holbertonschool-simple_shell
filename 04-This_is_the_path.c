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

	/* Check if the command starts with '/' or '.' (absolute or relative path) */
	if (command[0] == '/' || command[0] == '.')
	{
		/* Check if the file exists and is accessible */
		if (stat(command, &st) == 0)
		{
			/* If it exists, return a copy of the command */
			return (strdup(command));
		}
		/* If the file doesn't exist or isn't accessible, return NULL */
		return (NULL);
	}

	/* If it's not an absolute or relative path, search in PATH */
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

	/* Check if command is already a path */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)/* If it exists, return a copy */
			return (strdup(command));
		return (NULL);
	}
	path = _getenv("PATH", environ);/* Get the PATH environment variable */
	if (!path)
		return (NULL);
	path_copy = strdup(path);/*copy of PATH to avoid modifying the original */
	if (!path_copy)
		return (NULL);
	command_len = strlen(command);
	/* Tokenize PATH and iterate through each directory */
	dir = strtok(path_copy, ":");
	while (dir)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + command_len + 2);/* Allocate memory full path */
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);/* Construct full path */
		if (stat(full_path, &st) == 0)/* Check if file exists and is executable */
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);/* Free memory if file not found in this directory */
		dir = strtok(NULL, ":");
	}
	free(path_copy);/* Free PATH copy and return NULL if command not found */
	return (NULL);
}

/**
 * sigint_handler - avoid ctrl+c to quit program
 * @sig: keyboard entry
 */
void sigint_handler(int sig)
{
	/* Suppress unused parameter warning */
	(void)sig;

	/* Print a new line to move to the next line after ^C */
	write(STDOUT_FILENO, "\n", 1);

	/* Display the shell prompt again */
	display_prompt();

	/* Flush the output buffer to ensure prompt is displayed immediately */
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
