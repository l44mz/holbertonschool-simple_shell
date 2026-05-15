#include "shell.h"

/**
 * main - entry point for the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: last command exit status
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive;
	int line_num = 0;
	int last_status = 0;
	int prev_status = 0;

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
		trim_newline(line);
		if (line[0] == '\0')
			continue;
		line_num++;
		prev_status = last_status;
		last_status = execute_command(line, argv[0], line_num);
		if (last_status == -2)
			break;
	}

	free(line);
	return (last_status == -2 ? prev_status : last_status);
}
