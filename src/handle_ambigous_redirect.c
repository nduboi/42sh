/*
** EPITECH PROJECT, 2024
** handle_ambigous_redirect
** File description:
** handle_ambigous_redirect
*/

#include "mysh.h"
#include <unistd.h>

int count_nbr_pipe(char *src)
{
    int nbr = 0;

    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == '|')
            nbr++;
    }
    return nbr;
}

static int get_last_pipe_location(char *src)
{
    int place = 0;

    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == '|')
            place = i;
    }
    return place;
}

static int get_first_pipe_location(char *src)
{
    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == '|')
            return i;
    }
    return 0;
}

static int get_first_character(char *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++) {
        if (src[i] != ' ')
            return i;
    }
    return i;
}

static int get_last_character(char *src)
{
    int i = my_strlen(src) - 1;

    for (; i != -1; i--) {
        if (src[i] != ' ')
            return i;
    }
    return i;
}

bool ambigous_redirect(char *src)
{
    int nbr_pipe = count_nbr_pipe(src);

    if (nbr_pipe == 0)
        return false;
    for (int i = 0; src[i] != '\0'; i++) {
        if (i != get_first_character(src) && src[i] == '>' &&
            get_first_pipe_location(src) > i) {
            write(2, "Ambiguous output redirect.\n", 27);
            return true;
        }
        if (i != get_last_character(src) && src[i] == '<' &&
            get_last_pipe_location(src) < i) {
            write(2, "Ambiguous input redirect.\n", 26);
            return true;
        }
    }
    return false;
}
