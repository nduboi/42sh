/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** display_all_alias
*/

#include "mysh.h"

static int has_space(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == ' ')
            return (1);
    }
    return (0);
}

void display_all_alias(infos_t *infos)
{
    alias_t *temp = infos->alias;

    while (temp != NULL) {
        if (has_space(temp->new_command)) {
            printf("%s\t(%s)\n", temp->base_command, temp->new_command);
            return;
        }
        printf("%s\t%s\n", temp->base_command, temp->new_command);
        temp = temp->next;
    }
    return;
}
