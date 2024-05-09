/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** my_fg
*/

#include "mysh.h"
#include <sys/wait.h>
#include <signal.h>

void delete_current(int pid_d, jobs_t **jobs_ptr)
{
    jobs_t *current = *jobs_ptr;
    jobs_t *prev = current;

    if (current->pid == pid_d) {
        *jobs_ptr = current->next;
        free(current->wd);
        free(current->command);
        free(current);
        return;
    }
    current = current->next;
    while (current->pid != pid_d) {
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    free(current);
    return;
}

static int is_valid_arg(char *arg)
{
    if (arg[0] != '[' || arg[strlen(arg) - 1] != ']')
        return (0);
    for (int i = 1; i < my_strlen(arg) - 1; i++) {
        if (arg[i] < '0' || arg[i] > '9')
            return (0);
    }
    return (1);
}

static void put_fg_element(infos_t *infos, int num)
{
    jobs_t *current = infos->jobs;
    int status = 0;
    jobs_t **jobs_ptr = &infos->jobs;

    while (current != NULL && current->num != num) {
        current = current->next;
    }
    if (current == NULL) {
        fprintf(stderr, "fg: No such job.\n");
        return;
    }
    kill(current->pid, SIGCONT);
    waitpid(current->pid, &status, WUNTRACED);
    handle_signal(status);
    if (status != 5247) {
        delete_current(current->pid, jobs_ptr);
        infos->jobs = *jobs_ptr;
        update_exit(infos);
    }
}

void update_exit(infos_t *infos)
{
    jobs_t *temp = infos->jobs;
    int count = 0;

    while (temp != NULL) {
        count += 1;
        temp = temp->next;
    }
    if (count != 0)
        infos->can_exit_job = 0;
    else
        infos->can_exit_job = 1;
}

static void put_fg_last_element(infos_t *infos)
{
    jobs_t *current = infos->jobs;
    jobs_t **jobs_ptr = &infos->jobs;
    int status = 0;

    while (current->next != NULL)
        current = current->next;
    kill(current->pid, SIGCONT);
    waitpid(current->pid, &status, WUNTRACED);
    handle_signal(status);
    if (status != 5247) {
        delete_current(current->pid, jobs_ptr);
        infos->jobs = *jobs_ptr;
        update_exit(infos);
    }
}

int my_fg(char **args, infos_t *info)
{
    if (info->jobs == NULL) {
        fprintf(stderr, "fg: No current job\n");
        return (0);
    }
    if (my_arrlen(args) == 1) {
        put_fg_last_element(info);
    } else if (my_arrlen(args) == 2 && is_valid_arg(args[1])) {
        put_fg_element(info, my_get_nbr_lambda(args[1]));
    } else {
        put_fg_last_element(info);
    }
    return (0);
}
