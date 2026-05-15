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
 * builtin_env - prints the current environment
 */
void builtin_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}

/**
 * execute_command - forks and executes a command
 * @line: the command string
 * @prog_name: shell name
 * @line_num: line number
 *
 * Return: command exit status
 */
int execute_command(char *line, char *prog_name, int line_num)
{
	pid_t pid;
	int status;
	char **args;
	char *cmd, *full_path;

	args = tokenize(line);
	if (!args)
		return (0);

	cmd = args[0];
	
	if (strcmp(cmd, "exit") == 0)
	{
		free(args);
		return (-2);
	}

	
	if (strcmp(cmd, "env") == 0)
	{
		builtin_env();
		free(args);
		return (0);
	}

	full_path = find_in_path(cmd);

	if (!full_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_num, cmd);
		free(args);
		return (127);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free(args);
		return (1);
	}

	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror("execve");
		free(full_path);
		free(args);
		exit(127);
	}
	else
	{
		wait(&status);
		free(full_path);
		free(args);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (1);
}
