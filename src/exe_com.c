/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** exe_com
*/

#include "mysh.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>

static char *create_path(char *pre, char *post)
{
    char *result = NULL;
    int len_pre = my_strlen(pre);
    int len_post = my_strlen(post);

    result = malloc(sizeof(char) * (len_pre + len_post + 2));
    my_memset(result, 0, sizeof(char) * (len_pre + len_post + 2));
    my_strcat(result, pre);
    if (pre[len_pre - 1] != '/' && *post != '/' && *post) {
        my_strcat(result, "/");
    }
    my_strcat(result, post);
    return result;
}

char *find_path(var_t *var, char *command)
{
    char *path = my_strdup(var->val);
    char *token = strtok(path, ":");
    char *result = malloc(1);
    int len = my_strlen(command);

    do {
        free(result);
        if (!token) {
            return "";
        }
        result = create_path(token, command);
        token = strtok(NULL, ":");
    } while (access(result, F_OK) == -1);
    free(path);
    return result;
}

char *get_path(char *cmd, list_t **env)
{
    char *result = NULL;
    list_t *node = NULL;

    if (my_strstr(cmd, "/") && cmd[0] != '~') {
        return cmd;
    }
    if (cmd[0] == '~' && cmd[1] == '/') {
        node = find_node(env, "HOME");
        result = create_path(((var_t *) node->data)->val, cmd + 1);
        return result;
    }
    node = find_node(env, "PATH");
    if (!node) {
        return NULL;
    }
    result = find_path(node->data, cmd);
    return result;
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

int execute(char *path, char **args, char **arr_env)
{
    int pid = 0;
    int wstatus = 0;

    pid = fork();
    if (pid == -1){
        return -1;
    }
    if (pid > 0) {
        waitpid(pid, &wstatus, 0);
        handle_signal(wstatus);
        free_double_array(arr_env);
        return 0;
    } else {
        execve(path, args, arr_env);
        free_double_array(arr_env);
        manage_errors(args[0], errno);
    }
}

static bool not_permitted(char *path, DIR *dir)
{
    return (access(path, F_OK) == 0 &&
        (access(path, X_OK) < 0 || (dir && my_strstr(path, "/"))));
}

int exe_cmd(char **args, infos_t *infos)
{
    char **arr_env = chained_list_to_normal(infos->envs->env);
    char *path = get_path(args[0], infos->envs->env);
    DIR *dir = NULL;

    if (!path) {
        path = get_path(args[0], infos->envs->env_cpy);
    }
    path = !path ? args[0] : path;
    args[0] = args[0][0] == '~' ? path : args[0];
    dir = opendir(path);
    closedir(dir);
    if (not_permitted(path, dir)) {
        write(2, path, my_strlen(path));
        write(2, ": Permission denied.\n", 21);
        handle_exit_status(WRITE_STATUS, 1);
        return -1;
    }
    return execute(path, args, arr_env);
}
