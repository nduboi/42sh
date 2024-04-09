/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-42sh-alban.roussee
** File description:
** my_strcat_s
*/

#include "mysh.h"

char *my_strcat_s(char *str1, char *str2)
{
    int mutual_len = my_strlen(str1) + my_strlen(str2);
    char *dest = my_malloc(sizeof(char) * (mutual_len + 1));
    int i = 0;
    int j = 0;

    if (str1 == NULL) {
        free(dest);
        return str2;
    }
    for (; str1[i] != '\0'; i++) {
        dest[i] = str1[i];
    }
    for (; str2[j] != '\0'; j++)
        dest[i + j] = str2[j];
    return dest;
}
