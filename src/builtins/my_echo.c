/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_echo
*/

#include "mysh.h"
#include <unistd.h>

int find_errors(char **args, list_t **env)
{
    list_t *node = NULL;
    int index = 1;

    while (args[index]) {
        node = find_node(env, args[index] + 1);
        if (args[index][0] == '$' && !node && my_strcmp(args[index], "$?")) {
            write(2, args[index] + 1, my_strlen(args[index] + 1));
            write(2, ": Undefined variable.\n", 22);
            handle_exit_status(WRITE_STATUS, 1);
            return 1;
        }
        index++;
    }
    return 0;
}

void display_env_var(char *arg, list_t **env)
{
    list_t *node = NULL;
    var_t *var = NULL;

    if (!my_strcmp(arg, "$?")) {
        my_putnbr(handle_exit_status(GET_STATUS, 0));
        return;
    }
    node = find_node(env, arg + 1);
    var = node->data;
    write(1, var->val, my_strlen(var->val));
}

void display_args(char **args, list_t **env)
{
    for (int index = 1; args[index]; index++) {
        if (args[index][0] == '$') {
            display_env_var(args[index], env);
        }
        if (args[index][0] != '$') {
            write(1, args[index], my_strlen(args[index]));
        }
        if (args[index + 1]) {
            write(1, " ", 1);
        }
    }
    write(1, "\n", 1);
}

int my_echo(char **args, infos_t *infos)
{
    if (!args[1]) {
        write(1, "\n", 1);
        handle_exit_status(WRITE_STATUS, 0);
        return 0;
    }
    if (find_errors(args, infos->envs->env)) {
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    display_args(args, infos->envs->env);
    handle_exit_status(WRITE_STATUS, 0);
    return 0;
}
