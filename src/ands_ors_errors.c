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

bool errors_in_ands(char *cmd)
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

bool errors_in_ors(char *cmd)
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

bool errors_in_input(char *cmd)
{
    bool status = errors_in_ors(cmd);

    free(cmd);
    if (status) {
        handle_exit_status(WRITE_STATUS, 1);
    }
    return status;
}
