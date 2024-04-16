/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_unsetenv
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_unsetenv, too_few_args, .init=redirect_all_std)
{
    char *args[2] = {"unsetenv", NULL};

    my_unsetenv(args, NULL);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
}

Test(my_unsetenv, star_argument, .init=redirect_all_std)
{
    char *args[3] = {"unsetenv", "*", NULL};
    infos_t infos;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    my_unsetenv(args, &infos);
    cr_assert_stderr_eq_str("unsetenv: Can't take '*' argument.\n");
}

Test(my_unsetenv, delete_var)
{
    char *args_unset[3] = {"unsetenv", "foo", NULL};
    char *args_set[4] = {"setenv", "foo", "bar", NULL};
    infos_t infos;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    my_setenv(args_set, &infos);
    my_unsetenv(args_unset, &infos);
    cr_assert_eq(*infos.envs->env, NULL);
}

Test(my_unsetenv, delete_absent_var, .init=redirect_all_std)
{
    char *args_unset[3] = {"unsetenv", "bar", NULL};
    char *args_set[4] = {"setenv", "foo", "bar", NULL};
    char *args_env[2] = {"env", NULL};
    infos_t infos;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    my_setenv(args_set, &infos);
    my_unsetenv(args_unset, &infos);
    my_env(args_env, &infos);
    cr_assert_stdout_eq_str("foo=bar\n");
}
