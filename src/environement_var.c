/*
** EPITECH PROJECT, 2024
** replce env var
** File description:
** environement_var
*/

#include "mysh.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string.h>

static int print_error_variable(char **value_env, char *value, infos_t *info)
{
    if (!*value_env) {
        *value_env = get_local_val(value, info);
        if (!*value_env) {
            write(2, value, my_strlen(value));
            write(2, ": Undefined variable.\n", 22);
            return 1;
        }
    }
    return 0;
}

static int handle_brackets_env(char **data, int y, infos_t *info)
{
    char *value = NULL;
    char *value_env = NULL;
    char *part1 = my_malloc(sizeof(char));
    char *part2 = my_malloc(sizeof(char));

    value = get_value_env_with_brakets(&(*data)[y + 2]);
    value = special_var(value);
    value_env = append_env_value(value, info);
    if (print_error_variable(&value_env, value, info) == 1)
        return 1;
    cut_in_part_brakets(*data, &part1, &part2);
    *data = my_strcat_s(part1, value_env);
    *data = my_strcat_s(*data, part2);
    return 0;
}

static int handle_without_brackets_env(char **data, int y,
    infos_t *info)
{
    char *value = NULL;
    char *value_env = NULL;
    char *part1 = my_malloc(sizeof(char));
    char *part2 = my_malloc(sizeof(char));

    value = get_value_env(&(*data)[y + 1]);
    value = special_var(value);
    value_env = append_env_value(value, info);
    if (print_error_variable(&value_env, value, info) == 1)
        return 1;
    cut_in_part(*data, &part1, &part2);
    *data = my_strcat_s(part1, value_env);
    *data = my_strcat_s(*data, part2);
    return 0;
}

static int replace_input_env_var(char **data, int y, infos_t *info)
{
    if ((*data)[y] == '$' && my_strlen(&(*data)[y]) > 1 &&
        (*data)[y + 1] != ' ' && count_char_in_str(*data, '\'', y) % 2 == 0) {
        if ((*data)[y + 1] == '{') {
            return handle_brackets_env(data, y, info);
        } else {
            return handle_without_brackets_env(data, y, info);
        }
    }
    return 0;
}

static int parse_string_research_env(char **data, infos_t *info)
{
    for (int y = 0; (*data)[y] != '\0'; y++) {
        if (replace_input_env_var(data, y, info) == 1)
            return 1;
    }
    return 0;
}

int parse_input_env_var(char **data, infos_t *info)
{
    if (parse_string_research_env(data, info) == 1) {
        handle_exit_status(WRITE_STATUS, 1);
        return 1;
    }
    return 0;
}
