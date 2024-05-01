/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parsing
*/

#include "mysh.h"

char *remove_in_str(char *str, int ind)
{
    char *new = malloc(sizeof(char) * (strlen(str)));
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (i == ind)
            continue;
        new[j] = str[i];
        new[j + 1] = '\0';
        j++;
    }
    free(str);
    return (new);
}

char *insert_in_str(char *word, char *str, int start)
{
    int len = strlen(word) + strlen(str);
    char *new = malloc(sizeof(char) * (len + 1));
    int ind = 0;

    for (int i = 0; i < start && str[i] != '\0'; i++) {
        new[ind] = str[i];
        ind++;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        new[ind] = word[i];
        ind++;
    }
    for (int i = start; str[i] != '\0'; i++) {
        new[ind] = str[i];
        ind++;
    }
    new[len] = '\0';
    free(str);
    return (new);
}

char *arr_to_str(char **args)
{
    char *new = NULL;
    int len = 0;
    int ind = 0;

    for (int i = 0; args[i] != NULL; i++) {
        len += strlen(args[i]) + 1;
    }
    new = malloc(sizeof(char) * (len + 1));
    for (int i = 0; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            new[ind] = args[i][j];
            ind++;
        }
        new[ind] = ' ';
        ind++;
    }
    new[len] = '\0';
    return (new);
}

char *insert_spaces(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            str = insert_in_str(" ", str, i + 1);
            str = insert_in_str(" ", str, i);
            i++;
        }
    }
    return (str);
}
