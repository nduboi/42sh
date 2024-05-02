/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_input
*/

#include "mysh.h"

static int handle_or_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    int status = 0;

    (void) fds;
    if (!*skip) {
        status = handle_redirections(data, infos);
    }
    *skip = false;
    if (handle_exit_status(GET_STATUS, 0) == 0)
        *skip = true;
    return status;
}

static int handle_and_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    int status = 0;

    (void) fds;
    if (!*skip) {
        status = handle_redirections(data, infos);
    }
    *skip = false;
    if (handle_exit_status(GET_STATUS, 0) != 0)
        *skip = true;
    return status;
}

static int handle_semi_colon_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    int status = 0;

    if (!*skip) {
        status = handle_redirections(data, infos);
    }
    restart_fds(fds[0], fds[1]);
    *skip = false;
    return status;
}

static int handle_pipe_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    int pipe_fds[2];

    (void) fds;
    if (*skip)
        return 0;
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
    return 0;
}

static int handle_end_cmd
(parsing_t *data, infos_t *infos, bool *skip, int fds[2])
{
    int status = 0;

    if (!*skip) {
        status = handle_redirections(data, infos);
    }
    restart_fds(fds[0], fds[1]);
    return status;
}

int execute_commands(list_t **list_parse, infos_t *infos)
{
    list_t *node = *list_parse;
    parsing_t *data = NULL;
    bool skip = false;
    int (*fct_ptrs[6])(parsing_t *, infos_t *, bool *, int[2]) = {
        NULL, handle_semi_colon_cmd, handle_and_cmd, handle_or_cmd,
        handle_pipe_cmd, handle_end_cmd};
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    int status = 0;

    while (node) {
        data = node->data;
        status = fct_ptrs[data->link](data, infos, &skip, (int[2]) {in, out});
        if (status == -1)
            break;
        node = node->next;
    }
    close(in);
    close(out);
    return status;
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
    if (execute_commands(list_parse, infos) == -1)
        return 1;
    return 0;
}
