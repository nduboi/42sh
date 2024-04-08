/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parse_input
*/

#include "mysh.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static void operate_cmds(int pipe_fd, int fd, char *cmd, infos_t *infos)
{
    dup2(pipe_fd, fd);
    close(pipe_fd);
    handle_redirections(cmd, infos);
    exit(handle_exit_status(GET_STATUS, 0));
}

void handle_pipe(char *token, infos_t *infos)
{
    int pid = 0;
    int fd[2];
    int pipe_status = pipe(fd);

    pid = fork();
    if (pid == -1 || pipe_status == -1) {
        write(2, "Fork error\n", 11);
        return;
    }
    if (pid == 0) {
        close(fd[0]);
        operate_cmds(fd[1], STDOUT_FILENO, token, infos);
    } else {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
    }
}

void parse_cmd(char *data, infos_t *infos)
{
    int count = count_tokens(data, "|");
    char *copy = my_strdup(data);
    char *token = strtok_r(copy, "|", &copy);

    for (; count; count--) {
        if (count == 1) {
            handle_redirections(token, infos);
        } else {
            handle_pipe(token, infos);
        }
        token = strtok_r(copy, "|", &copy);
    }
}

static list_t **find_semi_colons(char *input)
{
    list_t **semi_colons = malloc(sizeof(list_t *));
    char *token = strtok_r(input, ";", &input);

    *semi_colons = NULL;
    while (token) {
        add_node(semi_colons, token);
        token = strtok_r(input, ";", &input);
    }
    return semi_colons;
}

void parse_input(char *input, infos_t *infos)
{
    list_t **cmds = find_semi_colons(input);
    list_t *node = *cmds;
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);

    while (node) {
        if (!errors_in_cmd(node->data)) {
            parse_cmd(node->data, infos);
            wait(NULL);
            restart_fds(in, out);
        }
        node = node->next;
    }
    close(in);
    close(out);
}
