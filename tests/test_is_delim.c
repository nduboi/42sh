/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_is_delim.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(is_delim, valid_delimiter, .init=redirect_all_std)
{
    char *str = ";";
    cr_assert(is_delim(str), "Expected true for valid delimiter");
}

Test(is_delim, not_valid_delimiter, .init=redirect_all_std)
{
    char *str = "a";
    cr_assert(!is_delim(str), "Expected false for valid delimiter");
}
