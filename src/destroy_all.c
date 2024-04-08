/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** destroy_all
*/

#include "mysh.h"

void free_double_array(char **array)
{
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

void free_chained_list(list_t **begin)
{
    list_t *node = *begin;
    list_t *temp = NULL;

    while (node) {
        temp = node->next;
        delete_node(node, NULL, begin);
        node = temp;
    }
    free(begin);
}

void free_infos(infos_t *infos)
{
    free_chained_list(infos->envs->env);
    free_chained_list(infos->envs->env_cpy);
    free(infos->envs);
    free(infos);
}
