/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_setenv
*/

#include "mysh.h"
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int add_var(char *name, char *val, list_t **env)
{
    list_t *node = *env;
    var_t *temp = NULL;

    if (!val) {
        val = "";
    }
    while (node) {
        temp = node->data;
        if (my_strcmp(temp->name, name) == 0) {
            temp->val = val;
            return 0;
        }
        node = node->next;
    }
    temp = malloc(sizeof(var_t));
    temp->name = name;
    temp->val = val;
    add_node(env, temp);
    return 0;
}

int is_num(char c)
{
    if ('0' <= c && c <= '9') {
        return 1;
    }
    return 0;
}

int is_alpha(char c)
{
    if ('A' <= c && c <= 'Z') {
        return 1;
    }
    if ('a' <= c && c <= 'z') {
        return 1;
    }
    return 0;
}

int errors(char **args)
{
    if (my_arrlen(args) > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        handle_exit_status(WRITE_STATUS, 1);
        return 1;
    }
    if (!is_alpha(args[1][0]) && args[1][0] != '_') {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        handle_exit_status(WRITE_STATUS, 1);
        return 1;
    }
    for (int i = 1; args[1][i]; i++) {
        if (!is_alpha(args[1][i]) && !is_num(args[1][i])
            && args[1][i] != '_') {
            write(2, "setenv: "
                "Variable name must contain alphanumeric characters.\n", 60);
            handle_exit_status(WRITE_STATUS, 1);
            return 1;
        }
    }
    return 0;
}

int my_setenv(char **args, infos_t *infos)
{
    if (!args[1]) {
        my_env(args, infos);
        return 0;
    }
    if (errors(args)) {
        return -1;
    }
    if (add_var(args[1], args[2], infos->envs->env) < 0) {
        write(2, "setenv: memory error\n", 21);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    handle_exit_status(WRITE_STATUS, 0);
    return 0;
}
