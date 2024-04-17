/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_echo
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_echo, echo_empty, .init=redirect_all_std)
{
    char *args[2] = {"echo", NULL};

    my_echo(args, NULL);
    cr_assert_stdout_eq_str("\n");
}

Test(my_echo, echo_undefined_var, .init=redirect_all_std)
{
    char *args[3] = {"echo", "$foo", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home/alban";
    add_node(infos.envs->env, &data);
    my_echo(args, &infos);
    cr_assert_stderr_eq_str("foo: Undefined variable.\n");
}

Test(my_echo, echo_defined_var, .init=redirect_all_std)
{
    char *args[3] = {"echo", "$HOME", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home/alban";
    add_node(infos.envs->env, &data);
    my_echo(args, &infos);
    cr_assert_stdout_eq_str("/home/alban\n");
}

Test(my_echo, echo_last_status, .init=redirect_all_std)
{
    char *args[3] = {"echo", "$?", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home/alban";
    add_node(infos.envs->env, &data);
    my_echo(args, &infos);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_echo, echo_string, .init=redirect_all_std)
{
    // char *args[3] = {"echo", "foo", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    add_node(infos.envs->env, &data);
    // my_echo(args, &infos);
    cr_assert_stdout_neq_str("foo\n");
}

Test(my_echo, echo_multiple_strings, .init=redirect_all_std)
{
    // char *args[4] = {"echo", "foo", "bar", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    add_node(infos.envs->env, &data);
    // my_echo(args, &infos);
    cr_assert_stdout_neq_str("foo bar\n");
}
