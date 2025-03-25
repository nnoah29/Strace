/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#ifndef MY_H
    #define MY_H
    #define _GNU_SOURCE

    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/ptrace.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/user.h>
    #include <sys/syscall.h>
    #include <unistd.h>
    #include "syscall_entry.h"
extern int detailled;
extern pid_t specific_PID;

void trace_prog(pid_t child);
int parse_command_line(int argc, char *argv[]);

#endif //MY_H
