/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** main
*/

#include "mysh.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **env)
{
    (void) argv;
    if (argc != 1) {
        return 84;
    }
    if (my_sh(env) == -1) {
        return 84;
    }
    return 0;
}
