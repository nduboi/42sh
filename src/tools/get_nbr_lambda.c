/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** get_nbr_lambda
*/

#include "mysh.h"

int my_compute_power_rec(int nb, int p)
{
    if (p < 0) {
        return (0);
    }
    if (p == 0) {
        return (1);
    }
    nb = nb * my_compute_power_rec(nb, p - 1);
    return (nb);
}

int get_nbr_len(char *str, int i)
{
    int len = 0;

    while (str[i] >= 48 && str[i] <= 57) {
        len += 1;
        i++;
    }
    return len - 1;
}

int my_get_nbr_lambda(char *str)
{
    int nb = 0;
    int len = 0;
    int j = 0;
    int count = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            j = i;
            len = get_nbr_len(str, i);
            break;
        }
    }
    for (int i = len + j; i >= j; i--) {
        nb += ((str[i] - 48) * my_compute_power_rec(10, count));
        count += 1;
    }
    return nb;
}
