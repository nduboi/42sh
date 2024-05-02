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

static char *add_char_strings(char *first, char cara)
{
    int len = strlen(first);
    char *result = my_malloc(sizeof(char) * (len + 2));
    int i = 0;

    for (; first[i] != '\0'; i++)
        result[i] = first[i];
    result[i] = cara;
    free(first);
    return result;
}

static char *remove_last_char_strings(char *src)
{
    int len = strlen(src);
    char *result = my_malloc(sizeof(char) * (len));
    int i = 0;

    for (; src[i + 1] != '\0'; i++)
        result[i] = src[i];
    free(src);
    return result;
}

static bool handle_delete(char ch, char **strings)
{
    if (ch == 127) {
        if (strlen(*strings) > 0) {
            write(1, "\b \b", 3);
            *strings = remove_last_char_strings(*strings);
        }
        return true;
    }
    return false;
}

static void write_commands(char *strings)
{
    printf("\033[2K");
    printf("\r");
    fflush(stdout);
    write(1, strings, my_strlen(strings));
}

static int *init_data_arrow(void)
{
    int *data_arrow = my_malloc(sizeof(int *) * 3);

    data_arrow[0] = 0;
    data_arrow[1] = 0;
    return data_arrow;
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
    action_2 = handle_delete(ch, strings);
    action = handle_arrow(ch, data_arrow, *strings, list);
    if (action == false && action_2 == false)
        *strings = add_char_strings(*strings, ch);
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
        write_commands(strings);
        action = false;
    }
    return exit_getline(return_input, strings, &old, len);
}
