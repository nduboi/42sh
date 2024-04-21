/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** parse_input
*/

#include "mysh.h"

static bool in_delims(char *str, int offset)
{
    char *delims[5] = {";", "||", "|", "&&", NULL};

    for (int i = 0; delims[i]; i++) {
        if (!strncmp(str + offset, delims[i], my_strlen(delims[i]))) {
            return true;
        }
    }
    return false;
}

static parsing_t *create_node
(enum type_e type, union content_u content, enum link_e link)
{
    parsing_t *parsing = malloc(sizeof(parsing_t));

    parsing->type = type;
    parsing->content = content;
    parsing->link = link;
    return parsing;
}

static parsing_t *handle_and
(parsing_t *grp_parse, int *i, char *input, int *off)
{
    parsing_t *parsing = grp_parse;
    union content_u content;

    if (parsing == NULL) {
        input[*i] = '\0';
        input[*i + 1] = '\0';
        content.command = my_strdup(input + *off);
        parsing = create_node(CMD, content, AND);
    } else {
        parsing->link = AND;
    }
    *i += 1;
    *off = *i + 1;
    return parsing;
}

static parsing_t *handle_or
(parsing_t *grp_parse, int *i, char *input, int *off)
{
    parsing_t *parsing = grp_parse;
    union content_u content;

    if (parsing == NULL) {
        input[*i] = '\0';
        input[*i + 1] = '\0';
        content.command = my_strdup(input + *off);
        parsing = create_node(CMD, content, OR);
    } else {
        parsing->link = OR;
    }
    *i += 1;
    *off = *i + 1;
    return parsing;
}

static parsing_t *handle_sc
(parsing_t *grp_parse, int *i, char *input, int *off)
{
    parsing_t *parsing = grp_parse;
    union content_u content;

    if (parsing == NULL) {
        input[*i] = '\0';
        content.command = my_strdup(input + *off);
        parsing = create_node(CMD, content, SC);
    } else {
        parsing->link = SC;
    }
    *off = *i + 1;
    return parsing;
}

static parsing_t *handle_pipe
(parsing_t *grp_parse, int *i, char *input, int *off)
{
    parsing_t *parsing = grp_parse;
    union content_u content;

    if (parsing == NULL) {
        input[*i] = '\0';
        content.command = my_strdup(input + *off);
        parsing = create_node(CMD, content, PIPE);
    } else {
        parsing->link = PIPE;
    }
    *off = *i + 1;
    return parsing;
}

static parsing_t *handle_group(int *i, char *input, int *offset)
{
    parsing_t *parsing = NULL;
    union content_u content;
    list_t **list = malloc(sizeof(list_t *));
    int group_offset = 0;

    *list = NULL;
    group_offset = parse_input(input + *i + 1, list);
    content.group = list;
    parsing = create_node(GRP, content, 0);
    *i += group_offset;
    *offset = *i;
    return parsing;
}

static parsing_t *handle_end(char *input, int *i, int off)
{
    union content_u content;

    if (input[*i] == ')') {
        input[*i] = '\0';
        *i += 1;
    }
    content.command = my_strdup(input + off);
    return create_node(CMD, content, END);
}

static parsing_t *handle_delims_and_groups
(int *i, char *input, int *offset, parsing_t *parsing)
{
    if (input[*i] == '&' && input[*i + 1] == '&')
        return handle_and(parsing, i, input, offset);
    if (input[*i] == '|' && input[*i + 1] == '|')
        return handle_or(parsing, i, input, offset);
    if (input[*i] == ';')
        return handle_sc(parsing, i, input, offset);
    if (input[*i] == '|' && input[*i + 1] != '|')
        return handle_pipe(parsing, i, input, offset);
    if (input[*i] == '(')
        return handle_group(i, input, offset);
    if ((!input[*i] || input[*i] == ')') && !parsing)
        return handle_end(input, i, *offset);
    return NULL;
}

int parse_input(char *input, list_t **list_parse)
{
    parsing_t *parsing = NULL;
    int offset = 0;
    int i = 0;
    bool ended = false;
    bool is_in_delims = false;

    while (!ended) {
        if (input[i] == '\0' || input[i] == ')')
            ended = true;
        is_in_delims = in_delims(input, i);
        parsing = handle_delims_and_groups(&i, input, &offset, parsing);
        if (parsing)
            add_node(list_parse, parsing);
        if (is_in_delims)
            parsing = NULL;
        i++;
    }
    return i;
}
