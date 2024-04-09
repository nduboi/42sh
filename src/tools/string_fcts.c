/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** string_fcts
*/

#include "mysh.h"
#include <string.h>

int my_arrlen(char **arr)
{
    int count = 0;

    while (*arr) {
        arr++;
        count++;
    }
    return count;
}

int my_strlen(char *str)
{
    int count = 0;

    if (str == NULL)
        return (0);
    while (*str) {
        str++;
        count++;
    }
    return count;
}

int count_tokens(char *str, char *sep)
{
    int result = 0;
    char *copy = my_strdup(str);
    char *token = strtok_r(copy, sep, &copy);

    while (token) {
        result++;
        token = strtok_r(copy, sep, &copy);
    }
    return result;
}

char **str_to_word_array(char *buffer)
{
    int count = count_tokens(buffer, " \t");
    char **result = malloc(sizeof(char *) * (count + 1));

    for (int i = 0; i < count; i++) {
        result[i] = strtok_r(buffer, " \t", &buffer);
    }
    result[count] = NULL;
    return result;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == 0 || s2[i] == 0) {
            break;
        }
        i++;
    }
    return (s1[i] - s2[i]);
}
