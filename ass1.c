#include<stdio.h>

/*short add
int main(){

    short a=15000,b=12000,sum;
    asm volatile(
        "movw %1,%%ax\n\t"
        "addw %2,%%ax\n\t"
        "movw %%ax,%0"
        :"=r"(sum)
        :"r"(a),"r"(b)
        :"ax"
    );

    printf("Short sum = %d",sum);
    return 0;
}*/

/* long add
int main(){
    long a = 50000000L,b = 2000000000L,sum;
    asm volatile(
        "movl %1,%%eax\n\t"
        "addl %2,%%eax\n\t"
        "movl %%eax,%0"
        :"=r"(sum)
        :"r"(a),"r"(b)
        :"eax"
    );

    printf("Long sum = %ld",sum);
    return 0;
}*/


/*  signed multiplication 
int main(){
    int a =-25,b=2,mul;

    asm volatile(
        "movl %1,%%eax\n\t"
        "imull %2,%%eax\n\t"
        "movl %%eax,%0"
        :"=r"(mul)
        :"r"(a),"r"(b)
        :"eax"
    );

    printf("Int product = %d",mul);
    return 0;
}
*/


int main(){
    int a=-100,b=3,q,r;
    asm volatile(
        "movl %2,%%eax\n\t"
        "cltd\n\t"
        "idivl %3\n\t"
        "movl %%eax,%0\n\t"
        "movl %%edx,%1"
        :"=r"(q),"=r"(r)
        :"r"(a),"r"(b)
        :"eax","edx"
    );
    printf("Quotient = %d, Remainder = %d",q,r);
    return 0;
}