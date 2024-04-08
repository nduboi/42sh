/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_exit
*/

#include "mysh.h"
#include <unistd.h>
#include <sys/wait.h>

int good_number(char *nbr)
{
    int i = 1;

    while (nbr[i]) {
        if ((nbr[i] < '0' || '9' < nbr[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

void exit_number(char **args)
{
    int nbr = 0;

    if (!good_number(args[1])) {
        write(2, "exit: Badly formed number.\n", 27);
        handle_exit_status(WRITE_STATUS, 1);
        return;
    }
    nbr = my_getnbr(args[1]);
    free(args);
    exit(nbr);
}

int my_exit(char **args, infos_t *infos)
{
    if (args[1] && (args[2]
        || ((args[1][0] < '0' || '9' < args[1][0]) && args[1][0] != '-'))) {
        write(2, "exit: Expression Syntax.\n", 25);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    free_infos(infos);
    if (args[1] == NULL) {
        exit(handle_exit_status(GET_STATUS, 0));
        return 0;
    }
    exit_number(args);
    return 0;
}
