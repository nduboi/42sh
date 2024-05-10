/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_environement_cut_part.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(cut_in_part, simple_case, .init=redirect_all_std)
{
    char *data = "before${VAR} after";
    char *part1 = NULL;
    char *part2 = NULL;
    cut_in_part(data, &part1, &part2);
    cr_assert_str_eq(part1, "before");
    cr_assert_str_eq(part2, "after");
    free(part1);
    free(part2);
}

Test(cut_in_part_brakets, simple_case, .init=redirect_all_std)
{
    char *data = "before${VAR}after";
    char *part1 = NULL;
    char *part2 = NULL;
    cut_in_part_brakets(data, &part1, &part2);
    cr_assert_str_eq(part1, "before");
    cr_assert_str_eq(part2, "after");
    free(part1);
    free(part2);
}
