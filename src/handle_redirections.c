/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_redirections
*/

#include "mysh.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

static char *get_input_loop(char *str)
{
    char *buffer = my_malloc(sizeof(char));
    char *temp = NULL;
    size_t len = 0;

    while (1) {
        len = 0;
        temp = NULL;
        write(1, "? ", 2);
        if (getline(&temp, &len, stdin) == -1) {
            return NULL;
        }
        temp[my_strlen(temp) - 1] = '\0';
        if (my_strcmp(temp, str) == 0)
            break;
        temp[my_strlen(temp)] = '\n';
        buffer = my_realloc(buffer,
            sizeof(char) * (my_strlen(buffer) + my_strlen(temp) + 1));
        my_strcat(buffer, temp);
    }
    return buffer;
}

static int handle_double_in(char *file)
{
    int fd_wr = open("/tmp/temp_mysh_file.temp", O_WRONLY | O_CREAT | O_TRUNC,
        00644);
    char *buffer = get_input_loop(file);
    int fd_rd = 0;

    if (buffer == NULL) {
        write(1, "\n", 1);
        return STDIN_FILENO;
    }
    write(fd_wr, buffer, my_strlen(buffer));
    close(fd_wr);
    fd_rd = open("/tmp/temp_mysh_file.temp", O_RDONLY, 00444);
    return fd_rd;
}

static int handle_double_out(char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
        00644);

    return fd;
}

static int handle_in(char *file)
{
    int fd = open(file, O_RDONLY);

    return fd;
}

static int handle_out(char *file)
{
    int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC,
        00644);

    return fd;
}

static bool operate_redir
(char *input, char *redir, int (*fct_ptr)(char *), int fd2)
{
    char *temp = my_strstr(input, redir);
    char *str = NULL;
    char *file = NULL;
    int fd1 = 0;

    if (temp) {
        str = my_strdup(temp + my_strlen(redir));
        file = strtok_r(str, "<> \t", &str);
        fd1 = fct_ptr(file);
        dup2(fd1, fd2);
        close(fd1);
        return true;
    }
    return false;
}

static void find_redirs(char *input)
{
    char *ins[2] = {"<<", "<"};
    char *outs[2] = {">>", ">"};
    int (*fcts_in[2])(char *) = {handle_double_in, handle_in};
    int (*fcts_out[2])(char *) = {handle_double_out, handle_out};

    for (int i = 0; i < 2; i++) {
        if (operate_redir(input, ins[i], fcts_in[i], STDIN_FILENO)) {
            break;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (operate_redir(input, outs[i], fcts_out[i], STDOUT_FILENO)) {
            break;
        }
    }
}

static void skip_redir(char *input, int *i)
{
    if (input[*i] == '<' || input[*i] == '>') {
        *i += 1;
        for (;
            input[*i] == ' ' || input[*i] == '\t' ||
            input[*i] == '<' || input[*i] == '>';
            *i += 1);
        for (; input[*i] && input[*i] != ' ' && input[*i] != '\t'; *i += 1);
    }
}

void handle_redirections(char *input, infos_t *infos)
{
    char *copy = my_strdup(input);
    char *cmd = my_malloc(sizeof(char) * (my_strlen(input) + 1));
    int i = 0;
    int j = 0;

    find_redirs(copy);
    for (i = 0; input[i]; i++) {
        skip_redir(input, &i);
        cmd[j] = input[i];
        j += 1;
    }
    handle_cmd(cmd, infos);
}
