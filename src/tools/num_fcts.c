/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** num_fcts
*/

#include "mysh.h"
#include <unistd.h>
#include <stdbool.h>

static bool is_number(char c)
{
    return ('0' <= c && c <= '9');
}

int my_getnbr(char *str)
{
    int result = 0;
    int sign = 1;

    for (; *str; str++) {
        if (*str == '-' && sign == 1) {
            sign = -1;
            continue;
        }
        if (is_number(*str)) {
            result = result * 10 + *str - 48;
        } else {
            return -1;
        }
    }
    return result * sign;
}

int my_nbrlen(int nbr)
{
    int result = 0;

    while (nbr >= 1) {
        result++;
        nbr /= 10;
    }
    return result;
}

void my_putnbr(int nbr)
{
    char c = 0;

    c = 48 + (nbr % 10);
    if (nbr < 10) {
        write(1, &c, 1);
        return;
    }
    my_putnbr(nbr / 10);
    write(1, &c, 1);
}
