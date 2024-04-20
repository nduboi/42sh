/*
** EPITECH PROJECT, 2024
** environment cut
** File description:
** environement_cut_part
*/

#include "mysh.h"

void cut_in_part(char *data, char **part1, char **part2)
{
    int k = count_len_before_env(data) + 1;
    int l = 0;
    int b = count_len_after_env(k, data);

    free(*part1);
    free(*part2);
    (*part1) = my_malloc(sizeof(char) * (k + 1));
    (*part2) = my_malloc(sizeof(char) * (b + 1));
    for (int i = 0; data[i] != '\0'; i++) {
        if (i < (k - 1))
            (*part1)[i] = data[i];
        if (i > (b + 1)) {
            (*part2)[l] = data[i];
            l++;
        }
    }
}

void cut_in_part_brakets(char *data, char **part1, char **part2)
{
    int k = count_len_before_env(data) + 1;
    int l = 0;
    int b = count_len_after_env(k, data);

    free(*part1);
    free(*part2);
    (*part1) = my_malloc(sizeof(char) * (k + 1));
    (*part2) = my_malloc(sizeof(char) * (b + 1));
    for (int i = 0; data[i] != '\0'; i++) {
        if (i < (k - 1))
            (*part1)[i] = data[i];
        if (i > (b)) {
            (*part2)[l] = data[i];
            l++;
        }
    }
}
