#include "shell.h"
#include <stdlib.h>

/**
 * search_path - This searchs for the command in the PATH directories
 * @command: This is the command to search for
 * @path: This is the PATH environment variable
 * Return: Full path to the command if found, NULL otherwise
 */
char *search_path(char *command, char *path)
{
    char *token, *full_path;
    char *path_copy = NULL;
    size_t path_len, token_len, full_path_len, i, j;

    path_len = _strlen(path);

    path_copy = malloc(path_len + 1);
    if (path_copy == NULL)
    {
        perror("malloc");
        _exit(EXIT_FAILURE);
    }

    for (i = 0; i < path_len; i++)
        path_copy[i] = path[i];
    path_copy[i] = '\0';

    token = path_copy;

    while (*token != '\0')
    {
        token_len = 0;
        while (token[token_len] != '\0' && token[token_len] != ':' && token[token_len] != '\n')
            token_len++;

        full_path_len = token_len + _strlen(command) + 2;
        full_path = malloc(full_path_len);
        if (full_path == NULL)
        {
            perror("malloc");
            _exit(EXIT_FAILURE);
        }

        for (i = 0; i < token_len; i++)
            full_path[i] = token[i];

        full_path[i] = '/';
        i++;

        for (j = 0; j < _strlen(command); j++, i++)
            full_path[i] = command[j];

        full_path[i] = '\0';

        if (access(full_path, F_OK | X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);

        token += token_len;
        if (*token == ':' || *token == '\n')
            token++;
    }

    free(path_copy);
    return NULL;
}
