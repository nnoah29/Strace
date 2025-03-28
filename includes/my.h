/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#ifndef MY_H
    #define MY_H
    #define _GNU_SOURCE
    #define MAX_STR_LEN 256

    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/ptrace.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/user.h>
    #include <sys/syscall.h>
    #include <unistd.h>
    #include "syscall_entry.h"
typedef struct config_t {
    int detailled;
    pid_t pid;
    char **cmd;
} config_t;
extern int detailled;
extern pid_t specific_PID;

void trace_prog(pid_t child);
char **parse_command_line(int argc, char *argv[], pid_t *pid);
void exit_with_error(char *msg);
#endif //MY_H
