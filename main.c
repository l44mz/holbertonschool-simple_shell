#include "shell.h"

/**
 * main - entry point for the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive;
	int line_num = 0;

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			display_prompt();

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		line_num++;
		trim_newline(line);
		if (line[0] == '\0')
			continue;
		execute_command(line, argv[0], line_num);
	}

	free(line);
	return (0);
}
