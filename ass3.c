#include <stdio.h>

int sum_n(int n){
    int res;

    asm volatile(
        "movl %1, %%ecx\n\t"
        "xorl %%eax,%%eax\n\t"
        "testl %%ecx,%%ecx\n\t"
        "jle 2f\n\t"
        "1:\n\t"
            "addl %%ecx,%%eax\n\t"
            "decl %%ecx\n\t"
            "jne 1b\n\t"
        "2:\n\t"
        :"=a"(res)
        :"r"(n)
        :"cc","ecx"
        );
        return res;
}

int main(){

    int n , result;
    printf("Enter a positive integer: ");

    if(scanf("%d",&n) != 1 || n < 0){
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    result = sum_n(n);
    printf("Sum of first %d natural numbers is: %d\n", n, result);
    return 0;
}