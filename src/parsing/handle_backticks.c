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
        buffer[strlen(buffer) - 1] = ' ';
        *bt_args = my_realloc(*bt_args, CHAR * (strlen(*bt_args) + size + 1));
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
    data->content.cmd = my_realloc(data->content.cmd,
        CHAR * (strlen(data->content.cmd) + strlen(bt_args) + 2));
    strcat(data->content.cmd, bt_args);
    strcat(data->content.cmd, " ");
    return 0;
}

int add_backtick(char **input_ptr, parsing_t *node, infos_t *infos)
{
    char *input = *input_ptr + 1;
    int len_str;
    char *buffer = my_malloc(sizeof(char));

    for (; *input != '`' && *input; input++) {
        len_str = strlen(buffer);
        buffer = realloc(buffer, CHAR * (len_str + 2));
        buffer[len_str] = *input;
        buffer[len_str + 1] = '\0';
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
