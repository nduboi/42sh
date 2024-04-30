/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** handle_globbing
*/

#include "mysh.h"
#include <dirent.h>
#include <glob.h>

#include <string.h>

static int print_and_free(char *new_cmd, char *ini_cmd,
    char **cmd, char **words)
{
    if ((strstr(new_cmd, "*") != NULL && strstr(ini_cmd, "*") != NULL)
        || (strstr(new_cmd, "?") != NULL && (strstr(ini_cmd, "?") != NULL))) {
        fprintf(stderr, "%s: No match.\n", words[0]);
        free(words);
        free(*cmd);
        free(ini_cmd);
        *cmd = NULL;
        return 1;
    }
    free(words);
    if (strlen(new_cmd) > 0)
    new_cmd[strlen(new_cmd) - 1] = '\0';
    free(*cmd);
    *cmd = new_cmd;
    free(ini_cmd);
    return 0;
}

static void append_words(glob_t glob_result, int *match_found, char **new_cmd)
{
    if (glob_result.gl_pathc == 0) {
        *match_found = 0;
    } else {
        for (int j = 0; j < (int)glob_result.gl_pathc; j++) {
            (*new_cmd) = realloc((*new_cmd), strlen((*new_cmd)) +
                strlen(glob_result.gl_pathv[j]) + 2);
            strcat((*new_cmd), glob_result.gl_pathv[j]);
            strcat((*new_cmd), " ");
            *match_found = 1;
        }
    }
    globfree(&glob_result);
}

static void looking_for_match(char **new_cmd, int word_count, char **words)
{
    int flags = GLOB_TILDE | GLOB_BRACE | GLOB_ERR;
    glob_t glob_result;
    int match_found = 0;

    (*new_cmd) = malloc(sizeof(char) * 1);
    (*new_cmd)[0] = '\0';
    for (int i = 0; i < word_count; i++) {
        match_found = 0;
        if (glob(words[i], flags, NULL, &glob_result) == 0) {
            append_words(glob_result, &match_found, new_cmd);
        } else {
            (*new_cmd) = realloc((*new_cmd),
                strlen((*new_cmd)) + strlen(words[i]) + 2);
            strcat((*new_cmd), words[i]);
            strcat((*new_cmd), " ");
            match_found = 1;
        }
        if (!match_found)
            free(words[i]);
    }
}

int handle_globbings(char **cmd)
{
    char *initial_command = my_strdup(*cmd);
    char *word = NULL;
    char *new_cmd = NULL;
    char **words = NULL;
    int word_count = 0;

    word = strtok(*cmd, " \t");
    while (word != NULL) {
        words = realloc(words, (word_count + 1) * sizeof(char *));
        words[word_count] = strdup(word);
        word_count++;
        word = strtok(NULL, " \t");
    }
    looking_for_match(&new_cmd, word_count, words);
    return (print_and_free(new_cmd, initial_command, cmd, words));
}
