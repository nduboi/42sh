/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** check_if_is_an_alias
*/

#include "mysh.h"

static char *get_all_str(char **args)
{
    char *temp = NULL;

    for (int i = 0; args[i] != NULL; i++) {
        temp = my_strcat_s(temp, args[i]);
        if (args[i + 1] != NULL)
            temp = my_strcat_s(temp, " ");
    }
    return temp;
}

static char **check_if_recursivity(char **args, alias_t *temp, infos_t *infos)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (!my_strcmp(temp->base_command, args[i]))
            return args;
    }
    args = check_if_is_an_alias(args, infos);
    return args;
}

char **check_if_is_an_alias(char **args, infos_t *infos)
{
    alias_t *temp = infos->alias;

    while (temp != NULL) {
        if (strcmp(temp->base_command, args[0]) == 0) {
            args[0] = my_strdup(temp->new_command);
            args = str_to_word_array(get_all_str(args));
            args = check_if_recursivity(args, temp, infos);
            return args;
        }
        temp = temp->next;
    }
    return args;
}
