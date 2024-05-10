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

Test(handle_redirections, test_redirection_missing_input_file)
{
    parsing_t *data = malloc(sizeof(parsing_t));
    infos_t *infos = malloc(sizeof(infos_t));
    data->type = CMD;
    data->link = END;
    data->content.cmd = "ls";
    data->redirs.in = true;
    data->redirs.out = false;
    data->redirs.d_in = false;
    data->redirs.d_out = false;
    data->redirs.keyword_in = "missing_file.txt";
    int ret = handle_redirections(data, infos);
    cr_assert_eq(ret, 1, "Expected return value to be 1");
}
