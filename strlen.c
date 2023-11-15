#include "shell.h"

/**
 * _strlen - Custom implementation of strlen
 * @s: Input string
 *
 * Return: Length of the string
 */
size_t _strlen(const char *s)
{
    size_t len = 0;

    while (s[len] != '\0')
        len++;

    return len;
}

/**
 * _strcmp - Custom implementation of strcmp
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if strings are equal, positive if s1 > s2, negative if s1 < s2
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
