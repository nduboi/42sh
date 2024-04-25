/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** is_delim
*/

#include "mysh.h"

bool is_delim(char *str)
{
    char *delims[5] = {";", "||", "|", "&&", NULL};

    for (int i = 0; delims[i]; i++) {
        if (!strncmp(str, delims[i], strlen(delims[i]))) {
            return true;
        }
    }
    return false;
}
