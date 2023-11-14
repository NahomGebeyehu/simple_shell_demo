#include "shell.h"
#include <stdlib.h>

/**
 * is_absolute_path - Check if the given path is absolute
 * @path: The path to check
 *
 * Return: 1 if the path is absolute, 0 otherwise
 */
int is_absolute_path(const char *path)
{
    return path[0] == '/';
}

/**
 * run_simple_shell - Simple Shell
 *
 * Return: Always 0 on success
 */
int run_simple_shell(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    pid_t child_pid;
    int status;
    char *path;

    path = getenv("PATH");

    signal(SIGINT, SIG_IGN);

    while (1)
    {
        write(STDOUT_FILENO, ":) ", 3);
        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        buffer[characters - 1] = '\0'; /* Remove newline character */

        if (characters > 1) /* Ignore empty lines */
        {
            char **args = parse_input(buffer);

            if (is_absolute_path(args[0]) || access(args[0], F_OK | X_OK) == 0)
            {
                child_pid = fork();
                if (child_pid == -1)
                {
                    perror("Error forking");
                }
                else if (child_pid == 0)
                {
                    /* Child process */
                    if (execve(args[0], args, NULL) == -1)
                    {
                        perror("Execution error");
                        _exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    /* Parent process */
                    waitpid(child_pid, &status, 0);
                }
            }
            else
            {
                char *full_path = search_path(args[0], path);

                if (full_path != NULL)
                {
                    child_pid = fork();
                    if (child_pid == -1)
                    {
                        perror("Error forking");
                    }
                    else if (child_pid == 0)
                    {
                        /* Child process */
                        if (execve(full_path, args, NULL) == -1)
                        {
                            perror("Execution error");
                            _exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        /* Parent process */
                        waitpid(child_pid, &status, 0);
                    }

                    free(full_path);
                }
                else
                {
                    write(STDERR_FILENO, "sh: 1: ", 6);
                    write(STDERR_FILENO, args[0], _strlen(args[0]));
                    write(STDERR_FILENO, ": not found\n", 12);
                }
            }

            free(args);
        }
    }

    free(buffer);
    return 0;
}

