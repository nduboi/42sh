/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_parse_input
*/

#include "mysh.h"
#include <criterion/criterion.h>

// Test(parse_input, parse_a_simple_cmd)
// {
//     char *cmd = my_strdup("ls");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_str_eq(parsing->content.command, "ls");
// }

// Test(parse_input, parse_a_piped_cmd)
// {
//     char *cmd = my_strdup("ls | cat");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_str_eq(parsing->content.command, "ls ");
//     cr_assert_eq(parsing->link, PIPE);
// }

// Test(parse_input, parse_a_or_cmd)
// {
//     char *cmd = my_strdup("ls || echo foo");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_str_eq(parsing->content.command, "ls ");
//     cr_assert_eq(parsing->link, OR);
// }

// Test(parse_input, parse_an_and_cmd)
// {
//     char *cmd = my_strdup("ls && echo bar");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_str_eq(parsing->content.command, "ls ");
//     cr_assert_eq(parsing->link, AND);
// }

// Test(parse_input, parse_a_semi_colon_cmd)
// {
//     char *cmd = my_strdup("ls ; echo bar");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_str_eq(parsing->content.command, "ls ");
//     cr_assert_eq(parsing->link, SC);
// }

// Test(parse_input, parse_a_cmd_with_parentheses)
// {
//     char *cmd = my_strdup("(echo bar)");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_eq(parsing->type, GRP);
// }

// Test(parse_input, parse_a_cmd_with_parentheses_and_pipe)
// {
//     char *cmd = my_strdup("(echo bar) | ls");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_eq(parsing->type, GRP);
// }

// Test(parse_input, parse_a_cmd_with_parentheses_and_or)
// {
//     char *cmd = my_strdup("(echo bar) || ls");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_eq(parsing->link, OR);
// }

// Test(parse_input, parse_a_cmd_with_parentheses_and_and)
// {
//     char *cmd = my_strdup("(echo bar) && ls");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_eq(parsing->link, AND);
// }

// Test(parse_input, parse_a_cmd_with_parentheses_and_sc)
// {
//     char *cmd = my_strdup("(echo bar) ; ls");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_eq(parsing->link, SC);
// }

// Test(parse_input, parse_a_simple_cmd_with_single_and)
// {
//     char *cmd = my_strdup("ls &");
//     list_t **list = malloc(sizeof(list_t *));
//     parsing_t *parsing;

//     *list = NULL;
//     parse_input(cmd, list);
//     parsing = (*list)->data;
//     cr_assert_str_eq(parsing->content.command, "ls &");
// }
