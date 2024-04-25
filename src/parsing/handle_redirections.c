/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_redirections
*/

#include "mysh.h"

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

static void dup_fds(int old_fd, int new_fd)
{
    dup2(old_fd, new_fd);
    close(old_fd);
}

static void operate_redirs(redirs_t *redirs)
{
    int fd;

    if (redirs->in) {
        fd = open(redirs->keyword_in, O_RDONLY);
        dup_fds(fd, STDIN_FILENO);
    }
    if (redirs->d_in) {
        fd = handle_double_in(redirs->keyword_d_in);
        dup_fds(fd, STDIN_FILENO);
    }
    if (redirs->out) {
        fd = open(redirs->keyword_out, O_CREAT | O_WRONLY | O_TRUNC, 00644);
        dup_fds(fd, STDOUT_FILENO);
    }
    if (redirs->d_out) {
        fd = open(redirs->keyword_d_out, O_CREAT | O_WRONLY | O_APPEND, 00644);
        dup_fds(fd, STDOUT_FILENO);
    }
}

void handle_redirections(parsing_t *data, infos_t *infos)
{
    if (data->redirs.in && access(data->redirs.keyword_in, F_OK) != 0) {
        error_message(data->redirs.keyword_in, errno);
        handle_exit_status(WRITE_STATUS, 1);
        return;
    }
    operate_redirs(&data->redirs);
    handle_cmd(data->content.cmd, infos);
}

static char *get_redir(char **input_ptr)
{
    char *redirs[5] = {">>", "<<", ">", "<", NULL};
    char *input = *input_ptr;

    for (int i = 0; redirs[i]; i++) {
        if (!strncmp(input, redirs[i], strlen(redirs[i]))) {
            *input_ptr += strlen(redirs[i]);
            return redirs[i];
        }
    }
    return NULL;
}

static char *get_keyword(char **input_ptr)
{
    char *result = my_malloc(sizeof(char));
    char *input = *input_ptr;
    int len;

    while (*input == ' ' || *input == '\t') {
        input += 1;
    }
    while (*input && *input != ' ' && *input != '\t' && !is_delim(input)
        && *input != '<' && *input != '>') {
        len = strlen(result);
        result = realloc(result, sizeof(char) * (len + 2));
        result[len] = *input;
        result[len + 1] = '\0';
        input++;
    }
    *input_ptr = input;
    return result;
}

static int find_index(char **list, char *str)
{
    for (int i = 0; list[i]; i++) {
        if (!strcmp(str, list[i])) {
            return i;
        }
    }
    return -1;
}

static bool ambiguous_redirect(int index, bool *redir_bool[])
{
    if (index & 0b1) {
        if (*(redir_bool[index]) || *(redir_bool[(index + 2) % 4])) {
            write(2, "Ambiguous output redirect.\n", 27);
            return true;
        }
    } else {
        if (*(redir_bool[index]) || *(redir_bool[(index + 2) % 4])) {
            write(2, "Ambiguous input redirect.\n", 26);
            return true;
        }
    }
    return false;
}

int add_redir(char **input_ptr, redirs_t *red)
{
    char *redir = get_redir(input_ptr);
    char *keyword = get_keyword(input_ptr);
    char *redirs[5] = {"<<", ">>", "<", ">", NULL};
    bool *redir_bool[4] = {&red->d_in, &red->d_out, &red->in, &red->out};
    char **redir_keyword[4] = {&red->keyword_d_in, &red->keyword_d_out,
        &red->keyword_in, &red->keyword_out};
    int index;

    if (only_char_in_str(keyword, ' ')) {
        write(2, "Missing name for redirect.\n", 27);
        return -1;
    }
    index = find_index(redirs, redir);
    if (ambiguous_redirect(index, redir_bool)) {
        return -1;
    }
    *redir_bool[index] = true;
    *redir_keyword[index] = keyword;
    return 0;
}
