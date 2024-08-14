#include "StarHeader.h"

/**
 * execute_command - Executes a command if it exists
 * @args: An array of arguments for the command
 * @environ: The environment variables
 * @program_name: name of program
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute_command(char **args, char **environ, char *program_name)
{
	char *command_path; /* Path to the command executable */

	/* Check if the command is empty */
	if (args[0] == NULL)
		return (1);

	/* Get the full path of the command */
	command_path = get_command_path(args[0], environ);
	if (command_path == NULL)
	{
		/* Print error if the command is not found */
		fprintf(stderr, "%s 1 : %s: not found\n", program_name, args[0]);
		return (1);
	}

	execute_command_(args);
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

/**
* execute_ls_with_color - Executes 'ls' with '--color=auto' option
* @args: Array of command arguments
*
* Return: (0) after execution
*/
int execute_ls_with_color(char **args)
{
	/* Allocate space for new arguments */
	char *new_args[100];
	int i = 0;

	/* Copy existing arguments */
	while (args[i] != NULL)
	{
		new_args[i] = args[i];
		i++;
	}

	/* Add '--color=auto' option */
	new_args[i++] = "--color=auto";
	new_args[i] = NULL;

	/* Execute ls with color option */
	execute_command_(new_args);
	return (0); /* Command was handled */
}

/**
 * execute_command_ - Forks and executes a command
 * @args: Array of command arguments
 */
void execute_command_(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}
	if (pid == 0)
	{
		/* In child process, execute the command */
		if (execvp(args[0], args) == -1)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* In parent process, wait for the child to finish */
		int status;

		wait(&status);
	}
}
