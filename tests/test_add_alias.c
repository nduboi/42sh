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

Test(add_alias, test_alias_alias)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos->alias = NULL;
    char *args[] = {"alias", "alias", "something", NULL};
    int ret = add_alias(args, infos);
    cr_assert_eq(ret, 1, "Expected return value to be 1");
    cr_assert_null(infos->alias, "Alias list should be NULL");
}

Test(add_alias, test_alias_unalias)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos->alias = NULL;
    char *args[] = {"alias", "unalias", "something", NULL};
    int ret = add_alias(args, infos);
    cr_assert_eq(ret, 1, "Expected return value to be 1");
    cr_assert_null(infos->alias, "Alias list should be NULL");
}

Test(display_alias, test_display_alias_does_not_exist)
{
    infos_t *infos = malloc(sizeof(infos_t));
    alias_t *existing_alias = malloc(sizeof(alias_t));
    existing_alias->base_command = strdup("ls");
    existing_alias->new_command = strdup("ls --color=auto");
    existing_alias->next = NULL;
    infos->alias = existing_alias;
    char *args[] = {"alias", "cd", NULL};
    cr_redirect_stdout();
    display_alias(args, infos);
    cr_assert_stdout_eq_str("", "Expected empty string");
    free(existing_alias->base_command);
    free(existing_alias->new_command);
    free(existing_alias);
    free(infos);
}
