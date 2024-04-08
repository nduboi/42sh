/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** my_strsignal
*/

#include "mysh.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

const char *messages_tab[31] = {
    "Hangup",
    "Interrupt",
    "Quit",
    "Illegal instruction",
    "Trace/BPT trap",
    "Abort",
    "Bus error",
    "Floating exception",
    "Killed",
    "User signal 1",
    "Segmentation fault",
    "User signal 2",
    "Broken pipe",
    "Alarm clock",
    "Terminated",
    "Stack limit exceeded",
    "Child exited",
    "Continued",
    "Stopped (signal)",
    "Stopped",
    "Stopped (tty input)",
    "Stopped (tty output)",
    "Urgent condition on I/O channel",
    "Cputime limit exceeded",
    "Filesize limit exceeded",
    "Virtual time alarm",
    "Profiling time alarm",
    "Window size changed",
    "Input/output possible signal",
    "Power failure",
    "Bad system call"};

const int codes[31] = {
    SIGHUP,
    SIGINT,
    SIGQUIT,
    SIGILL,
    SIGTRAP,
    SIGABRT,
    SIGBUS,
    SIGFPE,
    SIGKILL,
    SIGUSR1,
    SIGSEGV,
    SIGUSR2,
    SIGPIPE,
    SIGALRM,
    SIGTERM,
    SIGSTKFLT,
    SIGCHLD,
    SIGCONT,
    SIGSTOP,
    SIGTSTP,
    SIGTTIN,
    SIGTTOU,
    SIGURG,
    SIGXCPU,
    SIGXFSZ,
    SIGVTALRM,
    SIGPROF,
    SIGWINCH,
    SIGIO,
    SIGPWR,
    SIGSYS};

void my_strsignal(int wstatus)
{
    int term_sig = WTERMSIG(wstatus);
    char *message = NULL;

    for (int i = 0; i < 31; i++) {
        if (codes[i] == term_sig) {
            message = (char *) messages_tab[i];
            break;
        }
    }
    write(2, message, my_strlen(message));
    if (WCOREDUMP(wstatus)) {
        write(2, " (core dumped)", 14);
    }
    write(2, "\n", 1);
}
