/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parentheses_errors
*/

#include "mysh.h"

bool too_many_parenthesis(char *cmd)
{
    int count_open = 0;
    int count_close = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '(') {
            count_open += 1;
        }
        if (cmd[i] == ')') {
            count_close += 1;
        }
        if (count_close > count_open) {
            write(2, "Too many )'s.\n", 14);
            return true;
        }
    }
    if (count_open > count_close) {
        write(2, "Too many ('s.\n", 14);
        return true;
    }
    return false;
}
