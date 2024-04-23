/*
** EPITECH PROJECT, 2024
** 42sh - Sam
** File description:
** test_globbing_fcts
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/mysh.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_globbing, glob_standart, .init = redirect_all_std)
{
    char *args[] =  {"glob", "coucou", NULL};
    my_globbing(args, NULL);
    cr_assert_stdout_eq_str("coucou");
}

Test(my_globbing, glob_backslashes_2, .init = redirect_all_std)
{
    char *args[] = {"glob", "\\n\\t\\r\\b\\a\\v\\f\\0", NULL};

    my_globbing(args, NULL);
    cr_assert_stdout_eq_str("ntrbavf0");
}

Test(my_globbing, glob_escape_sequences_1, .init = redirect_all_std)
{
    char *args[] = {"glob", "\\\n\\\t\\\r\\\b\\\a\\\v\\\f\\\0", NULL};
    my_globbing(args, NULL);
    cr_assert_stdout_eq_str("\n\t\r\b\a\v\f\0");
}

Test(my_globbing, glob_escape_sequences_2, .init = redirect_all_std)
{
    char *args[] = {"glob", "\\\\p", NULL};
    my_globbing(args, NULL);
    cr_assert_stdout_eq_str("\\p");
}

Test(my_globbing, glob_escape_sequences_3, .init = redirect_all_std)
{
    char *args[] = {"glob", "\\\v", NULL};
    my_globbing(args, NULL);
    cr_assert_stdout_eq_str("\v");
}

Test(my_globbing, glob_escape_sequences_4, .init = redirect_all_std)
{
    char *args[] = {"glob", NULL};
    my_globbing(args, NULL);
    cr_assert_stdout_eq_str("");
}

