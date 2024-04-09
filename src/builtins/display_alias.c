/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** display_alias
*/

#include "mysh.h"

void display_alias(char **args, infos_t *infos)
{
    alias_t *temp = infos->alias;

    while (temp != NULL && my_strcmp(args[1], temp->base_command) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    } else {
        printf("%s\n", temp->new_command);
    }
    return;
}
