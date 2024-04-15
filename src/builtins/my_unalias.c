/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** my_unalias
*/

#include "mysh.h"

static void delete_alias(alias_t *alias, alias_t *prev, infos_t *infos)
{
    if (alias == infos->alias) {
        infos->alias = infos->alias->next;
        free(alias);
    } else {
        prev->next = alias->next;
        free(alias);
    }
}

static void find_alias(char *alias, infos_t *infos)
{
    alias_t *temp = infos->alias;
    alias_t *prev;

    while (temp != NULL) {
        if (strcmp(alias, temp->base_command) == 0) {
            delete_alias(temp, prev, infos);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

int my_unalias(char **args, infos_t *infos)
{
    for (int i = 1; args[i] != NULL; i++) {
        find_alias(args[i], infos);
    }
    return (0);
}
