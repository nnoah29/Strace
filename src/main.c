/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#include <stdio.h>
#include <unistd.h>
#include "../includes/my.h"

int detailled = 0;
pid_t specific_PID = 0;

int main(int argc, char *argv[])
{
    pid_t child = -1;

    parse_command_line(argc, argv);
    child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execvp(argv[1], &argv[1]);
        perror("execvp");
        return 1;
    } else {
        trace_prog(child);
    }
    return 0;
}
