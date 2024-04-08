/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_unsetenv
*/

#include "mysh.h"
#include <string.h>
#include <unistd.h>

void del_var(list_t **env, char *arg)
{
    list_t *node = *env;
    list_t *last = NULL;
    var_t *temp = NULL;

    while (node) {
        temp = node->data;
        if (my_strcmp(temp->name, arg) == 0) {
            delete_node(node, last, env);
            return;
        }
        last = node;
        node = node->next;
    }
}

int handle_vars(char **args, list_t **env)
{
    for (int i = 1; args[i]; i++) {
        if (my_strcmp(args[i], "*") == 0) {
            write(2, "unsetenv: Can't take '*' argument.\n", 35);
            handle_exit_status(WRITE_STATUS, 1);
            return -1;
        }
        del_var(env, args[i]);
    }
    return 0;
}

int my_unsetenv(char **args, infos_t *infos)
{
    if (!args[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    if (handle_vars(args, infos->envs->env) == -1) {
        return -1;
    }
    handle_exit_status(WRITE_STATUS, 0);
    return 0;
}
