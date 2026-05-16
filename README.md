# Simple Shell

A simple UNIX command line interpreter written in C, built as part of the Holberton School curriculum.

## Description

**hsh** is a simple UNIX shell that reads commands from the user, interprets them, and executes them. It supports both **interactive** and **non-interactive** modes.

## Requirements

- Ubuntu 20.04 LTS
- gcc compiler
- Betty style compliant

## Betty Style

All files are written in C and follow the **Betty coding style**, checked with `betty *.c *.h`.

Betty enforces:
- Max 40 lines per function
- Max 80 columns per line
- Proper comment formatting
- Correct function and variable naming

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c path.c shell.c shell.h
($) ls
hsh main.c path.c shell.c shell.h
($) ls -l /tmp
total 0
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c path.c shell.c shell.h
$ echo "ls -l" | ./hsh
total 48
-rwxr-xr-x 1 user user 8192 Jan 1 00:00 hsh
```

## Files

| File | Description |
|------|-------------|
| `main.c` | Entry point — reads input and drives the shell loop |
| `shell.c` | Core logic — prompt, tokenizer, built-ins, command execution |
| `path.c` | PATH searching — finds full path of a command |
| `shell.h` | Header file — prototypes and includes |
| `man_1_simple_shell` | Manual page for the shell |

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `env` | Print the current environment variables |

## How It Works

1. Print the prompt `($) `
2. Read user input with `getline()`
3. Tokenize the input by spaces and tabs
4. Check for built-in commands (`exit`, `env`)
5. Search for the command in `PATH`
6. Fork a child process and execute with `execve()`
7. Parent waits for child to finish
8. Repeat

## Error Handling

If a command is not found, the shell prints:

```
./hsh: 1: command: not found
```

## Man Page

To view the manual page, run:

```bash
man ./man_1_simple_shell
```

## Authors

- Sarah Alkhubaizy
- Lama Almazroa
