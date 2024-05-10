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

Test(my_fg, test_fg_no_current_job)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos->jobs = NULL;
    cr_redirect_stderr();
    my_fg(NULL, infos);
    cr_assert_stderr_eq_str("fg: No current job\n", "Expected 'fg: No current job\\n'");
    free(infos);
}

Test(my_bg, test_bg_invalid_arg)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos->jobs = malloc(sizeof(jobs_t));
    infos->jobs->pid = 123;
    infos->jobs->wd = strdup("/test/path");
    infos->jobs->command = strdup("ls");
    infos->jobs->num = 1;
    infos->jobs->next = NULL;
    cr_redirect_stderr();
    my_bg((char *[3]){"bg", "test", NULL}, infos);
    cr_assert_stderr_eq_str("", "Expected ''");
    cr_assert_null(infos->jobs, "Job should be deleted");
    free(infos);
}
