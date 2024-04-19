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

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

enum type_e {
    CMD = 0,
    GRP
};

enum link_e {
    SC = 0,
    AND,
    OR,
    PIPE,
    END
};

union content_u {
    list_t **group;
    char *command;
};

typedef struct parsing_s {
    enum type_e type;
    union content_u content;
    enum link_e link;
} parsing_t;

typedef struct var_s {
    char *name;
    char *val;
} var_t;

typedef struct alias_s {
    char *base_command;
    char *new_command;
    struct alias_s *next;
} alias_t;

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
    alias_t *alias;
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
bool only_char_in_str(char *str, char c);

// my shell functions
int my_sh(char **env);
void handle_input(char *input, infos_t *infos);
int parse_input(char *input, list_t **list_parse);
void execute_commands(list_t **list_parse, infos_t *infos);
bool errors_in_input(char *str);
bool errors_in_pipes_and_redirs(char *cmd);
void handle_cmd(char *input, infos_t *infos);
int exe_cmd(char **args, infos_t *infos);
void error_message(char *str, int errnum);
void handle_signal(int wstatus);
int handle_exit_status(int action, int nbr);
void handle_redirections(char *input, infos_t *infos);
bool ambigous_redirect(char *src);
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
int my_alias(char **args, infos_t *infos);
void display_alias(char **args, infos_t *infos);
void add_alias(char **args, infos_t *infos);
void display_all_alias(infos_t *infos);
int my_unalias(char **args, infos_t *infos);

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

// Custom prompt

void write_prompt(env_t *env);
char *get_env_var(char *key, list_t **env);

// history
void add_history(infos_t *info, char *line);
int my_history(char **args, infos_t *info);
void free_history(history_t *h);
char *check_exclamation(char *input, infos_t *info);

char **check_if_is_an_alias(char **args, infos_t *infos);

#endif /* !MYSH_H_ */
