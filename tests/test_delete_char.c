/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_delete_char.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(delete_char, simple_case, .init=redirect_all_std)
{
    char str[] = "Hello World";
    char c = 'o';
    delete_char(str, c);
    cr_assert_str_eq(str, "Hell Wrld");
}
