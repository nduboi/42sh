/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_parsing_errors.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(null_cmd, empty_cmd, .init=redirect_all_std)
{
    parsing_t *cmd = malloc(sizeof(parsing_t));
    cmd->type = CMD;
    cmd->content.cmd = "   ";

    bool result = null_cmd(cmd);

    cr_assert_eq(result, false);

    free(cmd);
}

Test(null_cmd, non_empty_cmd, .init=redirect_all_std)
{
    parsing_t *cmd = malloc(sizeof(parsing_t));
    cmd->type = CMD;
    cmd->content.cmd = "ls";

    bool result = null_cmd(cmd);

    cr_assert_eq(result, false);

    free(cmd);
}

Test(null_cmd, empty_grp_list, .init=redirect_all_std)
{
    list_t *grp_list = NULL;

    parsing_t *grp = malloc(sizeof(parsing_t));
    grp->type = GRP;
    grp->content.grp = &grp_list;

    bool result = null_cmd(grp);

    cr_assert_eq(result, false);

    free(grp);
}

Test(null_cmd, non_empty_grp_list, .init=redirect_all_std)
{
    parsing_t *cmd = malloc(sizeof(parsing_t));
    cmd->type = CMD;
    cmd->content.cmd = "ls";

    list_t *cmd_list = malloc(sizeof(list_t));
    cmd_list->data = cmd;
    cmd_list->next = NULL;

    parsing_t *grp = malloc(sizeof(parsing_t));
    grp->type = GRP;
    grp->content.grp = &cmd_list;

    bool result = null_cmd(grp);
    cr_assert_eq(result, false);

    free(cmd);
    free(cmd_list);
    free(grp);
}

Test(ambiguous_redir, input_redirect, .init=redirect_all_std)
{
    parsing_t *cmd = malloc(sizeof(parsing_t));
    bool result;

    cmd->type = CMD;
    cmd->content.cmd = "ls";
    cmd->link = NONE_LINK;
    cmd->bt = false;
    cmd->redirs.in = true;
    cmd->redirs.d_in = false;
    cmd->redirs.out = false;
    cmd->redirs.d_out = false;
    result = ambiguous_redir(cmd);

    cr_assert_eq(result, false);
    free(cmd);
}

Test(null_cmd, check_AND_link_not_empty_str, .init=redirect_all_std)
{
    parsing_t *cmd = malloc(sizeof(parsing_t));
    cmd->type = CMD;
    cmd->content.cmd = "ls";
    cmd->link = AND;
    cmd->bt = false;

    bool result = null_cmd(cmd);

    cr_assert_eq(result, false);

    free(cmd);
}

Test(ambiguous_redir, was_pipe_out_output_redirect, .init=redirect_all_std)
{
    parsing_t *cmd = malloc(sizeof(parsing_t));
    cmd->type = CMD;
    cmd->content.cmd = "ls";
    cmd->link = PIPE;
    cmd->bt = false;
    cmd->redirs.in = false;
    cmd->redirs.d_in = false;
    cmd->redirs.out = true;
    cmd->redirs.d_out = false;

    bool result = ambiguous_redir(cmd);

    cr_assert_eq(result, true);

    free(cmd);
}

Test(parse_input, handle_append_redirection)
{
    infos_t *infos = malloc(sizeof(infos_t));
    list_t *list = NULL;

    char *input = strdup("echo hello >> file.txt");
    int res = parse_input(input, &list, infos);
    cr_assert_eq(res, 22, "Expected 22, got %d", res);
    cr_assert_eq(((parsing_t *)list->data)->redirs.d_out, true, "Expected true, got false");
    cr_assert_str_eq(((parsing_t *)list->data)->redirs.keyword_d_out, "file.txt", "Expected 'file.txt', got %s", ((parsing_t *)list->data)->redirs.keyword_d_out);
}

Test(parse_input, handle_double_input_redirection)
{
    infos_t *infos = malloc(sizeof(infos_t));
    list_t *list = NULL;

    char *input = strdup("cat << EOF");
    int res = parse_input(input, &list, infos);
    cr_assert_eq(res, 10, "Expected 10, got %d", res);
    cr_assert_eq(((parsing_t *)list->data)->redirs.d_in, true, "Expected true, got false");
}

Test(parse_input, handle_output_redirection)
{
    infos_t *infos = malloc(sizeof(infos_t));
    list_t *list = NULL;
    char *input = "ls > file.txt";
    int res = parse_input(input, &list, infos);
    cr_assert_eq(res, 13, "Expected 13, got %d", res);
    cr_assert_eq(((parsing_t *)list->data)->redirs.out, true, "Expected true, got false");
    cr_assert_str_eq(((parsing_t *)list->data)->redirs.keyword_out, "file.txt", "Expected 'file.txt', got %s", ((parsing_t *)list->data)->redirs.keyword_out);
}

Test(parse_input, test_malformed_input_with_redirections)
{
    list_t *list = NULL;
    infos_t *infos = malloc(sizeof(infos_t));
    int ret = parse_input("ls > ; cat < file.txt ; echo test >> file.txt", &list, infos);

    cr_assert_null(list, "Expected NULL list");
    cr_assert_eq(ret, -1, "Expected return value to be -1");
}

Test(parse_input, test_malformed_input_ambiguous_output_redirect)
{
    list_t *list = NULL;
    infos_t *infos = malloc(sizeof(infos_t));
    int ret = parse_input("ls > file.txt > other_file.txt", &list, infos);

    cr_assert_null(list, "Expected NULL list");
    cr_assert_eq(ret, -1, "Expected return value to be -1");
}

Test(parse_input, test_malformed_input_ambiguous_input_redirect)
{
    list_t *list = NULL;
    infos_t *infos = malloc(sizeof(infos_t));
    int ret = parse_input("cat < file.txt < other_file.txt", &list, infos);

    cr_assert_null(list, "Expected NULL list");
    cr_assert_eq(ret, -1, "Expected return value to be -1");
}
