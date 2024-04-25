/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parse_input
*/

#include "mysh.h"

static parsing_t *init_parsing_node(void)
{
    parsing_t *new = malloc(sizeof(parsing_t));

    new->type = CMD;
    new->content.cmd = my_malloc(sizeof(char) * 2);
    new->content.cmd[0] = ' ';
    new->link = NONE_LINK;
    new->bt = NULL;
    new->redirs.in = false;
    new->redirs.out = false;
    new->redirs.d_in = false;
    new->redirs.d_out = false;
    new->redirs.keyword_in = NULL;
    new->redirs.keyword_out = NULL;
    new->redirs.keyword_d_in = NULL;
    new->redirs.keyword_d_out = NULL;
    return new;
}

static bool is_redir(char *str)
{
    char *redirs[5] = {"<<", ">>", "<", ">", NULL};

    for (int i = 0; redirs[i]; i++) {
        if (!strncmp(str, redirs[i], strlen(redirs[i]))) {
            return true;
        }
    }
    return false;
}

static bool null_cmd(parsing_t *data)
{
    bool empty_str = only_char_in_str(data->content.cmd, ' ');
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
    if (need_check && empty_str && !data->bt) {
        write(2, "Invalid null command.\n", 22);
        return true;
    }
    return false;
}

static bool ambiguous_redir(parsing_t *data)
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

static int handle_delims(char **input_ptr, parsing_t *data)
{
    char *delims[6] = {NULL, ";", "&&", "||", "|", NULL};
    char *input = *input_ptr;

    if (!*input)
        data->link = END;
    for (enum link_e link = SC; *input && delims[link]; link++) {
        if (!strncmp(input, delims[link], strlen(delims[link]))) {
            data->link = link;
            *input_ptr += strlen(delims[link]);
            break;
        }
    }
    if (ambiguous_redir(data) || null_cmd(data))
        return -1;
    return 0;
}

static void add_char_to_cmd(char **input_ptr, parsing_t *parsing)
{
    char *input = *input_ptr;
    char *cmd = parsing->content.cmd;
    int len = strlen(cmd);

    cmd = realloc(cmd, sizeof(char) * (len + 2));
    cmd[len] = *input;
    cmd[len + 1] = '\0';
    parsing->content.cmd = cmd;
    *input_ptr += 1;
}

static int handle_specificities
(char **input_ptr, parsing_t *data, infos_t *infos)
{
    if (**input_ptr == '`') {
        return add_backtick(input_ptr, data, infos);
    }
    if (is_redir(*input_ptr)) {
        return add_redir(input_ptr, &data->redirs);
    }
    add_char_to_cmd(input_ptr, data);
    return 0;
}

static int try_add_node(char **input, parsing_t **data, list_t **list_parse)
{
    if ((!**input || is_delim(*input))) {
        if (handle_delims(input, *data) == -1) {
            return -1;
        }
        add_node(list_parse, *data);
        *data = init_parsing_node();
    }
    return 0;
}

int parse_input(char *input, list_t **list_parse, infos_t *infos)
{
    parsing_t *data = init_parsing_node();
    char *temp = input;
    bool end = false;

    while (!end) {
        if (!*input)
            end = true;
        if (try_add_node(&input, &data, list_parse) == -1)
            return -1;
        if (handle_specificities(&input, data, infos) == -1)
            return -1;
    }
    return input - temp;
}
