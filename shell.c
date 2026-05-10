#include "shell.h"

/**
 * display_prompt - prints the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
 * trim_newline - removes trailing newline from a string
 * @str: the string to trim
 *
 * Return: the trimmed string
 */
char *trim_newline(char *str)
{
	size_t len;

	if (!str)
		return (NULL);

	len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';

	return (str);
}

/**
 * execute_command - forks and executes a command
 * @line: the command string
 * @prog_name: name of the shell (argv[0])
 * @line_num: current line number for error messages
 */
void execute_command(char *line, char *prog_name, int line_num)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = line;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(line, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_num, line);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}
