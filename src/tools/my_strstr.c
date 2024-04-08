/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_strstr
*/

#include "mysh.h"
#include <stddef.h>

char *my_strstr(char *hay, char *needle)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(needle);

    for (i = 0; hay[i]; i++) {
        for (j = 0; needle[j] && hay[i + j] == needle[j]; j++) {
        }
        if (j == len) {
            return hay + i;
        }
        i += j;
    }
    return NULL;
}
