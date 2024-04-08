/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_realloc
*/

#include "mysh.h"

void *my_realloc(void *ptr, size_t size)
{
    unsigned char *dest = my_malloc(size);
    unsigned char *src = (unsigned char *) ptr;

    my_strcpy(dest, src);
    return (void *) dest;
}
