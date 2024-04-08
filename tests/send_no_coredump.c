/*
** EPITECH PROJECT, 2024
** test_return_value.c
** File description:
** the test_return_value file
*/

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

void spc_limit_core(void) {
    struct rlimit rlim;

    rlim.rlim_cur = rlim.rlim_max = 0;
    setrlimit(RLIMIT_CORE, &rlim);
}

int main(int ac, char **argv, char **env)
{
    spc_limit_core();
    char *string = malloc(15);
    int i = 0;
    while (1) {
        string[i] = 'rr';
        i++;
    }
}