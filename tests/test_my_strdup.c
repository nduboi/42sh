/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** tests_my_strcmp
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>

Test(my_strdup, dup_a_str)
{
    char *dest;
    char *src = "hello";

    dest = my_strdup(src);
    cr_assert_str_eq(dest, src);
}
