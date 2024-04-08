/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** Copies a string into another
*/

#include "mysh.h"

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    return (dest);
}
