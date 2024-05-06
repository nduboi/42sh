/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parse_local_var
*/

#include "mysh.h"

char *get_local_val(char *var, infos_t *infos)
{
    local_var_t *tmp = infos->vars;

    while (tmp != NULL) {
        if (strcmp(var, tmp->var) == 0)
            return (strdup(tmp->val));
        tmp = tmp->next;
    }
    return (NULL);
}
