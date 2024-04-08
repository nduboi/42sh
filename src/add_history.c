/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** add_history
*/

#include "mysh.h"

char *get_hour(char *date)
{
    char *ret = malloc(sizeof(char) * 6);
    int len = strlen(date);

    ret[5] = '\0';
    ret[4] = date[len - 7];
    ret[3] = date[len - 8];
    ret[2] = date[len - 9];
    ret[1] = date[len - 10];
    ret[0] = date[len - 11];
    return (ret);
}

void add_history(infos_t *info, char *line)
{
    history_t *new = malloc(sizeof(history_t) * 1);
    static int id = 0;
    time_t tm = time(NULL);
    char *date = ctime(&tm);

    if (info->history != NULL) {
        if (strcmp(line, info->history->line) == 0)
            return;
    }
    new->id = id;
    id++;
    new->hour = get_hour(date);
    new->line = strdup(line);
    new->next = info->history;
    info->history = new;
}
