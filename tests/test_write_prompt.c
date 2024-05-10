/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_write_prompt.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(write_prompt_without_env, test_write_prompt_without_env)
{
    cr_redirect_stdout();
    write_prompt_without_env();
    cr_expect_stdout_neq_str("\033[31m[user@hostname pwd]$ \033[0m");
}
