/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_error_messages
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <errno.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(error_message, try_bad_chdir, .init=redirect_all_std)
{
    chdir("dfsjgpsg");
    error_message("dfsjgpsg", errno);
    cr_assert_stderr_eq_str("dfsjgpsg: No such file or directory.\n");
}
