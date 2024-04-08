/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_nbr_fcts
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_getnbr, get_a_nbr)
{
    cr_assert_eq(my_getnbr("42"), 42);
}

Test(my_getnbr, get_a_negative_nbr)
{
    cr_assert_eq(my_getnbr("-42"), -42);
}

Test(my_getnbr, get_a_negative_wrong_nbr)
{
    cr_assert_eq(my_getnbr("--42"), -1);
}

Test(my_getnbr, get_a_wrong_nbr)
{
    cr_assert_eq(my_getnbr("a"), -1);
}

Test(my_nbrlen, find_the_length)
{
    cr_assert_eq(my_nbrlen(42), 2);
}

Test(my_putnbr, display_a_number, .init=redirect_all_std)
{
    my_putnbr(42);
    cr_assert_stdout_eq_str("42");
}
