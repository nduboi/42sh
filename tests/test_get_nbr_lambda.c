/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_get_nbr_lambda.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_compute_power_rec, positive_power, .init=redirect_all_std)
{
    int nb = 2;
    int p = 3;
    int result = my_compute_power_rec(nb, p);
    cr_assert_eq(result, 8);
}

Test(my_compute_power_rec, negative_power, .init=redirect_all_std)
{
    int nb = 2;
    int p = -3;
    int result = my_compute_power_rec(nb, p);
    cr_assert_eq(result, 0);
}

Test(get_nbr_len, simple_number, .init=redirect_all_std)
{
    char *str = "12345";
    int i = 0;
    int result = get_nbr_len(str, i);
    cr_assert_eq(result, 4);
}

Test(my_get_nbr_lambda, simple_number, .init=redirect_all_std)
{
    char *str = "12345";
    int result = my_get_nbr_lambda(str);
    cr_assert_eq(result, 12345);
}
