/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_parentheses_errors.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(too_many_parenthesis, after_wrong, .init=redirect_all_std)
{
    char *cmd = "(ls))";
    bool result = too_many_parenthesis(cmd);
    cr_assert_eq(result, true, "Expected true, got false");
}

Test(too_many_parenthesis, before_wrong, .init=redirect_all_std)
{
    char *cmd = "(((ls)";
    bool result = too_many_parenthesis(cmd);
    cr_assert_eq(result, true, "Expected true, got false");
}

Test(too_many_parenthesis, ok_parenthesis, .init=redirect_all_std)
{
    char *cmd = "(ls)";
    bool result = too_many_parenthesis(cmd);
    cr_assert_eq(result, false, "Expected false, got true");
}
