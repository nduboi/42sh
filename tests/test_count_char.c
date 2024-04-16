/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_count_char
*/

#include "mysh.h"
#include <criterion/criterion.h>

Test(count_char_in_str, count_chars)
{
    char *str = "Hello World";
    char c = 'l';

    cr_assert_eq(count_char_in_str(str, c), 3);
}
