#include "StarHeader.h"

/**
 * execute_command - Executes a command if it exists
 * @args: An array of arguments for the command
 * @environ: The environment variables
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute_command(char **args, char **environ)
{
	pid_t pid; /* Process ID for the forked process */
	char *command_path; /* Path to the command executable */

	/* Check if the command is empty */
	if (args[0] == NULL)
		return (1);

	/* Get the full path of the command */
	command_path = get_command_path(args[0], environ);
	if (command_path == NULL)
	{
		/* Print error if the command is not found */
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("Fork failed"); /* Handle fork error */
		if (command_path != args[0])
			free(command_path);
		return (-1);
	}
	if (pid == 0)
	{
		/* In the child process, execute the command */
		execute_child_process(command_path, args, environ);
	}
	else
	{
		int status; /* Status of the child process */
		/* Wait for the child process to finish */
		wait(&status);
	}
	/* Free the command path if it was dynamically allocated */
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
	/* Structure to hold file status information */
	struct stat st;
	char *command_path; /* Path to the command executable */

	/* Check if the command is a full path and exists */
	if (command[0] == '/' && stat(command, &st) == 0)
	{
		return (command);
	}
	/* Search for the command in the PATH */
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
	/* Execute the command using execve */
	if (execve(command_path, args, environ) == -1)
	{
		/* Handle execution error */
		perror("Execution failed");
		if (command_path != args[0])
			free(command_path);
		exit(EXIT_FAILURE);
	}
}
