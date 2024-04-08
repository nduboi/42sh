/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** tests_my_strcpy
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>

Test(my_strcpy, cpy_a_str)
{
    char dest[6];
    char *src = "hello";

    my_strcpy(dest, src);
    cr_assert_str_eq(dest, src);
}
