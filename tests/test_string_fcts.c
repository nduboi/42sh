/*
** EPITECH PROJECT, 2024
** alban
** File description:
** test_string_fcts
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>

Test(my_arrlen, find_len_of_array)
{
    char *array[10] = {
        "H", "E", "L", "L", "O", NULL
    };
    cr_assert_eq(my_arrlen(array), 5);
}

Test(my_strlen, find_len_of_a_word)
{
    int len = 5;
    char *word = "HELLO";

    cr_assert_eq(my_strlen(word), len);
}

// Test(count_tokens, count_words_of_a_string)
// {
//     char string[12] = "Hello World";

//     cr_assert_eq(count_tokens(string, " "), 2);
// }

// Test(count_tokens, count_words_of_empty_string)
// {
//     char string[1] = "";

//     cr_assert_eq(count_tokens(string, " "), 0);
// }

Test(str_to_word_array, transform_string_into_array)
{
    char string[12] = "Hello World";
    char **array = str_to_word_array(string);

    cr_assert_str_eq(array[0], "Hello");
}

Test(my_strcmp, compare_same_trings)
{
    char *str = "Hello";
    char *str2 = "Hello";

    cr_assert_eq(my_strcmp(str, str2), 0);
}

Test(my_strcmp, compare_different_trings)
{
    char *str = "Hello";
    char *str2 = "World";

    cr_assert_neq(my_strcmp(str, str2), 0);
}

Test(my_strcmp, compare_almost_same_trings)
{
    char *str = "Hello";
    char *str2 = "Hell";

    cr_assert_neq(my_strcmp(str, str2), 0);
}

Test(my_strcmp, compare_empty_trings)
{
    char *str = "";
    char *str2 = "";

    cr_assert_eq(my_strcmp(str, str2), 0);
}
