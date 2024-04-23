/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** tu lis les headers toi?
** (globbing function au cas où)
*/

#include "mysh.h"
#include <unistd.h>
#include <string.h>

static void globbing_write(char **args, int *i, int *j, int len)
{
    if (args[*i][*j] == '\\' && args[*i][*j + 1] != '\\')
        return;
    if ((args[*i][*j + 1] == '\0' && *i + 1 < len)
        || args[*i][*j + 1] == ' ') {
        write(1, &args[*i][*j], 1);
        write(1, "", 1);
        return;
    }
    write(1, &args[*i][*j], 1);
}

static int globbing_final_error_cases(char **args, int *i, int *j)
{
    if (args[*i][*j] == '\\' && args[*i][*j + 1] == '\\') {
        if (args[*i][*j + 2] == 'f') {
            args[*i][*j + 2] = '\f';
            *j = *j + 1;
            return 1;
        }
        if (args[*i][*j + 2] == '0') {
            write(1, "", 1);
            *j = *j + 2;
            return 1;
        }
    }
    return 0;
}

static int globbing_other_error_cases(char **args, int *i, int *j)
{
    if (args[*i][*j] == '\\' && args[*i][*j + 1] == '\\') {
        if (args[*i][*j + 2] == 'b') {
            args[*i][*j + 2] = '\b';
            *j = *j + 1;
            return 1;
        }
        if (args[*i][*j + 2] == 'a') {
            args[*i][*j + 2] = '\a';
            *j = *j + 1;
            return 1;
        }
        if (args[*i][*j + 2] == 'v') {
            args[*i][*j + 2] = '\v';
            *j = *j + 1;
            return 1;
        }
        if (globbing_final_error_cases(args, i, j) == 1)
            return 1;
    }
    return 0;
}

static void globbing_error_cases(char **args, int *i, int *j, int len)
{
    if (args[*i][*j] == '\\' && args[*i][*j + 1] == '\\') {
        if (args[*i][*j + 2] == 't') {
            args[*i][*j + 2] = '\t';
            *j = *j + 1;
            return;
        }
        if (args[*i][*j + 2] == 'r') {
            args[*i][*j + 2] = '\r';
            *j = *j + 1;
            return;
        }
        if (args[*i][*j + 2] == 'n') {
            args[*i][*j + 2] = '\n';
            *j = *j + 1;
            return;
        }
        if (globbing_other_error_cases(args, i, j) == 1)
            return;
    }
    globbing_write(args, i, j, len);
}

int my_globbing(char **args, infos_t *infos)
{
    int len = my_arrlen(args);

    (void) infos;
    for (int i = 1; i < len; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            globbing_error_cases(args, &i, &j, len);
        }
    }
    return 0;
}
