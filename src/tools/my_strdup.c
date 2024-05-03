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
    char *dest = my_malloc(sizeof(char) * (my_strlen(src) + 1));

    for (int i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    return (dest);
}
