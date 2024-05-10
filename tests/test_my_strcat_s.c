/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_strcat_s.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_strcat_s, concatenate_two_strings, .init=redirect_all_std)
{
    char *str1 = "Hello, ";
    char *str2 = "world!";
    char *result = my_strcat_s(str1, str2);
    cr_assert_str_eq(result, "Hello, world!");
    free(result);
}

Test(my_strcat_s, first_string_null, .init=redirect_all_std)
{
    char *str2 = strdup("world!");
    char *result = my_strcat_s(NULL, str2);
    cr_assert_str_eq(result, "world!");
    free(result);
}
