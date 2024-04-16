/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** exclamation_mark
*/

#include "mysh.h"

static char *insert_in_str(char *word, char *str, int start)
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

static char *remove_in_str(char *str, int ind)
{
    char *new = malloc(sizeof(char) * (strlen(str) - 1));
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

char *recall_last_command(char *str, int i, infos_t *info)
{
    char *line = (info->history == NULL ? NULL : strdup(info->history->line));
    char *new = strdup(str);

    if (line == NULL) {
        write(2, "Event not found.\n", 18);
        return (NULL);
    }
    new = insert_in_str(line, new, i + 2);
    new = remove_in_str(new, i);
    new = remove_in_str(new, i);
    free(str);
    free(line);
    printf("%s\n", new);
    return (new);
}

char *check_exclamation(char *input, infos_t *info)
{
    char *cpy = strdup(input);

    free(input);
    for (int i = 0; cpy[i] != '\0'; i++) {
        if (cpy[i] == '!' && cpy[i + 1] == '!')
            cpy = recall_last_command(cpy, i, info);
        if (cpy == NULL)
            return (NULL);
    }
    return (cpy);
}
