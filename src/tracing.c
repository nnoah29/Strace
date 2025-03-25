/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#include "../includes/my.h"

void print_instruction(struct user_regs_struct *regs)
{
    printf("%s", syscall_table[regs->rax]);
}

int print_registre(unsigned long long int r, int is_last)
{
    if (r != 0) {
        printf("%#llx", r);
        if (!is_last)
            printf(", ");
        return 0;
    }
    return 1;
}

static void print_arguments(struct user_regs_struct *regs)
{
    const unsigned long long args[] = {regs->rdi, regs->rsi, regs->rdx,
        regs->r10, regs->r8, regs->r9};
    int count = 0;
    int printed = 0;

    printf("(");
    for (size_t i = 0; i < 6; i++)
        if (args[i] != 0)
            count++;
    for (size_t i = 0; i < 6; i++)
        if (args[i] != 0) {
            print_registre(args[i], printed == count - 1);
            printed++;
        }
    printf(") = ");
}

void print_result(struct user_regs_struct *regs)
{
    printf("%#llx\n", regs->rax);
}

int trace(struct user_regs_struct *regs, const pid_t *child, int *status)
{
    long instruction = 0;

    instruction = ptrace(PTRACE_PEEKTEXT, *child, (void *)regs->rip, NULL);
    if (instruction == -1) {
        perror("ptrace peek text");
        return 1;
    }
    if ((instruction & 0xFFFF) == 0x050F) {
        print_instruction(regs);
        print_arguments(regs);
        ptrace(PTRACE_SINGLESTEP, *child, NULL, NULL);
        waitpid(*child, status, 0);
        ptrace(PTRACE_GETREGS, *child, NULL, regs);
        print_result(regs);
    }
    return 0;
}

void trace_prog(pid_t child)
{
    int status;
    struct user_regs_struct regs;

    waitpid(child, &status, 0);
    while (1) {
        if (WIFEXITED(status))
            break;
        if (ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) < 0) {
            perror("ptrace singles");
            break;
        }
        waitpid(child, &status, 0);
        if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) {
            perror("ptrace get regs");
            break;
        }
        if (trace(&regs, &child, &status) == 1)
            break;
    }
}
