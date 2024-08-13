#include "00-main.h"


/**
 * execute_command - Executes a command if it exists
 * @args: An array of arguments for the command
 * @environ: The environment variables
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute_command(char **args, char **environ)
{
	pid_t pid;
	char *command_path;

	if (args[0] == NULL)
		return (1);

	command_path = get_command_path(args[0], environ);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		if (command_path != args[0])
			free(command_path);
		return (-1);
	}
	if (pid == 0)
	{
		execute_child_process(command_path, args, environ);
	}
	else
	{
		int status;

		wait(&status);
	}

	if (command_path != args[0])
		free(command_path);

	return (1);
}

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
	char *command_path;

	if (command[0] == '/' && stat(command, &st) == 0)
	{
		return (command);
	}
	command_path = find_in_path(command, environ);
	return (command_path);
}

/**
 * execute_child_process - Executes the command in the child process
 * @command_path: The path of the command
 * @args: The arguments for the command
 * @environ: The environment variables
 */
void execute_child_process(char *command_path, char **args, char **environ)
{
	if (execve(command_path, args, environ) == -1)
	{
		perror("Execution failed");
		if (command_path != args[0])
			free(command_path);
		exit(EXIT_FAILURE);
	}
}

/**
 * find_in_path - Searches for an executable in the PATH directories
 * @command: The command to find
 * @environ: The environment variables
 *
 * Return: The full path of the executable, or NULL if not found
 */
char	*find_in_path(char *command, char **environ)
{
	char	*path_env = _getenv("PATH", environ);
	char	*path_copy, *token, *full_path;
	struct stat	st;

	if (!path_env)
		return (NULL);

	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
