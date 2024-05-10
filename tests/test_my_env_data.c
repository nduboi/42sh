/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_env_data.c
*/

#include "mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(count_len_name_env, simple_env_variable, .init=redirect_all_std)
{
    char *data = "${VAR}";
    int result = count_len_name_env(data);
    cr_assert_eq(result, 6);
}

Test(count_len_name_env, env_variable_with_special_characters, .init=redirect_all_std)
{
    char *data = "${VAR123_456}";
    int result = count_len_name_env(data);
    cr_assert_eq(result, 13);
}

Test(get_value_env_with_brakets, simple_env_variable, .init=redirect_all_std)
{
    char *data = "${VAR}";
    char *result = get_value_env_with_brakets(data);
    cr_assert_str_eq(result, "${VAR");
    free(result);
}

Test(get_value_env, simple_env_variable, .init=redirect_all_std)
{
    char *data = "VAR";
    char *result = get_value_env(data);
    cr_assert_str_eq(result, "VAR");
    free(result);
}

Test(get_value_env, complex_env_variable, .init=redirect_all_std)
{
    char *data = "VAR_12_?";
    char *result = get_value_env(data);
    cr_assert_str_eq(result, "VAR_12_?");
    free(result);
}

Test(get_value_env, wrong_env_variable, .init=redirect_all_std)
{
    char *data = "-";
    char *result = get_value_env(data);
    cr_assert_str_eq(result, "");
    free(result);
}

Test(count_len_before_env, before_env_variable, .init=redirect_all_std)
{
    char *src = "before${VAR}";
    int result = count_len_before_env(src);
    cr_assert_eq(result, 6);
}

Test(count_len_before_env, no_dollar, .init=redirect_all_std)
{
    char *src = "lmao there's nothing";
    int result = count_len_before_env(src);
    cr_assert_eq(result, 0);
}

Test(count_len_after_env, after_env_variable, .init=redirect_all_std)
{
    char *data = "${VAR}after";
    int k = 0;
    int result = count_len_after_env(k, data);
    cr_assert_eq(result, 5);
}

Test(count_len_after_env, after_env_variable_return, .init=redirect_all_std)
{
    char *data = "";
    int k = 0;
    int result = count_len_after_env(k, data);
    cr_assert_eq(result, 1);
}

Test(count_len_after_env, after_env_variable_no_end, .init=redirect_all_std)
{
    char *data = "${VAR";
    int k = 0;
    int result = count_len_after_env(k, data);
    cr_assert_eq(result, 5);
}
