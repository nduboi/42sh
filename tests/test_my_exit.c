/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_exit
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(good_number, big_nbr, .init=redirect_all_std)
{
    char *args = strdup("110");
    int some = good_number(args);
    cr_assert_eq(some, 1);
}

Test(good_number, wrong_nbr, .init=redirect_all_std)
{
    char *args = strdup("110-");
    int some = good_number(args);
    cr_assert_eq(some, 0);
}

Test(my_exit, badly_formed_nbr, .init=redirect_all_std)
{
    char *args[3] = {"exit", "0foo", NULL};
    infos_t *infos = malloc(sizeof(infos_t));

    infos->envs = malloc(sizeof(env_t));
    infos->envs->env = malloc(sizeof(list_t *));
    infos->envs->env_cpy = malloc(sizeof(list_t *));
    *infos->envs->env = NULL;
    *infos->envs->env_cpy = NULL;
    int status = my_exit(args, infos);
    cr_assert_eq(status, -1, "status actually is %i\n", status);
}

Test(my_exit, badly_formed_nbr_second_case, .init=redirect_all_std)
{
    char *args[3] = {"exit", "0.", NULL};
    infos_t *infos = malloc(sizeof(infos_t));

    infos->envs = malloc(sizeof(env_t));
    infos->envs->env = malloc(sizeof(list_t *));
    infos->envs->env_cpy = malloc(sizeof(list_t *));
    *infos->envs->env = NULL;
    *infos->envs->env_cpy = NULL;
    my_exit(args, infos);
    cr_assert_stderr_eq_str("exit: Badly formed number.\n");
}

Test(exit_number, well_formed_number, .init=redirect_all_std)
{
    char *args[3] = {"exit", "0.", NULL};
    infos_t *infos = malloc(sizeof(infos_t));

    infos->envs = malloc(sizeof(env_t));
    infos->envs->env = malloc(sizeof(list_t *));
    infos->envs->env_cpy = malloc(sizeof(list_t *));
    *infos->envs->env = NULL;
    *infos->envs->env_cpy = NULL;
    exit_number(args, infos);
    cr_assert_stderr_eq_str("exit: Badly formed number.\n");
}