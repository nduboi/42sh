/*
** EPITECH PROJECT, 2024
** getline modif
** File description:
** main
*/

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mysh.h"
#include <sys/ioctl.h>

static void init_termios(int echo, struct termios *old, struct termios *new)
{
    tcgetattr(0, old);
    *new = *old;
    (*new).c_lflag &= ~ICANON;
    (*new).c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, new);
}

static void reset_termios(struct termios *old)
{
    tcsetattr(0, TCSANOW, old);
}

static char *add_char_strings(char *first, char cara, int *data_arrow)
{
    char *result = my_malloc(sizeof(char) * (my_strlen(first) + 2));
    int i = 0;

    for (; i < (my_strlen(first) - data_arrow[0]); i++) {
        result[i] = first[i];
    }
    result[i] = cara;
    for (int k = my_strlen(first) - data_arrow[0]; first[k] != '\0'; k++) {
        result[k + 1] = first[k];
    }
    free(first);
    return result;
}

static char *remove_char_strings(char *src, int cursor)
{
    int len = strlen(src);
    char *result = my_malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (cursor == len)
        return src;
    for (; i < (len - cursor - 1); i++)
        result[i] = src[i];
    for (i++; src[i] != '\0'; i++)
        result[i - 1] = src[i];
    free(src);
    return result;
}

static bool handle_delete(char ch, char **strings, int cursor)
{
    if (ch == 127) {
        if (strlen(*strings) > 0)
            *strings = remove_char_strings(*strings, cursor);
        return true;
    }
    return false;
}

static void write_commands(char *strings, bool *action, int *data_action)
{
    struct winsize ws;
    int len = 0;
    int nbr_delete = 0;
    int i = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    len = my_strlen(strings) + get_nbr_line_new_prompt();
    nbr_delete = (len) / ws.ws_col;
    printf("\r");
    if (nbr_delete != 0)
        printf("\033[%dA", nbr_delete);
    printf("\033[J");
    fflush(stdout);
    write_prompt_without_env();
    write(1, strings, my_strlen(strings));
    if (data_action[0] > 0)
        printf("\033[%dD", data_action[0]);
    *action = false;
}

static int handle_data_user(char **strings, int **data_arrow, infos_t *list)
{
    char ch = getchar();
    bool action = false;
    bool action_2 = false;

    if (ch == '\n')
        return 1;
    if (ch == 4)
        return 2;
    if (ch == 12)
        return 3;
    action_2 = handle_delete(ch, strings, (*data_arrow)[0]);
    action = handle_arrow(ch, data_arrow, strings, list);
    if (action == false && action_2 == false)
        *strings = add_char_strings(*strings, ch, *data_arrow);
    return 0;
}

static char *exit_getline(int return_input, char *strings,
    struct termios *old, int *len)
{
    if (return_input == 1)
        write(1, "\n", 1);
    reset_termios(old);
    if (return_input == 1) {
        *len = my_strlen(strings);
        return strings;
    } else {
        *len = EOF;
        return NULL;
    }
}

static void clear_terminal(char *strings)
{
    printf("\033[2J");
    printf("\033[H");
    write_prompt_without_env();
    fflush(stdout);
    if (strings)
        write(1, strings, my_strlen(strings));
}

char *getline_modif(infos_t *list, int *len)
{
    char ch = '\0';
    char *strings = my_malloc(sizeof(char) * 1);
    bool action = false;
    bool action_2 = false;
    struct termios old;
    struct termios new;
    int *data_arrow = init_data_arrow();
    int return_input = 0;

    init_termios(0, &old, &new);
    while (1) {
        return_input = handle_data_user(&strings, &data_arrow, list);
        if (return_input == 1 || return_input == 2)
            break;
        if (return_input == 3)
            clear_terminal(strings);
        else
            write_commands(strings, &action, data_arrow);
    }
    return exit_getline(return_input, strings, &old, len);
}
