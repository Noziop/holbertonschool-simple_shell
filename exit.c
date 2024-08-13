#include "00-main.h"

/**
 * shell_exit - Exits the shell.
 * @args: Array of arguments passed to the exit command.
 *
 * Return: 0 on success, or an exit code if an argument is provided.
 */
int shell_exit(char **args)
{
	if (args[1])
	/* Convert the output code supplied into a number. */
	{
		char *endptr;
		long exit_code = strtol(args[1], &endptr, 10);

		if (*endptr) /* Check that the conversion is valid.*/
		{
			fprintf(stderr, "exit: %s: Argument non valide\n", args[1]);
			return (1);
		}

		exit((int)exit_code); /* Close the shell. */
	}
	/* If no arguments are supplied, exit as normal. */
	exit(0);
}
