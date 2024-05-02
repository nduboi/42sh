/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_input
*/

#include "../include/mysh.h"
#include <unistd.h>
#include <string.h>

function_t functions[] = {
    {"exit", my_exit},
    {"cd", my_cd},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"env", my_env},
    {"echo", my_echo},
    {"history", my_history},
    {"alias", my_alias},
    {"unalias", my_unalias},
    {"jobs", my_jobs},
    {"fg", my_fg},
    {"bg", my_bg},
    {"glob", my_globbing},
    {"unset", my_unset},
    {"set", my_set},
    {NULL, exe_cmd}
};

static int replace_args(char **input, infos_t *infos)
{
    *input = parse_input_local_var(*input, infos);
    if (!*input || parse_input_env_var(input, infos) == 1 ||
        handle_globbings(input) == 1) {
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    return 0;
}

int handle_cmd(char *input, infos_t *infos)
{
    char **args = NULL;
    int index = 0;

    if (replace_args(&input, infos) == -1)
        return -1;
    args = str_to_word_array(input);
    if (!args[0])
        return 0;
    args = check_if_is_an_alias(args, infos);
    for (; index < SIZE_TAB && my_strcmp(args[0],
    functions[index].name); index++);
    functions[index].function(args, infos);
    free(args);
    if (index < SIZE_TAB && handle_exit_status(GET_STATUS, 0) != 0)
        return -1;
    return 0;
}
