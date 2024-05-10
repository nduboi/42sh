/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_only_char_in_str.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(only_char_in_str, all_chars_are_same, .init=redirect_all_std)
{
    char *str = "aaa";
    char c = 'a';

    cr_assert(only_char_in_str(str, c));
}

Test(only_char_in_str, not_all_chars_are_same, .init=redirect_all_std)
{
    char *str = "aab";
    char c = 'a';

    cr_assert_not(only_char_in_str(str, c));
}

Test(only_char_in_str, empty_string, .init=redirect_all_std)
{
    char *str = "";
    char c = 'a';

    cr_assert(only_char_in_str(str, c));
}
