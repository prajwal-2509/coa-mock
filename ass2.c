// accpet string and display length of string using inline assembly
#include<stdio.h>
/*
int main(){
    char a[100];
    int len;

    printf("Enter a string: ");
    scanf("%99[^\n]",a);

    asm volatile(
        "xorl %%eax,%%eax\n\t"
        "1:\n\t"
            "cmpb $0,(%%rdi,%%rax,1)\n\t"
            "je 2f\n\t"

            "incl %%eax\n\t"
            "jmp 1b\n\t"
        "2:\n\t"
        :"=a"(len)
        :"D"(a)
        :"cc"
    );
    printf("Length of the string: %d\n", len);
    return 0;
}*/

//pos - neg count from an array
int main(){
    int arr[] = {1, -2, 3, -4, 5};
    int n=sizeof(arr)/sizeof(arr[0]);
    int pos_count=0,neg_count=0;

    asm volatile(
        "movl %[n], %%ecx\n\t"
        "xorl %%eax,%%eax\n\t"
        "xorl %%ebx,%%ebx\n\t"
        "movq %[arr], %%rdi\n\t"

        "1:\n\t"
            "cmpl $0, (%%rdi)\n\t"
            "jg Pcount\n\t"
            "jl Ncount\n\t"
            "jmp Next\n\t"

        "Pcount:\n\t"
            "incl %%eax\n\t"
            "jmp Next\n\t"
        
        "Ncount:\n\t"
            "incl %%ebx\n\t"
        
        "Next:\n\t"
            "addq $4, %%rdi\n\t"
            "loop 1b\n\t"

        "movl %%eax, %[pos_count]\n\t"
        "movl %%ebx, %[neg_count]\n\t"

        :[pos_count]"=r"(pos_count), [neg_count]"=r"(neg_count)
        :[arr]"r"(arr), [n]"r"(n)
        :"eax", "ebx", "ecx", "rdi", "cc"
    );

    printf("Positive count: %d\n", pos_count);
    printf("Negative count: %d\n", neg_count);
    return 0;
}