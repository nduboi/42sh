/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_history
*/

#include "mysh.h"

static int my_perror(char *line, int ret)
{
    write(2, line, strlen(line));
    return (ret);
}

int print_history(history_t *tmp, bool data, int times)
{
    char **arr = NULL;

    if (tmp == NULL)
        return (0);
    if (times > 0)
        print_history(tmp->next, data, times - 1);
    if (data == false)
        printf("%6i %-5s ", tmp->id, tmp->hour);
    arr = str_to_word_array(tmp->line);
    printf("%s", arr[0]);
    for (int i = 1; arr[i] != NULL; i++) {
        printf(" %s", arr[i]);
    }
    printf("\n");
    return (0);
}

int only_numbers(char *av)
{
    if (av == NULL)
        return (1);
    for (int i = 0; av[i] != '\0'; i++) {
        if (av[i] < '0' || av[i] > '9')
            return (0);
    }
    return (1);
}

static int reset_history(infos_t *info)
{
    free_history(info->history);
    info->history = NULL;
    return (0);
}

int my_history(char **args, infos_t *info)
{
    history_t *tmp = info->history;
    int len = my_arrlen(args);

    if (len > 3)
        return (my_perror("history: Too many arguments.\n", 1));
    if (len == 2 && strcmp(args[1], "-c") == 0)
        return (reset_history(info));
    if (len == 1)
        return (print_history(tmp, false, 100));
    if (len == 2 && strcmp(args[1], "-h") == 0)
        return (print_history(tmp, true, 100));
    if (strcmp(args[1], "-h") == 0 && only_numbers(args[2]) == 1)
        return (print_history(tmp, true, atoi(args[2]) - 1));
    if (only_numbers(args[1]) == 0 || only_numbers(args[2]) == 0)
        return (my_perror("history: Badly formed number.\n", 1));
    return (print_history(tmp, false, atoi(args[1]) - 1));
}
