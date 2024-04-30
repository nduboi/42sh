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

static void handle_arrow(bool *action, char ch)
{
    char seq[2];

    if (ch == 27) {
        seq[0] = getchar();
        seq[1] = getchar();
        if (seq[1] == '[' && seq[1] == 'C') {
            //Fleche de droite
        }
        if (seq[1] == '[' && seq[1] == 'D') {
            //Fleche de droite
        }
        if (seq[1] == '[' && seq[1] == 'A') {
            //Fleche du haut
        }
        if (seq[1] == '[' && seq[1] == 'B') {
            //Fleche du bas
        }
        *action = true;
    }
}

static void handle_delete(char ch, char **strings, bool *action)
{
    if (ch == 127) {
        if (strlen(*strings) > 0) {
            write(1, "\b \b", 3);
            *strings = remove_last_char_strings(*strings);
        }
        *action = true;
    }
}

char *getline_modif(void)
{
    char ch = '\0';
    char *strings = my_malloc(sizeof(char) * 1);
    bool action = false;
    struct termios old;
    struct termios new;

    init_termios(0, &old, &new);
    while (ch != '\n') {
        ch = getchar();
        if (ch == '\n')
            break;
        handle_delete(ch, &strings, &action);
        handle_arrow(&action, ch);
        if (!action)
            strings = add_char_strings(strings, ch);
        printf("\033[2K");
        printf("\r");
        fflush(stdout);
        write(1, strings, my_strlen(strings));
        action = false;
    }
    write(1, "\n", 1);
    reset_termios(&old);
    return strings;
}
