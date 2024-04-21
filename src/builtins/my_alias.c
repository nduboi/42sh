/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** my_alias
*/

#include "mysh.h"

int my_alias(char **args, infos_t *infos)
{
    if (my_arrlen(args) == 1)
        display_all_alias(infos);
    else if (my_arrlen(args) == 2) {
        display_alias(args, infos);
    } else {
        return add_alias(args, infos);
    }
    return (0);
}
