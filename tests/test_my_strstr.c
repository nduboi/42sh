/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_strstr
*/

#include "mysh.h"
#include <criterion/criterion.h>

Test(my_strstr, find_a_good_needle)
{
    char *hay = "Hello World";
    char *needle = "World";
    char *result = my_strstr(hay, needle);

    cr_assert_str_eq(result, hay + 6);
}

Test(my_strstr, find_a_bad_needle)
{
    char *hay = "Hello";
    char *needle = "Hello World";
    char *result = my_strstr(hay, needle);

    cr_assert_eq(result, NULL);
}
