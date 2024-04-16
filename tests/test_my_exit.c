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

Test(my_exit, error_expression_syntaxe, .init=redirect_all_std)
{
    char *args[4] = {"exit", "foo", "bar", NULL};

    my_exit(args, NULL);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
}

Test(my_exit, error_expression_syntaxe_second_case, .init=redirect_all_std)
{
    char *args[4] = {"exit", "foo", NULL};

    my_exit(args, NULL);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
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
    my_exit(args, infos);
    cr_assert_stderr_eq_str("exit: Badly formed number.\n");
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
