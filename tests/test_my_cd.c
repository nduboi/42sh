/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_cd
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>

Test(my_cd, too_many_args)
{
    char *args[4] = {"cd", "foo", "foo", NULL};
    
    cr_assert_eq(my_cd(args, NULL), -1);
}

Test(my_cd, home_path)
{
    char *args[2] = {"cd", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home";
    add_node(infos.envs->env, &data);
    my_cd(args, &infos);
    cr_assert_str_eq(getcwd(NULL, 0), "/home");
}

Test(my_cd, home_path_with_tilde)
{
    char *args[3] = {"cd", "~", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    data.name = "HOME";
    data.val = "/home";
    add_node(infos.envs->env, &data);
    my_cd(args, &infos);
    cr_assert_str_eq(getcwd(NULL, 0), "/home");
}

Test(my_cd, oldpwd)
{
    char *args[3] = {"cd", "-", NULL};
    infos_t infos;
    char *cwd = getcwd(NULL, 0);

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    my_cd(args, &infos);
    cr_assert_str_eq(getcwd(NULL, 0), cwd);
}

Test(my_cd, normal_cd)
{
    char *args[3] = {"cd", "/home", NULL};
    infos_t infos;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    my_cd(args, &infos);
    cr_assert_str_eq(getcwd(NULL, 0), "/home");
}

Test(my_cd, bad_dir)
{
    char *args[3] = {"cd", "/foo", NULL};
    infos_t infos;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    cr_assert_eq(my_cd(args, &infos), -1);
}

Test(my_cd, home_not_in_first_env)
{
    char *args[3] = {"cd", "~", NULL};
    infos_t infos;
    var_t data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    infos.envs->env_cpy = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    *infos.envs->env_cpy = NULL;
    data.name = "HOME";
    data.val = "/home";
    add_node(infos.envs->env_cpy, &data);
    my_cd(args, &infos);
    cr_assert_str_eq(getcwd(NULL, 0), "/home");
}

Test(my_cd, home_not_in_env)
{
    char *args[3] = {"cd", "~", NULL};
    infos_t infos;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    infos.envs->env_cpy = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    *infos.envs->env_cpy = NULL;
    cr_assert_eq(my_cd(args, &infos), -1);
}

Test(my_cd, home_far_in_env)
{
    char *args[3] = {"cd", "~", NULL};
    infos_t infos;
    var_t data;
    var_t blank_data;

    infos.envs = malloc(sizeof(env_t));
    infos.envs->env = malloc(sizeof(list_t *));
    *infos.envs->env = NULL;
    blank_data.name = "Foo";
    blank_data.val = "bar";
    add_node(infos.envs->env, &blank_data);
    data.name = "HOME";
    data.val = "/home";
    add_node(infos.envs->env, &data);
    my_cd(args, &infos);
    cr_assert_str_eq(getcwd(NULL, 0), "/home");
}
