#include "00-main.h"

/**
 * shell_exit - Exits the shell.
 * @args: Array of arguments passed to the exit command.
 *
 * Return: 0 on success, or an exit code if an argument is provided.
 */
int shell_exit(char **args)
{
	 (void)args;			/* Ignores arguments because they are unnecessary. */

	return (0);				/* Simply close the shell with exit code 0. */
}
