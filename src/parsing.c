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

void parse_commande_line3(char *argv[], const int *i, config_t *config)
{
    for (int j = 0; j < 10; j++) {
        if (j != 0 && strcmp(argv[(*i) - 1], config->cmd[j - 1]) != 0)
            return;
        if (config->cmd[j] == NULL) {
            config->cmd[j] = strdup(argv[*i]);
            return;
        }
    }
}

void parse_command_line2(char *argv[], int *i, int argc, config_t *config)
{
    int a = 0;

    if (strcmp(argv[*i], "-s") == 0) {
        config->detailled = 1;
        return;
    }
    if (strcmp(argv[*i], "-p") == 0) {
        a = (*i) + 1;
        if (a >= argc)
            exit_with_error("Erreur: -p doit être suivi d'un PID.\n");
        (*i)++;
        config->pid = atoi(argv[*i]);
        return;
    }
    parse_commande_line3(argv, i, config);
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
