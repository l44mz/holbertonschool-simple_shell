#ifndef SHELL_H
#define SHELL_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
extern char **environ;
 
void display_prompt(void);
void execute_command(char *line, char *prog_name, int line_num);
char *trim_newline(char *str);
 
#endif

