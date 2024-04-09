/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** delete_char
*/

#include "mysh.h"

void delete_char(char *str, char c)
{
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}
