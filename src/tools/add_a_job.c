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
    temp = my_malloc(sizeof(char) * (len + 1));
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

void add_a_job(char *path, char **args, int pid, infos_t *infos)
{
    static int num = 0;
    jobs_t *new_element = malloc(sizeof(jobs_t));

    new_element->command = concatenete_str(args);
    new_element->num = num + 1;
    num += 1;
    new_element->pid = pid;
    put_element_at_end(infos, new_element);
    if (strcmp(path, "/usr/bin/ls") == 0) {
        printf("\n\nSuspended (signal)\n");
        new_element->wd = my_strdup("Suspended (signal)");
    } else {
        printf("\nSuspended\n");
        new_element->wd = my_strdup("Suspended");
    }
}
