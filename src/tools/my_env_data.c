/*
** EPITECH PROJECT, 2024
** env data
** File description:
** my_env_data
*/

#include "mysh.h"

int count_len_name_env(char *data)
{
    int i = 0;
    int nbr = 0;

    for (; data[i] != '\0'; i++) {
        nbr++;
        if (data[i] == '}')
            break;
    }
    return nbr;
}

char *get_value_env_with_brakets(char *data)
{
    char *result = my_malloc(sizeof(char) * (count_len_name_env(data) + 1));
    int status = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '}')
            status = 1;
        if (status == 0) {
            result[i] = data[i];
        }
    }
    return result;
}

char *get_value_env(char *data)
{
    char *result = my_malloc(sizeof(char) * (count_len_name_env(data) + 1));
    int status = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        if (!((data[i] >= 'a' && data[i] <= 'z') ||
            (data[i] >= 'A' && data[i] <= 'Z') ||
            (data[i] >= '0' && data[i] <= '9') ||
            data[i] == '_' || data[i] == '?'))
            status = 1;
        if (status == 0)
            result[i] = data[i];
    }
    return result;
}

int count_len_before_env(char *src)
{
    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == '$')
            return i;
    }
    return 0;
}

int count_len_after_env(int k, char *data)
{
    int nbr = k + 1;

    for (int i = k + 1; data[k] != '\0'; i++) {
        if (!((data[i] >= 'a' && data[i] <= 'z') ||
            (data[i] >= 'A' && data[i] <= 'Z') ||
            (data[i] >= '0' && data[i] <= '9') ||
            data[i] == '_' || data[i] == '?' || data[i] == '{'))
            return nbr;
        nbr++;
    }
    return nbr;
}
