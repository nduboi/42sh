/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parsing_errors
*/

#include "mysh.h"

static bool empty_list(list_t **ptr)
{
    list_t *node = *ptr;
    parsing_t *data = NULL;

    while (node) {
        data = node->data;
        if (data->type == CMD && !only_char_in_str(data->content.cmd, ' '))
            return false;
        if (data->type == GRP && !empty_list(data->content.grp))
            return false;
        node = node->next;
    }
    return true;
}

bool null_cmd(parsing_t *data)
{
    bool empty_str = data->type == GRP ? empty_list(data->content.grp) :
        only_char_in_str(data->content.cmd, ' ');
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
    if (data->type == GRP)
        need_check = true;
    if (need_check && empty_str && !data->bt) {
        write(2, "Invalid null command.\n", 22);
        return true;
    }
    return false;
}

bool ambiguous_redir(parsing_t *data)
{
    static bool was_pipe = false;

    if (was_pipe && (data->redirs.in || data->redirs.d_in)) {
        write(2, "Ambiguous input redirect.\n", 26);
        return true;
    }
    if (data->link == PIPE && (data->redirs.out || data->redirs.d_out)) {
        write(2, "Ambiguous output redirect.\n", 27);
        return true;
    }
    was_pipe = data->link == PIPE;
    return false;
}
