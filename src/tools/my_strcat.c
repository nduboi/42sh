/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** Concatenates two strings.
*/

#include "mysh.h"

char *my_strcat(char *dest, char *src)
{
    int start_cat = my_strlen(dest);
    int length = my_strlen(src);

    for (int i = 0; i < length; i += 1) {
        dest[start_cat + i] = src[i];
    }
    return (dest);
}
