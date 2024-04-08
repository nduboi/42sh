/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** Function that allocates memory and
** copies the string given as argument in it.
*/

#include "mysh.h"
#include <stdlib.h>

char *my_strdup(char *src)
{
    char *dest = NULL;
    int length = my_strlen(src) + 1;

    dest = malloc(sizeof(char) * length);
    my_memset(dest, 0, sizeof(char) * length);
    my_strcpy(dest, src);
    dest[length - 1] = '\0';
    return (dest);
}
