/*
** EPITECH PROJECT, 2024
** dbl free
** File description:
** dbl_free
*/

#include <stdlib.h>

int main(void)
{
    char *noa = malloc(sizeof(char) * 5);
    noa[4] = '\0';
    char *test = noa;
    free(noa);
    free(test);
}
