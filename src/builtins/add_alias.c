/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** add_alias
*/

#include "mysh.h"

static char *get_all_str(char **args, int i)
{
    char *temp = NULL;

    for (int j = 1; j <= i; j++) {
        temp = my_strcat_s(temp, args[j]);
        if (j != i)
            temp = my_strcat_s(temp, " ");
    }
    return temp;
}

static char *get_base_command(char **args, int *i)
{
    char *temp = NULL;

    if (args[1][0] == '"') {
        while (args[*i] != NULL && args[*i][strlen(args[*i]) - 1] != '"')
            (*i)++;
        temp = get_all_str(args, *i);
        return temp;
    } else {
        return args[1];
    }
}

static char *get_new_command(char **args, int i)
{
    char *temp = NULL;

    i++;
    while (args[i] != NULL) {
        temp = my_strcat_s(temp, args[i]);
        if (args[i + 1] != NULL) {
            temp = my_strcat_s(temp, " ");
        }
        i++;
    }
    return temp;
}

static void add_new_alias
(infos_t *infos, char *base_command, char *new_command)
{
    alias_t *new_element = malloc(sizeof(alias_t));
    alias_t *temp = infos->alias;

    while (temp != NULL) {
        if (my_strcmp(temp->base_command, base_command) == 0) {
            temp->new_command = my_strdup(new_command);
            return;
        }
        temp = temp->next;
    }
    new_element->base_command =
    my_malloc(sizeof(char) * strlen(base_command) + 1);
    strcpy(new_element->base_command, base_command);
    new_element->new_command =
    my_malloc(sizeof(char) * strlen(new_command) + 1);
    strcpy(new_element->new_command, new_command);
    new_element->next = infos->alias;
    infos->alias = new_element;
}

int add_alias(char **args, infos_t *infos)
{
    int i = 1;
    char *base_command = get_base_command(args, &i);
    char *new_command = get_new_command(args, i);

    if (strcmp(base_command, "alias") == 0 ||
    strcmp(base_command, "unalias") == 0) {
        fprintf(stderr, "%s: Too dangerous to alias that.\n", base_command);
        handle_exit_status(WRITE_STATUS, 1);
        return (1);
    }
    delete_char(base_command, '"');
    delete_char(new_command, '"');
    add_new_alias(infos, base_command, new_command);
    return (0);
}
