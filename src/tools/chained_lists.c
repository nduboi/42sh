/*
** EPITECH PROJECT, 2024
** alban
** File description:
** chained_lists
*/

#include "mysh.h"
#include <stdlib.h>
#include <unistd.h>

void add_node(list_t **begin, void *data)
{
    list_t *new = malloc(sizeof(list_t));
    list_t *temp = *begin;

    new->data = data;
    if (!temp) {
        new->next = *begin;
        *begin = new;
        return;
    }
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new;
    new->next = NULL;
}

void delete_node(list_t *node, list_t *last, list_t **list)
{
    if (last == NULL) {
        *list = node->next;
    } else {
        last->next = node->next;
    }
    free(node->data);
    free(node);
}

int chained_list_size(list_t **begin)
{
    int result = 0;
    list_t *node = *begin;

    while (node) {
        result++;
        node = node->next;
    }
    return result;
}

char **chained_list_to_normal(list_t **begin)
{
    int size = chained_list_size(begin);
    char **result = malloc(sizeof(char *) * (size + 1));
    list_t *node = *begin;
    var_t *temp = NULL;
    int i = 0;

    while (node) {
        temp = node->data;
        result[i] = malloc(sizeof(char)
            * (my_strlen(temp->name) + my_strlen(temp->val) + 2));
        my_memset(result[i], 0, sizeof(char)
            * (my_strlen(temp->name) + my_strlen(temp->val) + 2));
        my_strcat(result[i], temp->name);
        my_strcat(result[i], "=");
        my_strcat(result[i], temp->val);
        node = node->next;
        i++;
    }
    result[size] = NULL;
    return result;
}

list_t *find_node(list_t **env, char *name)
{
    list_t *node = *env;
    var_t *temp = NULL;

    while (node) {
        temp = node->data;
        if (!my_strcmp(temp->name, name)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}
