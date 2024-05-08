/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** exclamation_mark
*/

#include "mysh.h"

static char *last_com(char *key, infos_t *info)
{
    history_t *tmp = info->history;
    int size = strlen(key) - 1;

    while (tmp != NULL) {
        if (strncmp(key, tmp->line, size) == 0)
            return (strdup(tmp->line));
        tmp = tmp->next;
    }
    return (NULL);
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
    write(1, line, strlen(line));
    free(line);
    return (new);
}

char *get_key(char *str, int i)
{
    char *key = NULL;
    int len = 0;
    int j = i;

    for (j = i; !end_of_var(str + j); j++);
    len = j - i;
    if (len == 0)
        return (NULL);
    key = malloc(sizeof(char) * (len + 1));
    key[len] = '\0';
    for (int a = 0; a < len; a++) {
        key[a] = str[i + a];
    }
    return (key);
}

char *recall_start_with(char *str, int i, infos_t *info)
{
    char *key = get_key(str, i + 1);
    char *line = NULL;
    int len = 0;

    if (key == NULL)
        return (str);
    line = last_com(key, info);
    if (line == NULL) {
        dprintf(2, "%s: Event not found.\n", key);
        return (NULL);
    }
    len = strlen(key);
    str = insert_in_str(line, str, i + len + 1);
    for (int j = 0; j < len + 1; j++) {
        str = remove_in_str(str, i);
    }
    write(1, line, strlen(line));
    free(line);
    free(key);
    return (str);
}

char *check_exclamation(char *input, infos_t *info)
{
    char *cpy = strdup(input);

    for (int i = 0; cpy[i] != '\0'; i++) {
        if (cpy[i] == '!' && cpy[i + 1] == '!')
            cpy = recall_last_command(cpy, i, info);
        if (!cpy)
            break;
        if (cpy[i] == '!' && cpy[i + 1] != '!')
            cpy = recall_start_with(cpy, i, info);
        if (!cpy)
            break;
    }
    if (!cpy) {
        handle_exit_status(WRITE_STATUS, 1);
        return NULL;
    }
    if (strcmp(input, cpy) != 0)
        write(1, "\n", 1);
    free(input);
    return (cpy);
}
