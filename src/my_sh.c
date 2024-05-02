/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_sh
*/

#include "mysh.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void handler(int num)
{
    char *hostname = getenv("HOSTNAME");
    char *user = getenv("USER");
    char *pwd = getcwd(NULL, 0);
    char *dir = pwd;

    (void) num;
    while (dir && my_strstr(dir, "/")) {
        dir = my_strstr(dir, "/") + 1;
    }
    printf("\b\b\033\n");
    printf("\033[31m");
    printf("[%s", (user == NULL ? "user" : user));
    printf("@%s", (hostname == NULL ? "hostname" : hostname));
    printf(" %s]$ ", (dir == NULL ? "pwd" : dir));
    printf("\033[0m");
    fflush(stdout);
}

static void copy_in_list(list_t **copy, char **env, int size)
{
    var_t *var = NULL;
    char *temp = NULL;
    char *dup = NULL;

    for (int i = 0; i < size; i++) {
        dup = my_strdup(env[i]);
        var = malloc(sizeof(var_t));
        var->name = strtok_r(dup, "=", &dup);
        temp = strtok_r(dup, "", &dup);
        if (temp) {
            var->val = temp;
        } else {
            var->val = "";
        }
        add_node(copy, var);
    }
}

list_t **copy_env(char **env)
{
    list_t **copy = malloc(sizeof(list_t *));
    int size = my_arrlen(env);

    if (!copy) {
        return NULL;
    }
    *copy = NULL;
    copy_in_list(copy, env, size);
    return copy;
}

char *get_input(infos_t *infos)
{
    size_t size = 0;
    char *buffer = NULL;
    int len = 0;

    if (isatty(STDIN_FILENO) == 0) {
        len = getline(&buffer, &size, stdin);
        if (buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
    } else
        buffer = getline_modif(infos, &len);
    if (len == EOF) {
        if (isatty(STDIN_FILENO))
            write(1, "exit\n", 5);
        free_infos(infos);
        exit(handle_exit_status(GET_STATUS, 0));
    }
    return buffer;
}

void input_loop(infos_t *infos)
{
    int status = 0;
    char *input = NULL;

    while (1) {
        if (infos->isatty)
            write_prompt(infos->envs);
        input = get_input(infos);
        input = check_exclamation(input, infos);
        if (input != NULL) {
            add_history(infos, input);
            status = handle_input(input, infos);
        }
        if (status == 1 && !infos->isatty)
            exit(handle_exit_status(GET_STATUS, 0));
    }
}

int my_sh(char **env)
{
    infos_t *infos = malloc(sizeof(infos_t));

    infos->envs = malloc(sizeof(env_t));
    infos->envs->env = copy_env(env);
    infos->envs->env_cpy = copy_env(env);
    infos->history = NULL;
    infos->alias = NULL;
    infos->jobs = NULL;
    infos->vars = NULL;
    infos->can_exit_job = 1;
    if (!infos->envs->env || !infos->envs->env_cpy) {
        return -1;
    }
    infos->isatty = isatty(STDIN_FILENO);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT, handler);
    input_loop(infos);
    return 0;
}
