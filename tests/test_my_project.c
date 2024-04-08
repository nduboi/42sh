/*
** EPITECH PROJECT, 2023
** test_my_printf
** File description:
** Test file for my_printf
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell1.h"
#include "library.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(fill_struct, fill_struct1, .init = redirect_all_std)
{
    commands_t *commands = NULL;
    fill_struct(&commands);
    while (commands) {
        my_putstr(commands->name);
        my_putchar('\n');
        commands = commands->next;
    }
    cr_assert_stdout_eq_str("exit\nenv\nunsetenv\nsetenv\ncd\n");
}

Test(my_str_to_word_array, my_str_to_word_array1, .init = redirect_all_std)
{
    char *str = "ls -la /dev";
    char **data;

    data = my_str_to_word_array(str);
    for (int i = 0; data[i]; i++) {
        my_putstr(data[i]);
        my_putchar('\n');
    }
    cr_assert_stdout_eq_str("ls\n-la\n/dev\n");
}

Test(my_str_to_word_array, my_str_to_word_array2, .init = redirect_all_std)
{
    char *str = "l";
    char **data;

    data = my_str_to_word_array(str);
    for (int i = 0; data[i]; i++) {
        my_putstr(data[i]);
        my_putchar('\n');
    }
    cr_assert_stdout_eq_str("l\n");
}

Test(my_str_to_word_array_pwd, my_str_to_word_array_pwd1, .init = redirect_all_std)
{
    char *str = "/dev/bin:/home/noa";
    char **data;

    data = my_str_to_word_array_pwd(str);
    for (int i = 0; data[i]; i++) {
        my_putstr(data[i]);
        my_putchar('\n');
    }
    cr_assert_stdout_eq_str("/dev/bin\n/home/noa\n");
}

Test(my_str_to_word_array_pwd, my_str_to_word_array_pwd2, .init = redirect_all_std)
{
    char *str = "/";
    char **data;

    data = my_str_to_word_array_pwd(str);
    for (int i = 0; data[i]; i++) {
        my_putstr(data[i]);
        my_putchar('\n');
    }
    cr_assert_stdout_eq_str("/\n");
}

Test(check_correct_command, check_correct_command1, .init = redirect_all_std)
{
    commands_t *commands = NULL;
    fill_struct(&commands);
    int cmds = 0;
    char *data_ls[] = {"ls", NULL};
    char *data_cd[] = {"cd", NULL};
    char *data_nimp[] = {"fqfqfefq", NULL};
    char *data_env[] = {"env", NULL};
    char *data_setenv[] = {"setenv", NULL};
    char *data_unsetenv[] = {"unsetenv", NULL};
    char *data_NULL[] = {NULL};
    char **env = malloc(sizeof(char *) * 2);
    env[0] = my_strdup("PATH=/usr/bin");
    env[1] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);

    cmds = check_correct_command(data_ls, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(data_cd, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(data_nimp, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(data_env, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(data_setenv, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(data_unsetenv, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(NULL, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cmds = check_correct_command(data_NULL, commands, &env_variable, cpy_env);
    my_put_nbr(cmds);
    my_putchar('\n');
    cr_assert_stdout_eq_str("2\n1\n84\n1\n1\n1\n0\n0\n");
}

Test(main_env, main_env1, .init = redirect_all_std)
{
    char *av[] = {"env", NULL};
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char path[300];

    my_put_nbr(main_env(1, av, &env_variable, cpy_env));
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "coucou=noa\ntests=noa\nPWD="), path);
    strcat(final_str, "\n");
    strcat(final_str, "0");
    cr_assert_stdout_eq_str(final_str);
}

Test(main_env, main_env2, .init = redirect_all_std)
{
    char *av[] = {"encafv", NULL};
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char final[300];
    char path[300];

    getcwd(path, 300);
    my_put_nbr(main_env(1, av, &env_variable, cpy_env));
    strcat(strcpy(final, "coucou=noa\ntests=noa\nPWD="), path);
    strcat(final, "\n0");
    cr_assert_stdout_eq_str(final);
}

Test(main_env, main_env3, .init = redirect_all_std)
{
    char *av[] = {"encafv", NULL};
    char **env = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char path[300];
    char final[300];

    getcwd(path, 300);
    my_put_nbr(main_env(1, av, &env_variable, cpy_env));
    strcat(strcpy(final, "SHLVL=1\nPWD="), path);
    strcat(final, "\nHOST=");
    strcat(final, get_env("HOST", env_variable));
    strcat(final, "\n0");
    cr_assert_stdout_eq_str(final);
}

Test(main_setenv, main_setenv1, .init = redirect_all_std)
{
    char *av[] = {"setenv", "coucou", "ca va", NULL};
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char path[300];
    char final[300];

    getcwd(path, 300);
    my_put_nbr(main_setenv(3, av, &env_variable, cpy_env));
    print_env(env_variable);
    strcat(strcpy(final, "1coucou=noa\ntests=noa\nPWD="), path);
    strcat(final,"\n");
    cr_assert_stdout_eq_str(final);
}

Test(main_setenv, main_setenv2, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("setenv");
    av[1] = my_strdup("OLDPWD");
    av[2] = my_strdup("noa");
    av[4] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char final[300];
    char path[300];

    getcwd(path, 300);
    my_put_nbr(main_setenv(3, av, &env_variable, cpy_env));
    print_env(env_variable);
    strcat(strcpy(final, "0coucou=noa\ntests=noa\n"), "PWD=");
    strcat(final, path);
    strcat(final, "\nOLDPWD=noa\n");
    cr_assert_stdout_eq_str(final);
}

Test(main_setenv, main_setenv4, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 5);
    av[0] = my_strdup("setenv");
    av[1] = my_strdup("OLDPWD");
    av[2] = my_strdup("noa");
    av[3] = my_strdup("cace");
    av[4] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char final[300];
    char path[300];

    getcwd(path, 300);
    my_put_nbr(main_setenv(4, av, &env_variable, cpy_env));
    print_env(env_variable);
    strcat(strcpy(final, "1coucou=noa\ntests=noa\n"), "PWD=");
    strcat(final, path);
    strcat(final, "\n");
    cr_assert_stdout_eq_str(final);
}

Test(main_setenv, main_setenv5, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("setenvne");
    av[1] = my_strdup("OLDPWD");
    av[2] = my_strdup("noa");
    av[3] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char path[300];
    char final[300];

    getcwd(path, 300);
    my_put_nbr(main_setenv(3, av, &env_variable, cpy_env));
    print_env(env_variable);
    strcat(strcpy(final, "0coucou=noa\ntests=noa\n"), "PWD=");
    strcat(final, path);
    strcat(final, "\nOLDPWD=noa\n");
    cr_assert_stdout_eq_str(final);
}

Test(main_setenv, main_setenv6, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("setenv");
    av[1] = my_strdup("OLDPWD");
    av[2] = my_strdup("noa");
    av[3] = NULL;
    char **env = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char path[300];
    char final[300];

    getcwd(path, 300);
    my_put_nbr(main_setenv(3, av, &env_variable, cpy_env));
    print_env(env_variable);
    strcat(strcpy(final, "0SHLVL=1\nPWD="), path);
    strcat(final, "\nHOST=");
    strcat(final, get_env("HOST", env_variable));
    strcat(final, "\nOLDPWD=noa\n");
    cr_assert_stdout_eq_str(final);
}

Test(main_setenv, main_setenv7, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("setenvne");
    av[1] = NULL;
    av[2] = NULL;
    av[3] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);
    char final[300];
    char path[100];

    getcwd(path, 100);
    my_put_nbr(main_setenv(3, av, &env_variable, cpy_env));
    print_env(env_variable);
    strcat(strcpy(final, "1coucou=noa\ntests=noa\nPWD="), path);
    strcat(final, "\n");
    cr_assert_stdout_eq_str(final);
}


Test(get_line_env, get_line_env1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char *path = malloc(sizeof(char) * 100);

    my_put_nbr(get_line_env("azfbzbf", env_variable));
    print_env(env_variable);
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "-1coucou=noa\ntests=noa\nPWD="), path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(my_table_cpy, my_table_cpy1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char path[300];

    my_put_nbr(get_line_env("azfbzbf", env_variable));
    print_env(env_variable);
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "-1coucou=noa\ntests=noa\nPWD="), path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(my_table_cpy, my_table_cpy2, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("tests=noa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char path[300];

    my_put_nbr(get_line_env("azfbzbf", env_variable));
    print_env(env_variable);
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "-1coucou=noa\ntests=noa\nPWD="), path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(main_cd, main_cd1, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 2);
    av[0] = my_strdup("cd");
    av[1] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=tests");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char *buffer = malloc(sizeof(char) * 300);
    char *old_path = malloc(sizeof(char) * 300);
    char *path = malloc(sizeof(char) * 300);
    struct env_var *cpy_env = fill_environement(env);

    getcwd(old_path, 300);
    my_put_nbr(main_cd(my_array_len(av), av, &env_variable, cpy_env));
    getcwd(buffer, 300);
    if (my_strcmp(buffer, get_env("HOME", env_variable)))
        my_put_nbr(0);
    else
        my_put_nbr(1);
    print_env(env_variable);
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "00coucou=noa\nHOME=tests\nPWD="), path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(main_cd, main_cd2, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 3);
    av[0] = my_strdup("cd");
    av[1] = my_strdup("~");
    av[2] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=tests");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char *buffer = malloc(sizeof(char) * 300);
    char *old_path = malloc(sizeof(char) * 300);
    char *path = malloc(sizeof(char) * 300);
    struct env_var *cpy_env = fill_environement(env);

    getcwd(old_path, 300);
    my_put_nbr(main_cd(my_array_len(av), av, &env_variable, cpy_env));
    getcwd(buffer, 300);
    if (my_strcmp(buffer, get_env("HOME", env_variable)))
        my_put_nbr(0);
    else
        my_put_nbr(1);
    print_env(env_variable);
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "00coucou=noa\nHOME=tests\nPWD="), path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(main_cd, main_cd3, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 3);
    av[0] = my_strdup("cd");
    av[1] = my_strdup("-");
    av[2] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("1OLDPWD=tests");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char *buffer = malloc(sizeof(char) * 300);
    char *old_path = malloc(sizeof(char) * 300);
    char *now_path = malloc(sizeof(char) * 300);
    struct env_var *cpy_env = fill_environement(env);

    getcwd(old_path, 300);
    my_put_nbr(main_cd(my_array_len(av), av, &env_variable, cpy_env));
    getcwd(buffer, 300);
    if (my_strcmp(buffer, get_env("OLDPWD", env_variable)))
        my_put_nbr(0);
    else
        my_put_nbr(1);
    print_env(env_variable);
    char final_str[100];
    getcwd(now_path, 300);
    strcat(strcpy(final_str, "00coucou=noa\nPWD="), now_path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(main_cd, main_cd4, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 3);
    av[0] = my_strdup("cd");
    av[1] = my_strdup("tests");
    av[2] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=tests");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char *buffer = malloc(sizeof(char) * 300);
    char *old_path = malloc(sizeof(char) * 300);
    char *path = malloc(sizeof(char) * 300);
    struct env_var *cpy_env = fill_environement(env);

    getcwd(old_path, 300);
    my_put_nbr(main_cd(my_array_len(av), av, &env_variable, cpy_env));
    getcwd(buffer, 300);
    if (my_strcmp(buffer, "tests"))
        my_put_nbr(0);
    else
        my_put_nbr(1);
    print_env(env_variable);
    char final_str[100];
    getcwd(path, 300);
    strcat(strcpy(final_str, "00coucou=noa\nHOME=tests\nPWD="), path);
    strcat(final_str, "\n");
    cr_assert_stdout_eq_str(final_str);
}

Test(main_cd, main_cd5, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("cd");
    av[1] = my_strdup("tests");
    av[2] = my_strdup("bien");
    av[3] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=tests");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    struct env_var *cpy_env = fill_environement(env);

    my_put_nbr(main_cd(my_array_len(av), av, &env_variable, cpy_env));
    cr_assert_stdout_eq_str("1");
}

int specific_cases(char **av, char ***env);

Test(specific_cases, specific_cases1, .init = redirect_all_std)
{
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("cd");
    av[1] = my_strdup("tests");
    av[2] = my_strdup("bien");
    av[3] = NULL;
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=tests");
    env[2] = NULL;

    my_put_nbr(specific_cases(av, &env));
    cr_assert_stdout_eq_str("1");
}

char *replace_title_by_homedirectory(char *src, char *home);

Test(replace_title_by_homedirectory, replace_title_by_homedirectory1, .init = redirect_all_std)
{
    my_putstr(replace_title_by_homedirectory("~/my_script", "/home/roussierenoa"));
    cr_assert_stdout_eq_str("/home/roussierenoa/my_script");
}

char *replace_title_by_homedirectory(char *src, char *home);

Test(replace_title_by_homedirectory, replace_title_by_homedirectory2, .init = redirect_all_std)
{
    my_putstr(replace_title_by_homedirectory("NULL", NULL));
    cr_assert_stdout_eq_str("NULL");
}


char *check_for_home_dir(char *path, struct env_var *env_variable);

Test(check_for_home_dir, check_for_home_dir1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);

    my_putstr(check_for_home_dir("~/my_script", env_variable));
    cr_assert_stdout_eq_str("/home/roussierenoa/my_script");
}

Test(get_pwd_file, get_pwd_file1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);

    if (!(get_pwd_file(NULL, "nana", env_variable))) {
        my_put_nbr(0);
    } else {
        my_put_nbr(1);
    }
    cr_assert_stdout_eq_str("0");
}

Test(main_exit, main_exit1, .init = redirect_all_std, .exit_code = 0)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char **av = malloc(sizeof(char *) * 2);
    av[0] = my_strdup("exit");
    av[1] = NULL;
    struct env_var *cpy_env = fill_environement(env);

    main_exit(1, av, &env_variable, cpy_env);
    cr_assert_stdout_eq_str("");
}

Test(main_exit, main_exit3, .init = redirect_all_std, .exit_code = 34)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char **av = malloc(sizeof(char *) * 3);
    av[0] = my_strdup("exit");
    av[1] = my_strdup("34");
    av[2] = NULL;
    struct env_var *cpy_env = fill_environement(env);

    main_exit(2, av, &env_variable, cpy_env);
    cr_assert_stdout_eq_str("");
}

Test(main_unsetenv, main_unsetenv1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char **av = malloc(sizeof(char *) * 3);
    av[0] = my_strdup("unsetenv");
    av[1] = my_strdup("HOME");
    av[2] = NULL;
    struct env_var *cpy_env = fill_environement(env);
    char src[300];
    char path[300];

    getcwd(path, 300);
    main_unsetenv(2, av, &env_variable, cpy_env);
    print_env(env_variable);
    strcat(strcpy(src, "coucou=noa\nPWD="), path);
    strcat(src, "\n");
    cr_assert_stdout_eq_str(src);
}

Test(main_unsetenv, main_unsetenv2, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char **av = malloc(sizeof(char *) * 4);
    av[0] = my_strdup("unsetenv");
    av[1] = my_strdup("HOME");
    av[2] = my_strdup("coucou");
    av[3] = NULL;
    struct env_var *cpy_env = fill_environement(env);
    char final[300];
    char path[300];

    getcwd(path, 300);
    main_unsetenv(my_array_len(av), av, &env_variable, cpy_env);
    print_env(env_variable);
    strcat(strcpy(final, "PWD="), path);
    strcat(final, "\n");
    cr_assert_stdout_eq_str(final);
}

Test(main_unsetenv, main_unsetenv3, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 4);
    env[0] = my_strdup("coucou=noa");
    env[1] = my_strdup("HOME=/home/roussierenoa");
    env[2] = my_strdup("PWD=/home");
    env[3] = NULL;
    struct env_var *env_variable = fill_environement(env);
    char **av = malloc(sizeof(char *) * 3);
    av[0] = my_strdup("unsetenv");
    av[1] = my_strdup("neo");
    av[2] = NULL;
    struct env_var *cpy_env = fill_environement(env);
    char final[300];
    char path[300];

    getcwd(path, 300);
    main_unsetenv(my_array_len(av), av, &env_variable, cpy_env);
    print_env(env_variable);
    strcat(strcpy(final, "coucou=noa\nHOME=/home/roussierenoa\nPWD="), path);
    strcat(final, "\n");
    cr_assert_stdout_eq_str(final);
}
