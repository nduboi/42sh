/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** my_jobs
*/

#include "mysh.h"

char check_temp(jobs_t *temp)
{
    if (temp->next != NULL && temp->next->next == NULL) {
        return '-';
    } else if (temp->next == NULL) {
        return '+';
    } else {
        return ' ';
    }
}

int my_jobs(char **args, infos_t *info)
{
    jobs_t *temp = info->jobs;

    (void)args;
    while (temp != NULL) {
        printf("[%i]  %c %s %s\n", temp->num, check_temp(temp),
        temp->wd, temp->command);
        temp = temp->next;
    }
    return (0);
}
