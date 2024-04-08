/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_memset
*/

#include "mysh.h"

void *my_memset(void *ptr, int val, size_t len)
{
    unsigned char *dest = (unsigned char *) ptr;

    while (len > 0) {
        *dest = val;
        dest++;
        len--;
    }
    return dest;
}
