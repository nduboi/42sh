/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_echo
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(handle_input, test_handle_input_invalid_input)
{
    infos_t *infos = malloc(sizeof(infos_t));
    cr_assert_not_null(infos);

    char *input = "ls |";
    int result = handle_input(input, infos);
    cr_assert_eq(result, -1);
    free(infos);
}
