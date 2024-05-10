/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_realloc.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_realloc, increase_memory_size, .init=redirect_all_std)
{
    char *ptr = my_malloc(5);
    my_strcpy(ptr, "hello");

    char *result = my_realloc(ptr, 10);
    cr_assert_str_eq(result, "hello");
    free(result);
}
