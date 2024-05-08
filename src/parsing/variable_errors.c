/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** variable_errors
*/

#include "mysh.h"

bool end_of_var(char *src)
{
    return (*src == ' ' ||
            is_delim(src) ||
            *src == '(' ||
            *src == ')' ||
            *src == '\'' ||
            *src == '\"' ||
            !*src);
}

static bool check_with_brackets(char *src)
{
    if (*src == ' ' || *src == '}') {
        write(2, "Illegal variable name.\n", 23);
        return true;
    }
    if (!*src) {
        write(2, "Newline in variable name.\n", 26);
        return true;
    }
    for (; *src != '}'; src++) {
        if (end_of_var(src)) {
            write(2, "Missing '}'.\n", 13);
            return true;
        }
        if (!((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') ||
            (*src >= '0' && *src <= '9') || *src == '_' || *src == '?')) {
            write(2, "Illegal variable name.\n", 23);
            return true;
        }
    }
    return false;
}

static bool is_error(char *src)
{
    if (*src == '{')
        return check_with_brackets(src + 1);
    for (int i = 0; !end_of_var(src + i); i++) {
        if (!((src[i] >= 'a' && src[i] <= 'z') ||
            (src[i] >= 'A' && src[i] <= 'Z') ||
            (src[i] >= '0' && src[i] <= '9') ||
            src[i] == '_' || src[i] == '?')) {
            write(2, "Illegal variable name.\n", 23);
            return true;
        }
    }
    return false;
}

bool error_in_variables(char *input)
{
    for (; *input; input++) {
        if (*input == '$' && is_error(input + 1)) {
            return true;
        }
    }
    return false;
}
