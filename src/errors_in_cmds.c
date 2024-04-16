/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** errors_in_cmds
*/

#include "mysh.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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
            continue;
        }
        if (!strtok(str, " ")) {
            write(2, "Missing name for redirect.\n", 27);
            handle_exit_status(WRITE_STATUS, 1);
            return true;
        }
        free(str);
        i--;
    }
    return false;
}

static bool too_many_redirs(char *cmd)
{
    int ins = 0;
    int outs = 0;

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
    if (ins > 1 || outs > 1) {
        handle_exit_status(WRITE_STATUS, 1);
        return true;
    }
    return false;
}

static void skip_redirs(char *str, int *i)
{
    if (str[*i] == '<' || str[*i] == '>') {
        if (str[*i + 1] == str[*i]) {
            *i += 1;
        }
        *i += 1;
        for (; str[*i] && str[*i] != '<' && str[*i] != '>'; *i += 1);
    }
}

static void null_cmd_message(void)
{
    write(2, "Invalid null command.\n", 22);
    handle_exit_status(WRITE_STATUS, 1);
}

static bool no_cmd(char *cmd, int count)
{
    char *str = my_malloc(sizeof(char) * (my_strlen(cmd) + 1));
    int i = 0;
    char *token = NULL;

    for (; cmd[i]; i++) {
        skip_redirs(cmd, &i);
        str[my_strlen(str)] = cmd[i];
    }
    token = strtok_r(str, " ", &str);
    if ((!token || !*token) && (count)) {
        null_cmd_message();
        return true;
    }
    return false;
}

static bool file_doesnt_exist(char *cmd)
{
    char *token = NULL;
    char *copy = my_strdup(cmd);
    char *pos = NULL;

    for (int i = 0; copy[i]; i++) {
        if (copy[i] == '<' && copy[i + 1] == '<') {
            return false;
        }
        if (copy[i] == '<') {
            pos = copy + i;
            token = strtok_r(pos, " \n<>", &pos);
            break;
        }
    }
    if (token && access(token, F_OK) != 0) {
        error_message(token, errno);
        handle_exit_status(WRITE_STATUS, 1);
        return true;
    }
    return false;
}

static bool not_good_cmd(char *temp, int count)
{
    if (missing_name(temp)) {
        return true;
    }
    if (too_many_redirs(temp)) {
        return true;
    }
    if (no_cmd(temp, count)) {
        return true;
    }
    if (file_doesnt_exist(temp)) {
        return true;
    }
    return false;
}

static bool handle_error_cmd(char *cmd, int len, int count)
{
    char *temp = NULL;
    int j = 0;

    for (int i = 0; i < len; i++) {
        temp = my_malloc(sizeof(char) * (my_strlen(cmd) + 1));
        for (; cmd[j] && cmd[j] != '|'; j++) {
            temp[my_strlen(temp)] = cmd[j];
        }
        j++;
        if (not_good_cmd(temp, count)) {
            handle_exit_status(WRITE_STATUS, 1);
            return true;
        }
        free(temp);
    }
    return false;
}

bool errors_in_pipes_and_redirs(char *cmd)
{
    int len = count_tokens(cmd, "|");
    int count = count_char_in_str(cmd, '|');

    if (ambigous_redirect(cmd)) {
        handle_exit_status(WRITE_STATUS, 1);
        return true;
    }
    if (handle_error_cmd(cmd, len, count)) {
        handle_exit_status(WRITE_STATUS, 1);
        return true;
    }
    if (len != count + 1) {
        handle_exit_status(WRITE_STATUS, 1);
        null_cmd_message();
        return true;
    }
    return false;
}
