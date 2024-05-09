/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** last_arg_is_bg
*/

#include "mysh.h"

int last_arg_is_bg(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (!my_strcmp(args[i], "&"))
            return (1);
    }
    return (0);
}
