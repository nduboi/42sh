/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parentheses_errors
*/

#include "mysh.h"

static bool too_many_parenthesis(char *cmd)
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

static bool badly_placed_parentheses(char *cmd, int i)
{
    for (int j = i; j > 0 && cmd[j] != '(' && cmd[j] != ';' && cmd[j] != '&' &&
        cmd[j] != '|'; j -= 1) {
        if (cmd[j] != ' ' && cmd[j] != '\t') {
            write(2, "Badly placed ()'s.\n", 19);
            return true;
        }
    }
    return false;
}

bool errors_in_parentheses(char *cmd)
{
    if (too_many_parenthesis(cmd))
        return true;
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '(' && badly_placed_parentheses(cmd, i - 1)) {
            return true;
        }
    }
    return false;
}
