/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#include <string.h>
#include "../includes/my.h"

void exit_with_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(84);
}

void parse_command_line2(char *argv[], int *i, int argc, config_t *config)
{
    if (strcmp(argv[*i], "-s") == 0) {
        config->detailled = 1;
        return;
    }
    if (strcmp(argv[*i], "-p") == 0) {
        if ((*i) >= argc) {
            (*i)++;
            exit_with_error("Erreur: -p doit être suivi d'un PID.\n");
        }
        config->pid = atoi(argv[*i]);
        return;
    }
    for (int j = 0; j < 10; j++) {
        if (j != 0 && strcmp(argv[(*i) - 1], config->cmd[j - 1]) != 0)
            return;
        if (config->cmd[j] == NULL) {
            config->cmd[j] = strdup(argv[*i]);
            return;
        }
    }
}

char **parse_command_line(int argc, char *argv[], pid_t *pid)
{
    config_t config = {0};

    config.pid = -1;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-s] [-p <pid>|<command>]\n", argv[0]);
        exit(84);
    }
    config.cmd = malloc(sizeof(char *) * 10);
    if (!config.cmd) {
        perror("malloc");
        exit(84);
    }
    for (int i = 1; i < argc; i++) {
        parse_command_line2(argv, &i, argc, &config);
    }
    specific_PID = config.pid;
    detailled = config.detailled;
    return config.cmd;
}
