/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_echo
*/

#include "mysh.h"
#include <unistd.h>

void display_args(char **args)
{
    for (int index = 1; args[index]; index++) {
        write(1, args[index], my_strlen(args[index]));
        if (args[index + 1]) {
            write(1, " ", 1);
        }
    }
    write(1, "\n", 1);
}

int my_echo(char **args, infos_t *infos)
{
    (void) infos;
    if (!args[1]) {
        write(1, "\n", 1);
        handle_exit_status(WRITE_STATUS, 0);
        return 0;
    }
    display_args(args);
    handle_exit_status(WRITE_STATUS, 0);
    return 0;
}
