#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n, fact;

    if (argc != 2)
    {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    if (n < 0)
    {
        printf("Factorial of negative number is not defined\n");
        return 1;
    }

    if (n > 12)
    {
        printf("Number too large for 32-bit factorial\n");
        return 1;
    }

    asm volatile(
        "movl %[n], %%ecx\n\t"
        "movl $1, %%eax\n\t"

        "1:\n\t"
        "cmpl $1, %%ecx\n\t"
        "jle 2f\n\t"

        "imull %%ecx, %%eax\n\t"
        "decl %%ecx\n\t"
        "jmp 1b\n\t"

        "2:\n\t"

        : "=a"(fact)
        : [n] "r"(n)
        : "ecx", "cc"
    );

    printf("Factorial = %d\n", fact);

    return 0;
}