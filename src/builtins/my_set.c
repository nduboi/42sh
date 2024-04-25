/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_set
*/

#include "mysh.h"

static int display_vars(local_var_t *vars)
{
    local_var_t *tmp = vars;

    while (tmp != NULL) {
        printf("%s\t%s\n", tmp->var, tmp->val);
        tmp = tmp->next;
    }
    return (0);
}

int change_node(char *var, char *val, infos_t *info)
{
    local_var_t *tmp = info->vars;

    while (tmp != NULL) {
        if (strcmp(tmp->var, var) == 0) {
            free(tmp->val);
            tmp->val = strdup(val);
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

void add_node_var(char *var, char *val, infos_t *info)
{
    local_var_t *new = malloc(sizeof(local_var_t) * 1);

    if (change_node(var, val, info) == 1) {
        free(new);
        return;
    }
    new->var = strdup(var);
    new->val = strdup(val);
    new->next = info->vars;
    info->vars = new;
}

int error_cases_local(char *var)
{
    if (var[0] >= '0' && var[0] <= '9') {
        dprintf(2, "set: Variable name must begin with a letter.\n");
        return (1);
    }
    for (int i = 0; var[i] != '\0'; i++) {
        if (is_alpha(var[i]) == 0 && is_num(var[i]) == 0) {
            dprintf(2,
                "set: Variable name must contain alphanumeric characters.\n");
            return (1);
        }
    }
    return (0);
}

int local_loop(char **av, infos_t *infos)
{
    for (int i = 1; av[i] != NULL; i++) {
        if (av[i][0] == '=')
            continue;
        if (error_cases_local(av[i]) == 1)
            return (1);
        if (av[i + 1] == NULL || (av[i + 1][0] == '=' && av[i + 2] == NULL)
            || av[i + 1][0] != '=') {
            add_node_var(av[i], "\0", infos);
            continue;
        }
        if (av[i + 1][0] == '=' && av[i + 2] != NULL) {
            add_node_var(av[i], av[i + 2], infos);
            i += 2;
        }
    }
    free(av);
    return (0);
}

int my_set(char **args, infos_t *infos)
{
    int len = my_arrlen(args);
    char *line = arr_to_str(args);
    char **av = NULL;

    if (len == 1)
        return (display_vars(infos->vars));
    line = insert_spaces(line);
    av = str_to_word_array(line);
    return (local_loop(av, infos));
}
