/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_input
*/

#include "mysh.h"
#include <unistd.h>
#include <string.h>

void handle_cmd(char *input, infos_t *infos)
{
    char **args = NULL;
    char *commands[11] = {"exit", "cd", "setenv", "unsetenv", "env", "echo",
        "history", "alias", "unalias", "jobs", "fg"};
    int (*fcts_ptrs[12])(char **, infos_t *) = {my_exit, my_cd, my_setenv,
        my_unsetenv, my_env, my_echo, my_history, my_alias, my_unalias,
        my_jobs, my_fg, exe_cmd};
    int index = 0;

    args = str_to_word_array(input);
    if (!args[0])
        return;
    args = check_if_is_an_alias(args, infos);
    for (; index < 11 && my_strcmp(args[0], commands[index]); index++);
    fcts_ptrs[index](args, infos);
    free(args);
    if (index < 11 && handle_exit_status(GET_STATUS, 0) != 0
        && !infos->isatty)
        exit(handle_exit_status(GET_STATUS, 0));
}
