/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** my_bg
*/

#include "mysh.h"
#include <signal.h>

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

static void finish_a_bg_job(jobs_t *current, jobs_t **jobs_ptr, infos_t *infos)
{
    printf("[%i]  %c Exit 2 %s\n", current->num,
    check_temp(current), current->command);
    delete_current(current->pid, jobs_ptr);
    infos->jobs = *jobs_ptr;
    update_exit(infos);
}

static void put_bg_element(infos_t *infos, int num)
{
    jobs_t *current = infos->jobs;
    int status = 0;
    jobs_t **jobs_ptr = &infos->jobs;
    pid_t pid;

    while (current != NULL && current->num != num)
        current = current->next;
    if (current == NULL) {
        fprintf(stderr, "bg: No such job.\n");
        return;
    }
    kill(current->pid, SIGCONT);
    pid = fork();
    if (pid != 0) {
        waitpid(current->pid, &status, WUNTRACED);
        kill(pid, SIGKILL);
        handle_signal(status);
        if (status != 5247)
            finish_a_bg_job(current, jobs_ptr, infos);
    }
}

static void put_bg_last_element(infos_t *infos)
{
    jobs_t *current = infos->jobs;
    jobs_t **jobs_ptr = &infos->jobs;
    int status = 0;
    pid_t pid;

    while (current->next != NULL)
        current = current->next;
    kill(current->pid, SIGCONT);
    pid = fork();
    if (pid != 0) {
        waitpid(current->pid, &status, WUNTRACED);
        kill(pid, SIGKILL);
        handle_signal(status);
        if (status != 5247)
            finish_a_bg_job(current, jobs_ptr, infos);
    }
}

int my_bg(char **args, infos_t *info)
{
    if (info->jobs == NULL) {
        fprintf(stderr, "bg: No current job\n");
        return (0);
    }
    if (my_arrlen(args) == 1) {
        put_bg_last_element(info);
    } else if (my_arrlen(args) == 2 && is_valid_arg(args[1])) {
        put_bg_element(info, my_get_nbr_lambda(args[1]));
    } else {
        put_bg_last_element(info);
    }
    return (0);
}
