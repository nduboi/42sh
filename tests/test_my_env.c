/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_env
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_env, too_many_args, .init=redirect_all_std)
{
    char *args[3] = {"env", "foo", NULL};

    my_env(args, NULL);
    cr_assert_stderr_eq_str("env: No arguments needed.\n");
}

Test(my_env, display_env, .init=redirect_all_std)
{
    char *args[2] = {"env", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home/alban";
    add_node(infos.envs->env, &data);
    my_env(args, &infos);
    cr_assert_stdout_eq_str("HOME=/home/alban\n");
}
