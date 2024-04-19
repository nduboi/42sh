/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parse_input
*/

#include "mysh.h"

void handle_input(char *input, infos_t *infos)
{
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    list_t **list_parse = malloc(sizeof(list_t *));

    (void) infos;
    if (!list_parse) {
        return;
    }
    *list_parse = NULL;
    parse_input(input, list_parse);
    close(in);
    close(out);
}
