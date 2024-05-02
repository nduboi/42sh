/*
** EPITECH PROJECT, 2024
** handle_arrow_getline
** File description:
** handle_arrow_getline
*/

#include "mysh.h"


static bool handle_up_arrow(char seq[2], int **data_arrow, infos_t *list,
    char *strings)
{
    char *new_command = NULL;

    if (seq[0] == '[' && seq[1] == 'A') {
        new_command = recall_by_id((*data_arrow)[1], list);
        if (new_command)
            (*data_arrow)[1] = (*data_arrow)[1] + 1;
        else
            return true;
        free(strings);
        strings = my_strdup(new_command);
    }
    return false;
}

static bool handle_down_arrow(char seq[2], int **data_arrow, infos_t *list,
    char *strings)
{
    char *new_command = NULL;

    if (seq[0] == '[' && seq[1] == 'B') {
        new_command = recall_by_id((*data_arrow)[1] - 2, list);
        if (new_command)
            (*data_arrow)[1] = (*data_arrow)[1] - 1;
        else
            return true;
        free(strings);
        strings = my_strdup(new_command);
    }
    return false;
}

static void handle_right_arrow(char seq[2], int **data_arrow)
{
    if (seq[0] == '[' && seq[1] == 'C') {
        if ((*data_arrow)[0] > 0 && (*data_arrow)[0] != 0)
            (*data_arrow)[0] = (*data_arrow)[0] - 1;
    }
}

static void handle_left_arrow(char seq[2], int **data_arrow)
{
    if (seq[0] == '[' && seq[1] == 'D') {
        (*data_arrow)[0] = (*data_arrow)[0] + 1;
    }
}

bool handle_arrow(char ch, int **data_arrow, char *strings,
    infos_t *list)
{
    char seq[2];

    if (ch == 27) {
        seq[0] = getchar();
        seq[1] = getchar();
        handle_left_arrow(seq, data_arrow);
        handle_right_arrow(seq, data_arrow);
        if (handle_up_arrow(seq, data_arrow, list, strings))
            return true;
        if (handle_down_arrow(seq, data_arrow, list, strings))
            return true;
        return true;
    }
    return false;
}
