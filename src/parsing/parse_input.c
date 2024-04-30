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

    new->type = NONE_TYPE;
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

static int handle_delims(char **input_ptr, parsing_t *data)
{
    char *delims[6] = {NULL, ";", "&&", "||", "|", NULL};
    char *input = *input_ptr;

    if (!*input || *input == ')')
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

static int add_char_to_cmd(char **input_ptr, parsing_t *data)
{
    char *cmd = NULL;

    if (data->type == GRP) {
        if (**input_ptr == ' ') {
            return 0;
        }
        write(2, "Badly placed ()'s.\n", 19);
        return -1;
    }
    if (data->type == NONE_TYPE) {
        data->type = CMD;
        data->content.cmd = my_malloc(CHAR * 2);
        data->content.cmd[0] = ' ';
    }
    cmd = data->content.cmd;
    cmd = my_realloc(cmd, sizeof(char) * (strlen(cmd) + 2));
    cmd[strlen(cmd)] = **input_ptr;
    data->content.cmd = cmd;
    return 0;
}

static int add_group(char **input_ptr, parsing_t *data, infos_t *infos)
{
    char *input = *input_ptr;
    int offset = 0;

    if (data->type == CMD) {
        if (only_char_in_str(data->content.cmd, ' ')) {
            free(data->content.cmd);
        } else {
            write(2, "Badly placed ()'s.\n", 19);
            return -1;
        }
    }
    data->type = GRP;
    data->content.grp = malloc(sizeof(list_t *));
    *(data->content.grp) = NULL;
    offset = parse_input(input + 1, data->content.grp, infos);
    if (offset == -1)
        return -1;
    *input_ptr += offset + 2;
    return 0;
}

static int handle_specificities
(char **input_ptr, parsing_t *data, infos_t *infos)
{
    if (!**input_ptr)
        return 0;
    if (**input_ptr == '`') {
        return add_backtick(input_ptr, data, infos);
    }
    if (is_redir(*input_ptr)) {
        return add_redir(input_ptr, &data->redirs);
    }
    if (**input_ptr == '(') {
        return add_group(input_ptr, data, infos);
    }
    if (add_char_to_cmd(input_ptr, data) == -1)
        return -1;
    else {
        *input_ptr += 1;
        return 0;
    }
}

static int try_add_node
(char **input_ptr, parsing_t **data, list_t **list_parse)
{
    if ((!**input_ptr || **input_ptr == ')' || is_delim(*input_ptr))) {
        if ((*data)->type == NONE_TYPE) {
            (*data)->type = CMD;
            (*data)->content.cmd = my_malloc(CHAR * 2);
            (*data)->content.cmd[0] = ' ';
        }
        if (handle_delims(input_ptr, *data) == -1) {
            return -1;
        }
        add_node(list_parse, *data);
        *data = init_parsing_node();
        return 1;
    }
    return 0;
}

int parse_input(char *input, list_t **list_parse, infos_t *infos)
{
    parsing_t *data = init_parsing_node();
    char *temp = input;
    bool end = false;
    int status = 0;

    while (!end) {
        if (!*input || *input == ')')
            end = true;
        status = try_add_node(&input, &data, list_parse);
        if (status == -1)
            return -1;
        if (status == 1)
            continue;
        if (handle_specificities(&input, data, infos) == -1)
            return -1;
    }
    return input - temp;
}
