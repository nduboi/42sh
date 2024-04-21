/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** input_errors
*/

#include "mysh.h"

static char *skip_redirs(char *cmd)
{
    char *str = my_malloc(sizeof(char) * (my_strlen(cmd) + 1));

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] != '<' && cmd[i] != '>') {
            str[my_strlen(str)] = cmd[i];
            continue;
        }
        i += 1;
        for (;
            cmd[i] == ' ' || cmd[i] == '\t' ||
            cmd[i] == '<' || cmd[i] == '>';
            i += 1);
        for (; cmd[i] && cmd[i] != ' ' && cmd[i] != '\t'; i += 1);
    }
    return str;
}

static bool null_cmd(parsing_t *data)
{
    char *str = skip_redirs(data->content.command);
    bool empty_str = only_char_in_str(str, ' ');
    bool empty_cmd = only_char_in_str(data->content.command, ' ');
    static bool link = false;
    bool need_check = false;

    need_check = link;
    link = false;
    if (data->link == PIPE || data->link == OR) {
        need_check = true;
        link = true;
    }
    if (data->link == AND && !empty_str)
        link = true;
    if ((need_check && empty_str) || (empty_str && !empty_cmd)) {
        write(2, "Invalid null command.\n", 22);
        return true;
    }
    return false;
}

static bool got_name(char *cmd, char *str, int *i)
{
    if (cmd[*i] == '<' || cmd[*i] == '>') {
        if (cmd[*i + 1] == cmd[*i]) {
            *i += 1;
        }
        *i += 1;
        for (; cmd[*i] && cmd[*i] != '<' && cmd[*i] != '>'; *i += 1) {
            str[my_strlen(str)] = cmd[*i];
        }
        return false;
    }
    return true;
}

static bool missing_name(char *cmd)
{
    char *str = NULL;
    int i = 0;

    for (; cmd[i]; i++) {
        str = my_malloc(sizeof(char) * (my_strlen(cmd) + 1));
        if (got_name(cmd, str, &i)) {
            free(str);
            continue;
        }
        if (only_char_in_str(str, ' ')) {
            write(2, "Missing name for redirect.\n", 27);
            free(str);
            return true;
        }
        free(str);
        i--;
    }
    return false;
}

static bool ambiguous_redir(parsing_t *data)
{
    static bool was_pipe = false;
    int ins = was_pipe ? 1 : 0;
    int outs = data->link == PIPE ? 1 : 0;
    char *cmd = data->content.command;

    for (int i = 0; cmd[i] && ins <= 1 && outs <= 1; i++) {
        ins = (cmd[i] == '<' && cmd[i + 1] != '<') ? ins + 1 : ins;
        if (ins > 1) {
            write(2, "Ambiguous input redirect.\n", 26);
        }
        outs = (cmd[i] == '>' && cmd[i + 1] != '>') ? outs + 1 : outs;
        if (outs > 1) {
            write(2, "Ambiguous output redirect.\n", 27);
        }
    }
    was_pipe = data->link == PIPE;
    if (ins > 1 || outs > 1)
        return true;
    return false;
}

static bool errors_in_node(parsing_t *data)
{
    if (missing_name(my_strdup(data->content.command)))
        return true;
    if (ambiguous_redir(data))
        return true;
    if (null_cmd(data))
        return true;
    return false;
}

bool errors_in_parsing_list(list_t **list)
{
    list_t *node = *list;
    parsing_t *data = NULL;
    bool errors = false;

    while (node) {
        data = node->data;
        if (data->type == GRP) {
            errors = errors_in_parsing_list(data->content.group);
        } else {
            errors = errors_in_node(data);
        }
        if (errors) {
            return true;
        }
        node = node->next;
    }
    return false;
}
