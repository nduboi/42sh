/*
** EPITECH PROJECT, 2024
** replce env var
** File description:
** environement_var
*/

#include "mysh.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string.h>

static char *path_parsing(char *value, infos_t *info)
{
    char *value_env = get_env_var(value, info->envs->env);
    char *cpy = my_strdup(value_env);

    for (int i = 0; cpy[i] != '\0'; i++) {
        if (cpy[i] == ':')
            cpy[i] = ' ';
    }
    return cpy;
}

char *special_var(char *value)
{
    if (my_strcmp(value, "term") == 0) {
        free(value);
        value = strdup("TERM");
    } else if (my_strcmp(value, "cwd") == 0) {
        free(value);
        value = strdup("PWD");
    }
    if (my_strcmp(value, "status") == 0) {
        free(value);
        value = strdup("?");
    } else if (my_strcmp(value, "home") == 0) {
        free(value);
        value = strdup("HOME");
    }
    if (my_strcmp(value, "group") == 0) {
        free(value);
        value = strdup("GROUP");
    }
    return value;
}

char *append_env_value(char *value, infos_t *info)
{
    char *value_env = NULL;

    if (my_strcmp(value, "?") == 0)
        value_env = my_stock_nbr(handle_exit_status(GET_STATUS, 0));
    else if (my_strcmp(value, "path") == 0)
        value_env = path_parsing("PATH", info);
    else
        value_env = get_env_var(value, info->envs->env);
    return value_env;
}
