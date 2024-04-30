/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parse_local_var
*/

#include "mysh.h"

static bool is_there_char(char *line, char c)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == c)
            return (true);
    }
    return (false);
}

char *get_local_val(char *var, infos_t *infos)
{
    local_var_t *tmp = infos->vars;

    while (tmp != NULL) {
        if (strcmp(var, tmp->var) == 0)
            return (strdup(tmp->val));
        tmp = tmp->next;
    }
    return (NULL);
}

char *get_curly_var(char *str, int i)
{
    char *var = NULL;
    int len = 0;
    int j = i + 1;

    if (!is_there_char(str, '}'))
        return (str);
    for (j = i + 1; str[j] != '\0' && str[j] != '}'; j++);
    len = j - (i + 1);
    if (len == 0)
        return (NULL);
    var = malloc(sizeof(char) * (len + 1));
    var[len] = '\0';
    for (int a = 0; a < len; a++) {
        var[a] = str[i + a + 1];
    }
    str = remove_in_str(str, i);
    str = remove_in_str(str, i);
    return (var);
}

char *get_var(char *str, int i)
{
    char *var = NULL;
    int len = 0;
    int j = i;

    if (str[i] == '{')
        return (get_curly_var(str, i));
    for (j = i; str[j] != '\0' && str[j] != ' ' && str[j] != '\t'; j++);
    len = j - i;
    if (len == 0)
        return (NULL);
    var = malloc(sizeof(char) * (len + 1));
    var[len] = '\0';
    for (int a = 0; a < len; a++) {
        var[a] = str[i + a];
    }
    return (var);
}

char *check_local_var(char *input, int i, infos_t *infos)
{
    char *var = get_var(input, i + 1);
    char *val = NULL;
    int len = 0;

    if (var == NULL)
        return (input);
    val = get_local_val(var, infos);
    if (val == NULL)
        return (input);
    len = strlen(var);
    input = insert_in_str(val, input, i + len + 1);
    for (int j = 0; j < len + 1; j++) {
        input = remove_in_str(input, i);
    }
    return (input);
}

char *parse_input_local_var(char *input, infos_t *infos)
{
    char *cpy = strdup(input);

    free(input);
    for (int i = 0; cpy[i] != '\0'; i++) {
        if (cpy[i] == '$' && cpy[i + 1] != ' ' && cpy[i + 1] != '\t')
            cpy = check_local_var(cpy, i, infos);
    }
    return (cpy);
}
