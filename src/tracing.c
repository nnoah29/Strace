/*
** EPITECH PROJECT, 2023
** Strace
** File description:
** Strace
*/

#include <errno.h>
#include <string.h>

#include "../includes/my.h"

static void print_instruction(struct user_regs_struct *regs)
{
    printf("%s", syscall_table[regs->rax]);
}

char *read_string_from_process(pid_t pid, unsigned long addr)
{
    static char buffer[MAX_STR_LEN];
    size_t i = 0;
    unsigned long word;

    while (i < MAX_STR_LEN - sizeof(long)) {
        word = ptrace(PTRACE_PEEKDATA, pid, addr + i, NULL);
        if (word == -1 && errno) {
            return NULL;
        }
        memcpy(&buffer[i], &word, sizeof(long));
        if (memchr(&word, '\0', sizeof(long)) != NULL)
            break;
        i += sizeof(long);
    }
    buffer[MAX_STR_LEN - 1] = '\0';
    return buffer;
}

static int print_int(unsigned long long int r)
{
    if (r < 0xFFFFFFFF) {
        printf("%d", (int)r);
        return 0;
    }
    return 1;
}

static int print_str(unsigned long long int r, pid_t child, int a)
{
    char *str;

    if (a == 0)
        return 1;
    str = read_string_from_process(child, r);
    if (str && str[0] >= 32 && str[0] <= 126) {
                        printf("\"%s\"", str);
    } else {
        printf("%#llx", r);
    }
    return 0;
}

static int print(unsigned long long int r, pid_t child)
{
    int a = 0;

    if (detailled){
        a = print_int(r);
        a = print_str(r, child, a);
    } else
        printf("%#llx", r);
    return 0;
}

int print_registre(unsigned long long int r, int is_last, pid_t child)
{
    if (r != 0) {
        print(r, child);
        if (!is_last)
            printf(", ");
        return 0;
    }
    return 1;
}

static void print_arguments(struct user_regs_struct *regs, pid_t child)
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
            print_registre(args[i], printed == count - 1, child);
            printed++;
        }
    printf(") = ");
}

void print_result(struct user_regs_struct *regs, pid_t child)
{
    print(regs->rax, child);
    printf("\n");
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
        print_arguments(regs, *child);
        ptrace(PTRACE_SINGLESTEP, *child, NULL, NULL);
        waitpid(*child, status, 0);
        ptrace(PTRACE_GETREGS, *child, NULL, regs);
        print_result(regs, *child);
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
