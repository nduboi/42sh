/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_env
*/

#include "mysh.h"
#include <unistd.h>

void display_list(list_t *node)
{
    var_t *temp;

    if (!node) {
        return;
    }
    temp = node->data;
    write(1, temp->name, my_strlen(temp->name));
    write(1, "=", 1);
    write(1, temp->val, my_strlen(temp->val));
    write(1, "\n", 1);
    display_list(node->next);
}

int my_env(char **args, infos_t *infos)
{
    int index = 0;

    if (args[1]) {
        write(2, "env: No arguments needed.\n", 26);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    display_list(*infos->envs->env);
    handle_exit_status(WRITE_STATUS, 0);
    return 0;
}
