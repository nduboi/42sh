/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** recall_by_id
*/

#include "mysh.h"

char *recall_by_id(int id, infos_t *infos)
{
    history_t *tmp = infos->history;

    while (tmp != NULL) {
        if (id == 0)
            return (strdup(tmp->line));
        id -= 1;
        tmp = tmp->next;
    }
    return (NULL);
}
