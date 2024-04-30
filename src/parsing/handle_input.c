/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_input
*/

#include "mysh.h"

static void handle_or_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    (void) fds;
    if (!*skip) {
        handle_redirections(data, infos);
    }
    *skip = false;
    if (handle_exit_status(GET_STATUS, 0) == 0)
        *skip = true;
}

static void handle_and_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    (void) fds;
    if (!*skip) {
        handle_redirections(data, infos);
    }
    *skip = false;
    if (handle_exit_status(GET_STATUS, 0) != 0)
        *skip = true;
}

static void handle_semi_colon_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    if (!*skip) {
        handle_redirections(data, infos);
    }
    restart_fds(fds[0], fds[1]);
    *skip = false;
}

static void handle_pipe_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    int pipe_fds[2];

    (void) fds;
    if (*skip)
        return;
    pipe(pipe_fds);
    if (fork() == 0) {
        close(pipe_fds[0]);
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[1]);
        handle_redirections(data, infos);
        exit(handle_exit_status(GET_STATUS, 0));
    } else {
        close(pipe_fds[1]);
        dup2(pipe_fds[0], STDIN_FILENO);
        close(pipe_fds[0]);
    }
}

static void handle_end_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    if (!*skip) {
        handle_redirections(data, infos);
    }
    restart_fds(fds[0], fds[1]);
}

void execute_commands(list_t **list_parse, infos_t *infos)
{
    list_t *node = *list_parse;
    parsing_t *data = NULL;
    bool skip = false;
    void (*fct_ptrs[6])(parsing_t *, infos_t *, bool *, int[2]) = {
        NULL, handle_semi_colon_cmd, handle_and_cmd, handle_or_cmd,
        handle_pipe_cmd, handle_end_cmd
    };
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);

    while (node) {
        data = node->data;
        fct_ptrs[data->link](data, infos, &skip, (int[2]) {in, out});
        node = node->next;
    }
    close(in);
    close(out);
}

int handle_input(char *input, infos_t *infos)
{
    list_t **list_parse = malloc(sizeof(list_t *));

    if (!list_parse)
        return -1;
    *list_parse = NULL;
    if (too_many_parenthesis(input) ||
        parse_input(input, list_parse, infos) == -1) {
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    execute_commands(list_parse, infos);
    return 0;
}
