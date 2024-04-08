/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_cd
*/

#include "mysh.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

char *get_env_var(char *key, list_t **env)
{
    list_t *node = *env;
    var_t *temp = NULL;

    while (node) {
        temp = node->data;
        if (my_strcmp(temp->name, key) == 0) {
            return temp->val;
        }
        node = node->next;
    }
    return NULL;
}

int change_directory(char *path, infos_t *infos, char **oldpwd)
{
    char *args[4] = {"cd", "PWD", NULL, NULL};
    char *cwd = NULL;
    char *temp = NULL;

    temp = getcwd(NULL, 0);
    if (chdir(path) == -1) {
        error_message(path, errno);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    *oldpwd = temp;
    cwd = getcwd(NULL, 0);
    args[2] = cwd;
    my_setenv(args, infos);
    handle_exit_status(WRITE_STATUS, 0);
    return 0;
}

char *home_path(env_t *envs)
{
    char *path = NULL;
    char *temp = NULL;

    path = get_env_var("HOME", envs->env);
    if (!path) {
        path = get_env_var("HOME", envs->env_cpy);
    }
    if (access(path, F_OK)) {
        write(2, "cd: Can't change to home directory.\n", 36);
        handle_exit_status(WRITE_STATUS, 1);
        return NULL;
    }
    return path;
}

int my_cd(char **args, infos_t *infos)
{
    char *path = NULL;
    static char *oldpwd = "";

    if (my_arrlen(args) > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    if (args[1] == NULL || my_strcmp(args[1], "~") == 0) {
        path = home_path(infos->envs);
    } else if (my_strcmp(args[1], "-") == 0) {
        path = oldpwd;
    } else {
        path = args[1];
    }
    if (!path) {
        return -1;
    }
    return change_directory(path, infos, &oldpwd);
}
