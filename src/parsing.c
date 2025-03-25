/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#include <string.h>
#include "../includes/my.h"

void parse_specific_pid(char *argv[], int idx)
{
    if (argv[idx] == NULL) {
        exit(EXIT_FAILURE);
    }
    specific_PID = atoi(argv[idx]);
}

int parse_command_line(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(84);
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0)
            detailled = 1;
        if (strcmp(argv[i], "-p") == 0)
            parse_specific_pid(argv, i + 1);
    }
    return 0;
}
