/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** ands_ors_errors
*/

#include "mysh.h"

static void remove_trailing_spaces(char *str)
{
    while (str[my_strlen(str) - 1] == ' ') {
        str[my_strlen(str) - 1] = '\0';
    }
}

static bool errors_in_ands(char *cmd)
{
    char *cmd2 = NULL;
    char *temp_cmd = NULL;

    if (!my_strstr(cmd, "&&")) {
        return errors_in_pipes_and_redirs(cmd);
    }
    cmd2 = my_strstr(cmd, "&&") + 2;
    cmd[cmd2 - cmd - 2] = ' ';
    cmd[cmd2 - cmd - 1] = '\0';
    remove_trailing_spaces(cmd2);
    if (cmd2[0] == '\0' && only_char_in_str(cmd, ' ')) {
        temp_cmd = my_malloc(sizeof(char) * 2);
        temp_cmd[0] = ' ';
        cmd2 = temp_cmd;
    }
    return errors_in_pipes_and_redirs(cmd) || errors_in_ands(cmd2);
}

static bool errors_in_ors(char *cmd)
{
    char *cmd2 = NULL;

    if (!my_strstr(cmd, "||")) {
        return errors_in_ands(cmd);
    }
    cmd2 = my_strstr(cmd, "||") + 2;
    cmd[cmd2 - cmd - 2] = ' ';
    cmd[cmd2 - cmd - 1] = '\0';
    remove_trailing_spaces(cmd);
    remove_trailing_spaces(cmd2);
    return errors_in_ands(cmd) || errors_in_ors(cmd2);
}

static bool errors_in_parenthesis(char *cmd)
{
    int count_open = 0;
    int count_close = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '(') {
            count_open += 1;
        }
        if (cmd[i] == ')') {
            count_close += 1;
        }
        if (count_close > count_open) {
            write(2, "Too many )'s\n", 13);
            return true;
        }
    }
    if (count_open > count_close) {
        write(2, "Too many ('s\n", 13);
        return true;
    }
    return false;
}

static bool parse_semi_colons(char *cmd)
{
    char *cmd2 = NULL;
    char *temp_cmd = NULL;

    if (!my_strstr(cmd, ";")) {
        if (!*cmd) {
            temp_cmd = my_malloc(sizeof(char) * 2);
            temp_cmd[0] = ' ';
            cmd = temp_cmd;
        }
        return errors_in_ors(cmd);
    }
    cmd2 = my_strstr(cmd, ";") + 1;
    cmd[cmd2 - cmd - 1] = '\0';
    return parse_semi_colons(cmd) || parse_semi_colons(cmd2);
}

bool errors_in_input(char *cmd)
{
    bool error_status = false;

    if (errors_in_parenthesis(cmd)) {
        handle_exit_status(WRITE_STATUS, 1);
        return true;
    }
    error_status = parse_semi_colons(cmd);
    if (error_status) {
        handle_exit_status(WRITE_STATUS, 1);
    }
    return error_status;
}
