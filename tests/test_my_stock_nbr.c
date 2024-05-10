/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_stock_nbr.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_stock_nbr, positive_number, .init=redirect_all_std)
{
    int nb = 12345;
    char *result = my_stock_nbr(nb);
    cr_assert_str_eq(result, "12345");
    free(result);
}

Test(my_stock_nbr, negative_number, .init=redirect_all_std)
{
    int nb = -12345;
    char *result = my_stock_nbr(nb);
    cr_assert_str_eq(result, "12345");
    free(result);
}

Test(my_stock_nbr, positive_small_number, .init=redirect_all_std)
{
    int nb = 1;
    char *result = my_stock_nbr(nb);
    cr_assert_str_eq(result, "1");
    free(result);
}

Test(my_stock_nbr, positive_0, .init=redirect_all_std)
{
    int nb = 0;
    char *result = my_stock_nbr(nb);
    cr_assert_str_eq(result, "0");
    free(result);
}