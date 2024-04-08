/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_history
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>

Test(add_history, add_one_node)
{
    infos_t info;

    info.history = NULL;
    add_history(&info, "salut");
    cr_assert_str_eq(info.history->line, "salut");
}

Test(add_history, add_multiple_nodes)
{
    infos_t info;

    info.history = NULL;
    add_history(&info, "salut");
    add_history(&info, "salut");
    add_history(&info, "salam");
    add_history(&info, "salut");
    cr_assert_str_eq(info.history->line, "salut");
    cr_assert_str_eq(info.history->next->line, "salam");
    cr_assert_str_eq(info.history->next->next->line, "salut");
    cr_assert_eq(info.history->next->next->next, NULL);
}

Test(my_history, display_simple)
{
    infos_t info;

    info.history = NULL;
    add_history(&info, "salut");
    add_history(&info, "salut");
    add_history(&info, "salam");
    add_history(&info, "salut");
    cr_assert_eq(my_history(str_to_word_array("history"), &info), 0);
}

Test(my_history, display_h)
{
    char **arr = malloc(sizeof(char *) * 3);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("-h");
    arr[2] = NULL;
    info.history = NULL;
    add_history(&info, "history -h");
    cr_assert_eq(my_history(arr, &info), 0);
}

Test(my_history, display_number)
{
    char **arr = malloc(sizeof(char *) * 3);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("6");
    arr[2] = NULL;
    info.history = NULL;
    add_history(&info, "history 6");
    cr_assert_eq(my_history(arr, &info), 0);
}

Test(my_history, display_less_number)
{
    char **arr = malloc(sizeof(char *) * 3);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("2");
    arr[2] = NULL;
    info.history = NULL;
    add_history(&info, "history 6");
    add_history(&info, "history 7");
    add_history(&info, "history 8");
    add_history(&info, "history 9");
    cr_assert_eq(my_history(arr, &info), 0);
}

Test(my_history, display_both)
{
    char **arr = malloc(sizeof(char *) * 4);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("-h");
    arr[2] = strdup("2");
    arr[3] = NULL;
    info.history = NULL;
    add_history(&info, "history 6");
    add_history(&info, "history 7");
    add_history(&info, "history 8");
    add_history(&info, "history 9");
    cr_assert_eq(my_history(arr, &info), 0);
}


Test(my_history, wrong_arg1)
{
    char **arr = malloc(sizeof(char *) * 5);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("foo");
    arr[2] = strdup("foo");
    arr[3] = strdup("foo");
    arr[4] = NULL;
    info.history = NULL;
    add_history(&info, "history foo foo foo");
    cr_assert_eq(my_history(arr, &info), 1);
}

Test(my_history, wrong_arg2)
{
    char **arr = malloc(sizeof(char *) * 4);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("foo");
    arr[2] = strdup("foo");
    arr[3] = NULL;
    info.history = NULL;
    add_history(&info, "history foo foo");
    cr_assert_eq(my_history(arr, &info), 1);
}

Test(my_history, wrong_arg3)
{
    char **arr = malloc(sizeof(char *) * 4);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("-h");
    arr[2] = strdup("foo");
    arr[3] = NULL;
    info.history = NULL;
    add_history(&info, "history foo foo");
    cr_assert_eq(my_history(arr, &info), 1);
}

Test(my_history, wrong_arg4)
{
    char **arr = malloc(sizeof(char *) * 4);
    infos_t info;

    arr[0] = strdup("history");
    arr[1] = strdup("2");
    arr[2] = strdup("-2");
    arr[3] = NULL;
    info.history = NULL;
    add_history(&info, "history foo foo");
    cr_assert_eq(my_history(arr, &info), 1);
}
