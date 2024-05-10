/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_parsing.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(insert_spaces, no_spaces_needed, .init=redirect_all_std)
{
    char *str = strdup("key=value");
    char *result = insert_spaces(str);
    cr_assert_str_eq(result, "key = value");
    free(result);
}

Test(arr_to_str, simple_strings, .init=redirect_all_std)
{
    char *args[] = {"hello", "world", NULL};
    char *result = arr_to_str(args);
    cr_assert_str_eq(result, "hello world ");
    free(result);
}
