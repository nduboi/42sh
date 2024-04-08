/*
** EPITECH PROJECT, 2024
** alban
** File description:
** test_chained_lists
*/

#include <criterion/criterion.h>
#include "../include/mysh.h"

Test(add_node, adding_node_in_chained_list)
{
    list_t *tail = NULL;
    list_t **begin = malloc(sizeof(list_t *));
    var_t *data = NULL;

    *begin = NULL;
    add_node(begin, data);
    cr_assert_eq((*begin)->data, data);
    cr_assert_eq((*begin)->next, tail);
}

Test(delete_node, deleting_node_in_beginning_of_chained_list)
{
    list_t *tail = NULL;
    list_t **begin = malloc(sizeof(list_t *));
    var_t *data = NULL;

    *begin = NULL;
    add_node(begin, data);
    delete_node(*begin, NULL, begin);
    cr_assert_eq(*begin, tail);
}

Test(delete_node, deleting_node_in_middle_of_chained_list)
{
    list_t *tail = NULL;
    list_t **begin = malloc(sizeof(list_t *));
    var_t *data = NULL;

    *begin = NULL;
    add_node(begin, data);
    add_node(begin, data);
    delete_node((*begin)->next, *begin, begin);
    cr_assert_eq((*begin)->next, tail);
}

Test(chained_list_size, get_size_of_list)
{
    list_t **begin = malloc(sizeof(list_t *));
    var_t *data = NULL;

    *begin = NULL;
    add_node(begin, data);
    add_node(begin, data);
    cr_assert_eq(2, chained_list_size(begin));
}

Test(chained_list_to_normal, transform_chained_list_to_list)
{
    list_t **begin = malloc(sizeof(list_t *));
    var_t *data = malloc(sizeof(var_t));
    char **result;

    *begin = NULL;
    data->name = "Hello";
    data->val = "World";
    add_node(begin, data);
    result = chained_list_to_normal(begin);
    cr_assert_str_eq(result[0], "Hello=World");
}

Test(find_node, find_a_present_node)
{
    list_t **begin = malloc(sizeof(list_t *));
    list_t *node;
    var_t *data = malloc(sizeof(var_t));

    *begin = NULL;
    data->name = "Hello";
    data->val = "World";
    add_node(begin, data);
    node = find_node(begin, "Hello");
    cr_assert_eq(node, *begin);
}

Test(find_node, find_an_absent_node)
{
    list_t **begin = malloc(sizeof(list_t *));
    list_t *node;
    var_t *data = malloc(sizeof(var_t));

    *begin = NULL;
    data->name = "Hello";
    data->val = "World";
    add_node(begin, data);
    add_node(begin, data);
    node = find_node(begin, "Test");
    cr_assert_eq(node, NULL);
}
