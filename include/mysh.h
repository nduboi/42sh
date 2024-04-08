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

#ifndef MYSH_H_
    #define MYSH_H_

    #define WRITE_STATUS 1
    #define GET_STATUS 2

typedef struct var_s {
    char *name;
    char *val;
} var_t;

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

typedef struct env_s {
    list_t **env;
    list_t **env_cpy;
} env_t;

typedef struct commands_s {
    list_t **semi_colons;
} commands_t;

typedef struct history_s {
    int id;
    char *hour;
    char *line;
    struct history_s *next;
} history_t;

typedef struct infos_s {
    env_t *envs;
    bool isatty;
    history_t *history;
} infos_t;

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
int count_tokens(char *str, char *sep);
char *my_strstr(char *hay, char *needle);

// my shell functions
int my_sh(char **env);
void parse_input(char *input, infos_t *infos);
bool errors_in_cmd(char *cmd);
void handle_cmd(char *input, infos_t *infos);
int exe_cmd(char **args, infos_t *infos);
void error_message(char *str, int errnum);
void handle_signal(int wstatus);
int handle_exit_status(int action, int nbr);
void handle_redirections(char *input, infos_t *infos);
void restart_fds(int in, int out);

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

// tools
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
void *my_memset(void *ptr, int val, size_t len);
void free_double_array(char **array);
void free_chained_list(list_t **begin);
void free_infos(infos_t *infos);

// history
void add_history(infos_t *info, char *line);
int my_history(char **args, infos_t *info);

#endif /* !MYSH_H_ */
