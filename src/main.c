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

FILE *get_input_file(char *name)
{
    FILE *file = stdin;
    char *buffer = NULL;
    size_t size = 0;

    if (name) {
        file = fopen(name, "r");
        getline(&buffer, &size, file);
    }
    return file;
}

int main(int argc, char **argv, char **env)
{
    FILE *file = get_input_file(argv[1]);

    if (my_sh(env, file) == -1) {
        return 84;
    }
    return 0;
}
