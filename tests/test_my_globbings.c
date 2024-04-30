/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_globbing_*_?
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(handle_globbings, handle_globbings_empty, .init=redirect_all_std)
{
    char *args = strdup("echo");

    handle_globbings(&args);
    cr_assert_str_eq("echo", args);
}

Test(handle_globbings, handle_globbings_no_match_star, .init=redirect_all_std)
{
    char *args = strdup("ls *.q");

    handle_globbings(&args);
    cr_assert_stderr_eq_str("ls: No match.\n");
}

Test(handle_globbings, handle_globbings_no_match_question, .init=redirect_all_std)
{
    char *args = strdup("echo ?.q");

    handle_globbings(&args);
    cr_assert_stderr_eq_str("echo: No match.\n");
}

Test(handle_globbings, handle_globbings_still_no_match, .init=redirect_all_std)
{
    char *args = strdup("ls tests/kill*");

    handle_globbings(&args);
    cr_assert_str_eq("ls tests/kill tests/kill.c", args);
}

Test(handle_globbings, handle_globbings_no_globbing, .init=redirect_all_std)
{
    char *args = strdup("ls abcdefg");

    handle_globbings(&args);
    cr_assert_str_eq("ls abcdefg", args);
}

