/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_echo
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}


Test(error_in_variables, null_error_case, .init=redirect_all_std)
{
    int ret = error_in_variables("");
    cr_assert_eq(false, ret);
}

Test(error_in_variables, error_case, .init=redirect_all_std)
{
    int ret = error_in_variables("$echooooooooo");
    cr_assert_eq(false, ret);
}

Test(error_in_variables, brackets_error_case, .init=redirect_all_std)
{
    int ret = error_in_variables("${echooooooooo}");
    cr_assert_eq(false, ret);
}

Test(error_in_variables, not_ending_brackets_error_case, .init=redirect_all_std)
{
    int ret = error_in_variables("${echooooooooo");
    cr_assert_eq(true, ret);
}



Test(quotes_errors, unmatched, .init=redirect_all_std)
{
    int ret = quotes_errors("\"coucoulezami");
    cr_assert_eq(true, ret);
}

Test(quotes_errors, matched, .init=redirect_all_std)
{
    int ret = quotes_errors("\"coucoulezami\"");
    cr_assert_eq(false, ret);
}

Test(quotes_errors, unmatched_end, .init=redirect_all_std)
{
    int ret = quotes_errors("coucoulezami\"");
    cr_assert_eq(true, ret);
}


Test(parse_input_env_var, test_parse_input_env_var)
{
    infos_t *info = malloc(sizeof(infos_t));
    cr_assert_not_null(info);
    char *data = my_strdup("GROUP=samuelgiret");
    int result = parse_input_env_var(&data, info);
    cr_assert_eq(result, 0);
    free(info);
    free(data);
}

Test(check_if_is_an_alias, test_check_if_is_an_alias_no_alias)
{
    infos_t *infos = malloc(sizeof(infos_t));
    cr_assert_not_null(infos);
    infos->alias = NULL;
    char *args[] = {"echo", "-n", "hello", NULL};
    char **result = check_if_is_an_alias(args, infos);
    cr_assert_str_eq(result[0], "echo");
    free(infos);
}

Test(check_if_is_an_alias, test_check_if_is_an_alias_with_alias)
{
    infos_t *infos = malloc(sizeof(infos_t));
    cr_assert_not_null(infos);
    alias_t *alias = malloc(sizeof(alias_t));
    cr_assert_not_null(alias);
    alias->base_command = my_strdup("ls");
    alias->new_command = my_strdup("ls -l");
    alias->next = NULL;
    infos->alias = alias;
    char *args[] = {"ls", NULL};
    char **result = check_if_is_an_alias(args, infos);
    cr_assert_str_eq(result[0], "ls");
    free(infos->alias->base_command);
    free(infos->alias->new_command);
    free(infos->alias);
    free(infos);
}
