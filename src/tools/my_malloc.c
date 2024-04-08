/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_malloc
*/

#include "mysh.h"

void *my_malloc(size_t size)
{
    unsigned char *ptr = malloc(size);

    my_memset(ptr, 0, size);
    return ptr;
}
