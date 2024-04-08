/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** error_messages
*/

#include "mysh.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

void error_message(char *str, int errnum)
{
    write(2, str, my_strlen(str));
    write(2, ": ", 2);
    write(2, strerror(errnum), my_strlen(strerror(errnum)));
    write(2, ".\n", 2);
}
