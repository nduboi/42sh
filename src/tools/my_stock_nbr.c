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
    int divided = 1;
    int k = 0;
    char *src = malloc(sizeof(char) * (my_nbrlen(nb) + 1));

    if (nb == -2147483648) {
        src = "-2147483648";
        return (src);
    }
    src = check_minus(&nb, src);
    for (int i = 0; i < (my_stock_len(nb) - 1); i++)
        divided = divided * 10;
    for (int j = 0; j < my_stock_len(nb); j++) {
        src[k] = ((nb / divided) % 10) + 48;
        divided = divided / 10;
        k++;
    }
    src[k] = '\0';
    return (src);
}
