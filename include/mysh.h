/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** mysh
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>
#include "struct.h"
#include <termios.h>

#ifndef MYSH_H_
    #define MYSH_H_

    #define WRITE_STATUS 1
    #define GET_STATUS 2
    #define SIZE_TAB 15

    #define CHAR sizeof(char)

extern function_t functions[];

// string and numerical functions
void my_strsignal(int wstatus);
char **str_to_word_array(char *buffer);
char *my_strcpy(char *dest, char *src);
char *my_strdup(char *src);
char *my_strcat(char *dest, char *src);
int my_arrlen(char **arr);
int my_strlen(char *str);
int my_strcmp(char *s1, char *s2);
int my_getnbr(char *str);
int my_nbrlen(int nbr);
void my_putnbr(int nbr);
char *my_strstr(char *hay, char *needle);
bool only_char_in_str(char *str, char c);

// my shell functions
int my_sh(char **env);
int handle_input(char *input, infos_t *infos);
int execute_commands(list_t **list_parse, infos_t *infos);
int handle_cmd(char *input, infos_t *infos);
int exe_cmd(char **args, infos_t *infos);
void error_message(char *str, int errnum);
void handle_signal(int wstatus);
int handle_exit_status(int action, int nbr);
void restart_fds(int in, int out);

// parsing
int parse_input(char *input, list_t **list_parse, infos_t *infos);
bool too_many_parenthesis(char *cmd);
int add_backtick(char **input_ptr, parsing_t *node, infos_t *infos);
int add_redir(char **input_ptr, redirs_t *red);
int handle_redirections(parsing_t *data, infos_t *infos);
bool null_cmd(parsing_t *data);
bool ambiguous_redir(parsing_t *data);
int handle_globbings(char **cmd);

// chained list functions
void add_node(list_t **begin, void *data);
void delete_node(list_t *node, list_t *last, list_t **list);
char **chained_list_to_normal(list_t **begin);
int chained_list_size(list_t **begin);
list_t *find_node(list_t **env, char *name);

// builtins
int my_cd(char **args, infos_t *infos);
int my_env(char **args, infos_t *infos);
int my_echo(char **args, infos_t *infos);
int my_exit(char **args, infos_t *infos);
int my_setenv(char **args, infos_t *infos);
int my_unsetenv(char **args, infos_t *infos);
int my_alias(char **args, infos_t *infos);
void display_alias(char **args, infos_t *infos);
int add_alias(char **args, infos_t *infos);
void display_all_alias(infos_t *infos);
int my_unalias(char **args, infos_t *infos);
int my_jobs(char **args, infos_t *info);
int my_globbing(char **args, infos_t *infos);
int my_fg(char **args, infos_t *info);
int my_set(char **args, infos_t *infos);
int my_unset(char **av, infos_t *infos);
int my_bg(char **args, infos_t *info);
char check_temp(jobs_t *temp);

// tools
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
void *my_memset(void *ptr, int val, size_t len);
void free_double_array(char **array);
void free_chained_list(list_t **begin);
void free_infos(infos_t *infos);
int count_char_in_str(char *str, char c);
char *my_strcat_s(char *str1, char *str2);
void delete_char(char *str, char c);
char *my_stock_nbr(int nb);
void add_a_job(char *path, char **args, int pid, infos_t *infos);
int my_get_nbr_lambda(char *str);
bool is_delim(char *str);
char *insert_spaces(char *str);
char *arr_to_str(char **args);
char *insert_in_str(char *word, char *str, int start);
char *remove_in_str(char *str, int ind);
int is_alpha(char c);
int is_num(char c);
void update_exit(infos_t *infos);

// Custom prompt
void write_prompt(env_t *env);
char *get_env_var(char *key, list_t **env);

// history
void add_history(infos_t *info, char *line);
int my_history(char **args, infos_t *info);
void free_history(history_t *h);
char *check_exclamation(char *input, infos_t *info);
char *recall_by_id(int id, infos_t *infos);
char **check_if_is_an_alias(char **args, infos_t *infos);

// Environement var
int parse_input_env_var(char **data, infos_t *info);
int count_len_name_env(char *data);
char *get_value_env_with_brakets(char *data);
char *get_value_env(char *data);
int count_len_before_env(char *src);
int count_len_after_env(int k, char *data);
void cut_in_part(char *data, char **part1, char **part2);
void cut_in_part_brakets(char *data, char **part1, char **part2);

// Local var
char *parse_input_local_var(char *input, infos_t *infos);

// Line edition

char *getline_modif(infos_t *list, int *len);
bool handle_arrow(char ch, int **data_arrow, char *strings,
    infos_t *list);

#endif /* !MYSH_H_ */
