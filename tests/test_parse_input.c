/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_parse_input
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parse_input, add_group, .init=redirect_all_std)
{
    list_t *list_parse = NULL;
    infos_t *infos = malloc(sizeof(infos_t));
    infos->alias = NULL;
    char *input = "(ls)";

    int result = parse_input(input, &list_parse, infos);

    cr_assert_eq(result, 4);
    cr_assert_not_null(list_parse);
    cr_assert_not_null(list_parse->data);
    cr_assert_eq(((parsing_t *)(list_parse->data))->type, GRP);

    free(infos);
}

Test(parse_input, try_add_node_no_input, .init=redirect_all_std)
{
    list_t *list_parse = NULL;
    infos_t *infos = malloc(sizeof(infos_t));
    infos->alias = NULL;
    char *input = "";

    int result = parse_input(input, &list_parse, infos);

    cr_assert_eq(result, 0);

    free(infos);
}

Test(parse_input, try_add_node_with_delim, .init=redirect_all_std)
{
    list_t *list_parse = NULL;
    infos_t *infos = malloc(sizeof(infos_t));
    infos->alias = NULL;
    char *input = ";";

    int result = parse_input(input, &list_parse, infos);

    cr_assert_eq(result, 1);
    cr_assert_not_null(list_parse);
    cr_assert_not_null(list_parse->data);
    cr_assert_eq(((parsing_t *)(list_parse->data))->type, CMD);
    cr_assert_eq(((parsing_t *)(list_parse->data))->link, SC);

    free(infos);
}
