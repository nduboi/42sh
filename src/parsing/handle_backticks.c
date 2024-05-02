/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_backticks
*/

#include "mysh.h"

static void get_result(char **bt_args)
{
    FILE *file = fopen("/tmp/42sh_backtick.temp", "r");
    char *buffer = NULL;
    size_t size = 0;

    while (getline(&buffer, &size, file) != -1) {
        buffer[strlen(buffer) - 1] = '\0';
        *bt_args = my_realloc(*bt_args,
            CHAR * (strlen(*bt_args) + strlen(buffer)));
        strcat(*bt_args, buffer);
    }
    fclose(file);
}

static char *get_backtick_results(char *buffer, infos_t *infos)
{
    char *bt_args = NULL;
    int fd_wr = 0;
    int out;

    bt_args = my_malloc(CHAR);
    out = dup(STDOUT_FILENO);
    fd_wr = open("/tmp/42sh_backtick.temp", 01101, 00644);
    dup2(fd_wr, STDOUT_FILENO);
    close(fd_wr);
    if (handle_input(buffer, infos) == -1)
        return NULL;
    dup2(out, STDOUT_FILENO);
    get_result(&bt_args);
    return bt_args;
}

static int handle_backticks(parsing_t *data, char *buffer, infos_t *infos)
{
    char *bt_args = NULL;

    bt_args = get_backtick_results(buffer, infos);
    if (!bt_args)
        return -1;
    if (data->type == NONE_TYPE) {
        data->type = CMD;
        data->content.cmd = my_malloc(CHAR);
    }
    data->content.cmd = my_realloc(data->content.cmd,
        CHAR * (strlen(data->content.cmd) + strlen(bt_args) + 1));
    strcat(data->content.cmd, bt_args);
    return 0;
}

int add_backtick(char **input_ptr, parsing_t *node, infos_t *infos)
{
    char *input = *input_ptr + 1;
    char *buffer = my_malloc(sizeof(char));

    if (node->type == GRP) {
        write(1, "Badly placed ()'s.\n", 19);
        return -1;
    }
    for (; *input != '`' && *input; input++) {
        buffer = my_realloc(buffer, CHAR * (strlen(buffer) + 2));
        buffer[strlen(buffer)] = *input;
    }
    if (!*input) {
        write(2, "Unmatched '`'.\n", 15);
        return -1;
    }
    if (handle_backticks(node, buffer, infos) == -1)
        return -1;
    *input_ptr = input + 1;
    return 0;
}
