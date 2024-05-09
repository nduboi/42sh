/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** execute_in_bg
*/

#include "mysh.h"
#include <signal.h>
#include <string.h>

static void delete_current_bg(int pid_d, jobs_t **jobs_ptr)
{
    jobs_t *current = *jobs_ptr;
    jobs_t *prev = current;

    if (current->pid == pid_d) {
        *jobs_ptr = current->next;
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

static void manage_errors(char *pre, int error)
{
    write(2, pre, my_strlen(pre));
    if (error == ENOEXEC) {
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
    } else {
        write(2, ": Command not found.\n", 21);
    }
    exit(1);
}

static char **delete_bg_from_args(char **args)
{
    char **temp = malloc(sizeof(char *) * (my_arrlen(args)));
    int j = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "&")) {
            temp[i] = malloc(sizeof(char) * strlen(args[i]) + 1);
            strcpy(temp[i], args[i]);
            j++;
        }
    }
    temp[j] = NULL;
    return temp;
}

static void execute_in_bg_bis
(char **args, infos_t *infos, int pid, char **arr_env)
{
    int wstatus = 0;
    jobs_t **jobs_ptr = &infos->jobs;
    int pid_bis = fork();

    if (pid_bis == 0) {
        printf("[%i] %i\n", get_last_int(infos), pid);
        usleep(5000);
    } else {
        waitpid(pid, &wstatus, WUNTRACED);
        kill(pid_bis, SIGKILL);
        if (wstatus != 5247) {
            printf("[%i]-  Done\t%s\n", get_last_int(infos), args[0]);
            delete_current_bg(pid, jobs_ptr);
            infos->jobs = *jobs_ptr;
            update_exit(infos);
        }
        handle_signal(wstatus);
        free_double_array(arr_env);
    }
}

int execute_in_bg(char *path, char **args, char **arr_env, infos_t *infos)
{
    int pid = 0;

    pid = fork();
    args = delete_bg_from_args(args);
    if (pid == -1) {
        return -1;
    }
    if (pid > 0) {
        add_a_job_without_mess(path, args, pid, infos);
        execute_in_bg_bis(args, infos, pid, arr_env);
    } else {
        signal(SIGTSTP, SIG_DFL);
        execve(path, args, arr_env);
        free_double_array(arr_env);
        manage_errors(args[0], errno);
    }
    return 0;
}
