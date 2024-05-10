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

Test(my_set, test_set_change_node)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos->vars = malloc(sizeof(local_var_t));
    infos->vars->var = strdup("VAR");
    infos->vars->val = strdup("VALUE");
    infos->vars->next = NULL;
    int ret = change_node("VAR", "NEW_VALUE", infos);
    cr_assert_eq(ret, 1, "Expected return value to be 1");
    cr_assert_str_eq(infos->vars->val, "NEW_VALUE", "Expected value to be 'NEW_VALUE'");
    free(infos->vars->var);
    free(infos->vars->val);
    free(infos->vars);
    free(infos);
}

Test(error_cases_local, test_error_cases_local_numeric_beginning)
{
    cr_redirect_stderr();
    int ret = error_cases_local("123VAR");
    cr_assert_eq(ret, 1, "Expected return value to be 1");
    cr_assert_stderr_eq_str("set: Variable name must begin with a letter.\n",
        "Expected error message not found");
}

Test(error_cases_local, test_error_cases_local_invalid_characters)
{
    cr_redirect_stderr();
    int ret = error_cases_local("VAR@#");
    cr_assert_eq(ret, 1, "Expected return value to be 1");
    cr_assert_stderr_eq_str(
        "set: Variable name must contain alphanumeric characters.\n",
        "Expected error message not found");
}

Test(error_cases_local, test_error_cases_local_valid_name)
{
    int ret = error_cases_local("VAR123");
    cr_assert_eq(ret, 0, "Expected return value to be 0");
}

Test(add_node_var, test_add_node_var)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos->vars = NULL;

    add_node_var("VAR", "value", infos);

    local_var_t *current = infos->vars;
    bool found = false;
    while (current != NULL) {
        if (strcmp(current->var, "VAR") == 0 && strcmp(current->val, "value") == 0) {
            found = true;
            break;
        }
        current = current->next;
    }

    cr_assert(found, "Expected variable 'VAR' to be added with value 'value'");

    free(infos->vars->var);
    free(infos->vars->val);
    free(infos->vars);
    free(infos);
}

Test(my_unset, test_unset, .init=redirect_all_std)
{
    infos_t *infos = malloc(sizeof(infos_t));

    infos->vars = NULL;
    add_node_var("VAR1", "value1", infos);
    add_node_var("VAR2", "value2", infos);
    add_node_var("VAR3", "value3", infos);
    my_unset((char *[]){"unset", "VAR1", "VAR3", NULL}, infos);
    cr_assert_not_null(infos->vars, "Expected variables to be removed");
    free(infos);
}
