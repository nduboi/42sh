/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** test_my_strsignal
*/

#include "../include/mysh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_strsignal, hangup_signal, .init=redirect_all_std)
{
    int wstatus = 1;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Hangup\n");
}

Test(my_strsignal, interrupt_signal, .init=redirect_all_std)
{
    int wstatus = 2;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Interrupt\n");
}

Test(my_strsignal, quit_signal, .init=redirect_all_std)
{
    int wstatus = 3;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Quit\n");
}

Test(my_strsignal, illegal_signal, .init=redirect_all_std)
{
    int wstatus = 4;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Illegal instruction\n");
}

Test(my_strsignal, trap_signal, .init=redirect_all_std)
{
    int wstatus = 5;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Trace/BPT trap\n");
}

Test(my_strsignal, abort_signal, .init=redirect_all_std)
{
    int wstatus = 6;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Abort\n");
}

Test(my_strsignal, bus_signal, .init=redirect_all_std)
{
    int wstatus = 7;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Bus error\n");
}

Test(my_strsignal, float_signal, .init=redirect_all_std)
{
    int wstatus = 8;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Floating exception\n");
}

Test(my_strsignal, killed_signal, .init=redirect_all_std)
{
    int wstatus = 9;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Killed\n");
}

Test(my_strsignal, user_one_signal, .init=redirect_all_std)
{
    int wstatus = 10;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("User signal 1\n");
}

Test(my_strsignal, seg_fault_signal, .init=redirect_all_std)
{
    int wstatus = 11;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Segmentation fault\n");
}

Test(my_strsignal, user_two_signal, .init=redirect_all_std)
{
    int wstatus = 12;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("User signal 2\n");
}

Test(my_strsignal, pipe_signal, .init=redirect_all_std)
{
    int wstatus = 13;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Broken pipe\n");
}

Test(my_strsignal, alarm_signal, .init=redirect_all_std)
{
    int wstatus = 14;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Alarm clock\n");
}

Test(my_strsignal, term_signal, .init=redirect_all_std)
{
    int wstatus = 15;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Terminated\n");
}

Test(my_strsignal, stack_limit_signal, .init=redirect_all_std)
{
    int wstatus = 16;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Stack limit exceeded\n");
}

Test(my_strsignal, child_exit_signal, .init=redirect_all_std)
{
    int wstatus = 17;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Child exited\n");
}

Test(my_strsignal, continued_signal, .init=redirect_all_std)
{
    int wstatus = 18;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Continued\n");
}

Test(my_strsignal, stop_signal, .init=redirect_all_std)
{
    int wstatus = 19;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Stopped (signal)\n");
}

Test(my_strsignal, keyboard_stop_signal, .init=redirect_all_std)
{
    int wstatus = 20;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Stopped\n");
}

Test(my_strsignal, ttin_signal, .init=redirect_all_std)
{
    int wstatus = 21;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Stopped (tty input)\n");
}

Test(my_strsignal, ttout_signal, .init=redirect_all_std)
{
    int wstatus = 22;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Stopped (tty output)\n");
}

Test(my_strsignal, urgent_signal, .init=redirect_all_std)
{
    int wstatus = 23;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Urgent condition on I/O channel\n");
}

Test(my_strsignal, cputime_signal, .init=redirect_all_std)
{
    int wstatus = 24;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Cputime limit exceeded\n");
}

Test(my_strsignal, filesize_signal, .init=redirect_all_std)
{
    int wstatus = 25;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Filesize limit exceeded\n");
}

Test(my_strsignal, virtual_time_signal, .init=redirect_all_std)
{
    int wstatus = 26;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Virtual time alarm\n");
}

Test(my_strsignal, profiling_signal, .init=redirect_all_std)
{
    int wstatus = 27;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Profiling time alarm\n");
}

Test(my_strsignal, window_size_signal, .init=redirect_all_std)
{
    int wstatus = 28;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Window size changed\n");
}

Test(my_strsignal, io_signal, .init=redirect_all_std)
{
    int wstatus = 29;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Input/output possible signal\n");
}

Test(my_strsignal, power_failure_signal, .init=redirect_all_std)
{
    int wstatus = 30;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Power failure\n");
}

Test(my_strsignal, system_signal, .init=redirect_all_std)
{
    int wstatus = 31;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Bad system call\n");
}

Test(my_strsignal, segfault_coredump_signal, .init=redirect_all_std)
{
    int wstatus = 139;

    my_strsignal(wstatus);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}
