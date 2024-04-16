/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_setenv
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_setenv, display_env, .init=redirect_all_std)
{
    char *args[2] = {"setenv", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home/alban";
    add_node(infos.envs->env, &data);
    my_setenv(args, &infos);
    cr_assert_stdout_eq_str("HOME=/home/alban\n");
}

Test(my_setenv, too_many_args, .init=redirect_all_std)
{
    char *args[5] = {"setenv", "foo", "bar", "foo", NULL};

    my_setenv(args, NULL);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
}

Test(my_setenv, bad_first_char, .init=redirect_all_std)
{
    char *args[4] = {"setenv", "0foo", "bar", NULL};

    my_setenv(args, NULL);
    cr_assert_stderr_eq_str("setenv: Variable name must begin with a letter.\n");
}

Test(my_setenv, bad_name, .init=redirect_all_std)
{
    char *args[4] = {"setenv", "fo=o", "bar", NULL};

    my_setenv(args, NULL);
    cr_assert_stderr_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
}

Test(my_setenv, good_name)
{
    char *args[4] = {"setenv", "foo", "bar", NULL};
    infos_t infos;
    var_t *data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    my_setenv(args, &infos);
    data = (*infos.envs->env)->data;
    cr_assert_str_eq(data->name, "foo");
    cr_assert_str_eq(data->val, "bar");
}

Test(my_setenv, good_name_no_val)
{
    char *args[3] = {"setenv", "foo", NULL};
    infos_t infos;
    var_t *data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    my_setenv(args, &infos);
    data = (*infos.envs->env)->data;
    cr_assert_str_eq(data->name, "foo");
    cr_assert_str_eq(data->val, "");
}

Test(my_setenv, replace_existing_var)
{
    char *args[4] = {"setenv", "foo", "bar", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "foo";
    data.val = "foo";
    add_node(infos.envs->env, &data);
    my_setenv(args, &infos);
    cr_assert_str_eq(data.val, "bar");
}

