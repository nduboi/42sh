/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** write_prompt
*/

#include "mysh.h"

char *get_short_pwd(env_t *env)
{
    char *pwd = getcwd(NULL, 0);
    char *home = get_env_var("HOME", env->env_cpy);

    printf("%s\n", home);
    return (pwd);
}

void write_prompt(env_t *env)
{
    char *hostname = get_env_var("HOSTNAME", env->env_cpy);
    char *user = get_env_var("USER", env->env_cpy);
    char *pwd = get_short_pwd(env);

    printf("[%s", (hostname == NULL ? "hostname" : hostname));
    printf("@%s", (user == NULL ? "user" : user));
    printf(" %s]$ ", (pwd == NULL ? "pwd" : pwd));
    if (pwd != NULL)
        free(pwd);
}
