/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#include <stdio.h>
#include <unistd.h>
#include "../includes/my.h"
#include <unistd.h>
#include <fcntl.h>

int detailled = 0;
pid_t specific_PID = -1;

void deactivation_output(void)
{
    const int devnull = open("/dev/null", O_WRONLY);

    if (devnull != -1) {
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        close(devnull);
    }
}

int main(int argc, char *argv[])
{
    pid_t child = -1;
    char **prog = parse_command_line(argc, argv, &specific_PID);

    child = fork();
    if (child == -1)
        exit_with_error("fork");
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        deactivation_output();
        execvp(prog[0], prog);
        perror("execvp");
        return 1;
    } else {
        trace_prog(child);
    }
    for (int i = 0; prog[i] != NULL; i++)
        free(prog[i]);
    free(prog);
    return 0;
}
