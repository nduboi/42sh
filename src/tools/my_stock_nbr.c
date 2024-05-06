/*
** EPITECH PROJECT, 2023
** my_stock_nbr
** File description:
** Stock all the possible values of an int
*/

#include "mysh.h"

static char *check_minus(int *nb, char *src)
{
    if (*nb < 0) {
        *nb = -(*nb);
        return (src);
    }
    return (src);
}

static int my_stock_len(int nb)
{
    int len = 0;

    if (nb == 0) {
        return (1);
    }
    while (nb != 0) {
        nb /= 10;
        len += 1;
    }
    return (len);
}

char *my_stock_nbr(int nb)
{
    int divisor = 1;
    char *result = my_malloc(sizeof(char) * (my_stock_len(nb) + 1));

    if (nb == -2147483648) {
        result = "-2147483648";
        return (result);
    }
    result = check_minus(&nb, result);
    for (int i = 0; i < (my_stock_len(nb) - 1); i++)
        divisor = divisor * 10;
    for (int j = 0; j < my_stock_len(nb); j++) {
        result[j] = ((nb / divisor) % 10) + 48;
        divisor = divisor / 10;
    }
    return (result);
}
