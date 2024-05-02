/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_recall_by_id
*/

#include <criterion/criterion.h>
#include "mysh.h"

Test(recall_by_id, existing)
{
    infos_t info;

    info.history = NULL;
    add_history(&info, "ls -l");
    add_history(&info, "pwd");
    add_history(&info, "ls");
    add_history(&info, "echo oui");
    add_history(&info, "ls -la");
    cr_assert_str_eq(recall_by_id(2, &info), "ls");
}

Test(recall_by_id, negative)
{
    infos_t info;

    info.history = NULL;
    add_history(&info, "ls -l");
    add_history(&info, "pwd");
    add_history(&info, "ls");
    add_history(&info, "echo oui");
    add_history(&info, "ls -la");
    cr_assert_eq(recall_by_id(-5, &info), NULL);
}

Test(recall_by_id, bigger)
{
    infos_t info;

    info.history = NULL;
    add_history(&info, "ls -l");
    add_history(&info, "pwd");
    add_history(&info, "ls");
    add_history(&info, "echo oui");
    add_history(&info, "ls -la");
    cr_assert_eq(recall_by_id(15, &info), NULL);
}
