/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_fd
*/

#include "mysh.h"
#include <unistd.h>

void restart_fds(int in, int out)
{
    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
}
