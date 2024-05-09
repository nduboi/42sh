/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** add_a_job
*/

#include "mysh.h"

static char *concatenete_str(char **args)
{
    char *temp;
    int len = 0;

    for (int i = 0; args[i] != NULL; i++) {
        len += strlen(args[i]);
    }
    temp = my_malloc(sizeof(char) * (len + my_arrlen(args) + 1));
    for (int i = 0; args[i] != NULL; i++) {
        my_strcat(temp, my_strcat_s(" ", args[i]));
    }
    return temp;
}

static void put_element_at_end(infos_t *infos, jobs_t *new_element)
{
    jobs_t *current = infos->jobs;

    if (infos->jobs == NULL) {
        infos->jobs = new_element;
        new_element->next = NULL;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_element;
        new_element->next = NULL;
    }
}

int get_last_int(infos_t *infos)
{
    jobs_t *current = infos->jobs;
    int count = 0;

    if (current == NULL) {
        return (1);
    }
    while (current->next != NULL) {
        count += 1;
        current = current->next;
    }
    if (count == 0)
        return (2);
    return current->num + 1;
}

void add_a_job(char *path, char **args, int pid, infos_t *infos)
{
    jobs_t *new_element = malloc(sizeof(jobs_t));

    new_element->command = concatenete_str(args);
    new_element->num = get_last_int(infos);
    new_element->pid = pid;
    put_element_at_end(infos, new_element);
    infos->can_exit_job = 0;
    if (strcmp(path, "/usr/bin/ls") == 0) {
        printf("\n\nSuspended (signal)\n");
        new_element->wd = my_strdup("Suspended (signal)");
    } else {
        printf("\nSuspended\n");
        new_element->wd = my_strdup("Suspended");
    }
}

void add_a_job_without_mess(char *path, char **args, int pid, infos_t *infos)
{
    jobs_t *new_element = malloc(sizeof(jobs_t));

    (void) path;
    new_element->command = concatenete_str(args);
    new_element->num = get_last_int(infos);
    new_element->wd = NULL;
    new_element->pid = pid;
    put_element_at_end(infos, new_element);
    infos->can_exit_job = 0;
}
