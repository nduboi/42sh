/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** quotes_errors
*/

#include "mysh.h"

bool quotes_errors(char *input)
{
    if (count_char_in_str(input, '\'', -1) % 2 != 0) {
        write(2, "Unmatched '\''.\n", 15);
        return true;
    }
    if (count_char_in_str(input, '\"', -1) % 2 != 0) {
        write(2, "Unmatched '\"'.\n", 15);
        return true;
    }
    return false;
}
