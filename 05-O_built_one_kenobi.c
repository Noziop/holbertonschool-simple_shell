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
		return (builtin_cd(args, environ));
	}

	if (strcmp(args[0], "ls") == 0)
	{
		return (execute_ls_with_color(args, environ));
	}

	if (strcmp(args[0], "help") == 0)
	{
		return (help_builtin(args));
	}

	return (1);
}

/**
 * builtin_cd - Change the current directory
 * @args: Arguments passed to cd command
 * @env: Environment variables
 * Return: 0 on success, -1 on failure
 */
int builtin_cd(char **args, char **env)
{
	char cwd[PATH_MAX], *dir = NULL, *home_dir = NULL;
	static char old_pwd[PATH_MAX] = {0};
	int i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);

	for (i = 0; env[i]; i++)
		if (strncmp(env[i], "HOME=", 5) == 0)
		{
			home_dir = env[i] + 5;
			break;
		}

	if (!args[1] || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)
		dir = home_dir;
	else if (strcmp(args[1], "-") == 0)
	{
		if (old_pwd[0] != '\0')
		{
			dir = old_pwd;
			printf("%s\n", dir);
		}
		else
			return (0);
	}
	else
		dir = args[1];

	if (chdir(dir) == 0)
	{
		strcpy(old_pwd, cwd);
		return (0);
	}

	perror("cd");
	return (-1);
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
		exit_code = EXIT_SUCCESS;
	}

	free(args);
	free(input);
	exit(exit_code);
}

/**
 * help_builtin - Provide information on internal orders.
 * @args: Array of command arguments.
 *
 * Return: return (0) function has been completed successfully.
 */

int help_builtin(char **args)
{
	char cd[] = "\033[1;32mcd\033[0m", exit[] = "\033[1;32mhelp\033[0m";

	if (args[1] == NULL) /* */
	{
		printf("here are the builtins commands we\'ve implemented so far :\n\n");
		printf("%s : allows you to navigate through the file system\n", cd);
		printf("use this command to get more help about cd :  help cd\n\n");
		printf("\033[1;32mexit\033[0m : exits the shell programm\n");
		printf("use this command to get more help about exit :  help exit\n\n");
		printf("\033[1;32menv\033[0m : displays environment variables\n");
		printf("use this command to get more help about env :  help env\n\n");
		printf("%s :  displays help about help builtin command\n", exit);
		printf("use this command to get more help about help :  help help\n\n");
	}
	else if (strcmp(args[1], "cd") == 0)
	{
		printf("cd allows you to navigate through the file system.\n");
		printf("Usage: cd [directory] example : cd /path/to/");
		printf("desired/destination. \n\nYou can also use :\n");
		printf("cd .. : moves up one level in the directory tree.");
		printf("cd - : returns to the last visited directory\n");
		printf("cd / : goes to the file system root\n");
		printf("cd  ~ or cd $HOME or cd : goes to home directory\n ");
	}
	else if (strcmp(args[1], "exit") == 0)
	{
		printf("exit: quits the shell programm.\nUsage: exit [return code]\n");
		printf("you can then, verify exit code with the command : \'echo $?\'\n");
	}
	else if (strcmp(args[1], "env") == 0)
	{
		printf("env: Displays environment variables.\nUsage: env\n");
	}
	else if (strcmp(args[1], "help") == 0)
	{
		printf("help: Displays these informations.\n");
		printf("To display help for help builtin, simply type: \'help help\'\n");
		printf("(you're already here nonetheless, as you've typed \"help help\")\n");
	}
	return (0);
}
