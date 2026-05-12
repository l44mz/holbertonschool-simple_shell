#include "shell.h"

/**
 * display_prompt - prints the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
 * trim_newline - removes trailing whitespace from a string
 * @str: the string to trim
 *
 * Return: the trimmed string
 */
char *trim_newline(char *str)
{
	int len;

	if (!str)
		return (NULL);

	len = (int)strlen(str) - 1;
	while (len >= 0 && (str[len] == '\n' || str[len] == ' ' ||
		str[len] == '\t' || str[len] == '\r'))
	{
		str[len] = '\0';
		len--;
	}

	return (str);
}

/**
 * tokenize - splits a line into an array of tokens
 * @line: the input string (will be modified by strtok)
 *
 * Return: NULL-terminated array of tokens, or NULL on failure
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token;
	int count = 0;
	int i;

	tokens = malloc(sizeof(char *) * (strlen(line) + 1));
	if (!tokens)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		tokens[count++] = token;
		token = strtok(NULL, " \t");
	}
	tokens[count] = NULL;

	if (count == 0)
	{
		free(tokens);
		return (NULL);
	}

	/* shrink to exact size */
	i = count + 1;
	(void)i;
	return (tokens);
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
	char **args;
	char *cmd;

	args = tokenize(line);
	if (!args)
		return;

	cmd = args[0];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(args);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_num, cmd);
			free(args);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(args);
	}
}
