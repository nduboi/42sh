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

static void exec_and_cmd(char *cmd, infos_t *infos, int fds[2])
{
    char *new_cmd = NULL;

    if (!*cmd) {
        new_cmd = my_malloc(sizeof(char) * 2);
        new_cmd[0] = ' ';
        cmd = new_cmd;
    }
    parse_cmd(cmd, infos);
    wait(NULL);
    restart_fds(fds[0], fds[1]);
}

static void handle_ands(char *cmd, infos_t *infos, int fds[2])
{
    char *cmd2 = NULL;
    int pid = 0;
    int wstatus = 0;

    if (!my_strstr(cmd, "&&")) {
        return exec_and_cmd(cmd, infos, fds);
    }
    cmd2 = my_strstr(cmd, "&&") + 2;
    cmd[cmd2 - cmd - 2] = ' ';
    cmd[cmd2 - cmd - 1] = '\0';
    pid = fork();
    if (pid == 0) {
        handle_ands(cmd, infos, fds);
        exit(handle_exit_status(GET_STATUS, 0));
    }
    wait(&wstatus);
    handle_signal(wstatus);
    if (handle_exit_status(GET_STATUS, 0) == 0 || only_char_in_str(cmd, ' ')) {
        handle_ands(cmd2, infos, fds);
    }
}

static void handle_ors(char *cmd, infos_t *infos, int fds[2])
{
    char *cmd2 = NULL;
    int pid = 0;
    int wstatus = 0;

    if (!my_strstr(cmd, "||")) {
        return handle_ands(cmd, infos, fds);
    }
    cmd2 = my_strstr(cmd, "||") + 2;
    cmd[cmd2 - cmd - 2] = ' ';
    cmd[cmd2 - cmd - 1] = '\0';
    pid = fork();
    if (pid == 0) {
        handle_ors(cmd, infos, fds);
        exit(handle_exit_status(GET_STATUS, 0));
    }
    wait(&wstatus);
    handle_signal(wstatus);
    if (handle_exit_status(GET_STATUS, 0) != 0) {
        handle_ors(cmd2, infos, fds);
    }
}

static void handle_semi_colons(char *cmd, infos_t *infos, int fds[2])
{
    char *cmd2 = NULL;

    if (!my_strstr(cmd, ";")) {
        handle_ors(cmd, infos, fds);
        return;
    }
    cmd2 = my_strstr(cmd, ";") + 1;
    cmd[cmd2 - cmd - 1] = '\0';
    handle_ors(cmd, infos, fds);
    handle_semi_colons(cmd2, infos, fds);
}

void parse_input(char *input, infos_t *infos)
{
    int in = 0;
    int out = 0;
    char *copy = my_strdup(input);
    bool errors = errors_in_input(copy);

    free(copy);
    if (errors) {
        return;
    }
    in = dup(STDIN_FILENO);
    out = dup(STDOUT_FILENO);
    handle_semi_colons(input, infos, (int[2]) {in, out});
    close(in);
    close(out);
}
