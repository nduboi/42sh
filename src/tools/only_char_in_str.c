/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** only_char_in_str
*/

#include "mysh.h"

bool only_char_in_str(char *str, char c)
{
    while (*str) {
        if (*str != c) {
            return false;
        }
        str++;
    }
    return true;
}
