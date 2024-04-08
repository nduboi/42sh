/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** exit_status
*/

#include "mysh.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int handle_exit_status(int action, int nbr)
{
    static int exit_status = 0;

    if (action == WRITE_STATUS) {
        exit_status = nbr;
        return 0;
    }
    if (action == GET_STATUS) {
        return exit_status;
    }
    return 0;
}

void handle_signal(int wstatus)
{
    if (WIFSIGNALED(wstatus)) {
        my_strsignal(wstatus);
        handle_exit_status(WRITE_STATUS, 128 + WTERMSIG(wstatus));
    }
    if (WIFEXITED(wstatus)) {
        handle_exit_status(WRITE_STATUS, WEXITSTATUS(wstatus));
    }
}
