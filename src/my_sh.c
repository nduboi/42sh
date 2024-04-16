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
    (void) num;
    write(1, "\b\b\033[K\n$> ", 9);
}

static void copy_in_list(list_t **copy, char **env, int size)
{
    var_t *var = NULL;
    char *temp = NULL;

    for (int i = 0; i < size; i++) {
        var = malloc(sizeof(var_t));
        var->name = strtok_r(env[i], "=", &env[i]);
        temp = strtok_r(env[i], "", &env[i]);
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

    len = getline(&buffer, &size, stdin);
    if (len == EOF) {
        if (isatty(STDIN_FILENO)) {
            write(1, "exit\n", 5);
        }
        free_infos(infos);
        exit(handle_exit_status(GET_STATUS, 0));
    }
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    return buffer;
}

void input_loop(infos_t *infos)
{
    char *input = NULL;

    while (1) {
        if (infos->isatty)
            write_prompt(infos->envs);
        input = get_input(infos);
        input = check_exclamation(input, infos);
        if (input != NULL) {
            add_history(infos, input);
            parse_input(input, infos);
        }
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
    if (!infos->envs->env || !infos->envs->env_cpy) {
        return -1;
    }
    infos->isatty = isatty(STDIN_FILENO);
    signal(SIGINT, handler);
    input_loop(infos);
    return 0;
}
