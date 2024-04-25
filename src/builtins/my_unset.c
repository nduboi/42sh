/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_unset
*/

#include "mysh.h"

void free_node_local(local_var_t *node)
{
    free(node->val);
    free(node->var);
    free(node);
}

void remove_node_local(char *var, infos_t *infos)
{
    local_var_t *tmp = infos->vars;
    local_var_t *freetmp = NULL;

    if (strcmp(tmp->var, var) == 0) {
        infos->vars = infos->vars->next;
        free_node_local(tmp);
        return;
    }
    while (tmp->next != NULL) {
        if (strcmp(var, tmp->next->var) == 0) {
            freetmp = tmp->next;
            tmp->next = tmp->next->next;
            free_node_local(freetmp);
            break;
        }
        tmp = tmp->next;
    }
}

int my_unset(char **av, infos_t *infos)
{
    if (my_arrlen(av) == 1) {
        dprintf(2, "unset: Too few arguments.\n");
        return (1);
    }
    if (infos->vars == NULL)
        return (0);
    for (int i = 1; av[i] != NULL; i++) {
        remove_node_local(av[i], infos);
    }
    return (0);
}
