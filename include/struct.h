/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct local_var_s {
    char *var;
    char *val;
    struct local_var_s *next;
} local_var_t;

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

enum type_e {
    NONE_TYPE = 0,
    CMD,
    GRP
};

enum link_e {
    NONE_LINK = 0,
    SC,
    AND,
    OR,
    PIPE,
    END
};

typedef struct redirs_s {
    bool in;
    bool out;
    bool d_in;
    bool d_out;
    char *keyword_in;
    char *keyword_out;
    char *keyword_d_in;
    char *keyword_d_out;
} redirs_t;

union content_u {
    list_t **grp;
    char *cmd;
};

typedef struct parsing_s {
    enum type_e type;
    union content_u content;
    enum link_e link;
    char **bt;
    redirs_t redirs;
} parsing_t;

typedef struct jobs_s {
    int pid;
    char *wd;
    char *command;
    int num;
    struct jobs_s *next;
} jobs_t;

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
    jobs_t *jobs;
    local_var_t *vars;
    int can_exit_job;
} infos_t;

typedef struct function_s {
    char *name;
    int (*function)(char **, infos_t *);
} function_t;

#endif /* !STRUCT_H_ */
