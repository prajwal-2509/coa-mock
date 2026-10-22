#include <stdio.h>
#include <pthread.h>

int a, b;
int add_res, sub_res, mul_res;
float div_res;

pthread_mutex_t lock;

void *addition(void *arg)
{
    pthread_mutex_lock(&lock);

    asm volatile(
        "movl %1, %0\n\t"
        "addl %2, %0"
        : "=&r"(add_res)
        : "r"(a), "r"(b)
        : "cc"
    );

    printf("Thread 1 (Addition) finished\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *subtraction(void *arg)
{
    pthread_mutex_lock(&lock);

    asm volatile(
        "movl %1, %0\n\t"
        "subl %2, %0"
        : "=&r"(sub_res)
        : "r"(a), "r"(b)
        : "cc"
    );

    printf("Thread 2 (Subtraction) finished\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *multiplication(void *arg)
{
    pthread_mutex_lock(&lock);

    asm volatile(
        "movl %1, %0\n\t"
        "imull %2, %0"
        : "=&r"(mul_res)
        : "r"(a), "r"(b)
        : "cc"
    );

    printf("Thread 3 (Multiplication) finished\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *division(void *arg)
{
    pthread_mutex_lock(&lock);

    if (b == 0)
    {
        printf("Division by zero is not allowed.\n");
    }
    else
    {
        float x = (float)a;
        float y = (float)b;

        asm volatile(
            "divss %1, %0"
            : "+x"(x)
            : "x"(y)
        );

        div_res = x;
        printf("Thread 4 (Division) finished\n");
    }

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2, t3, t4;

    printf("Enter first number (a): ");
    scanf("%d", &a);

    printf("Enter second number (b): ");
    scanf("%d", &b);

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, addition, NULL);
    pthread_create(&t2, NULL, subtraction, NULL);
    pthread_create(&t3, NULL, multiplication, NULL);
    pthread_create(&t4, NULL, division, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("\nAddition = %d\n", add_res);
    printf("Subtraction = %d\n", sub_res);
    printf("Multiplication = %d\n", mul_res);

    if (b != 0)
        printf("Division = %.2f\n", div_res);

    pthread_mutex_destroy(&lock);

    return 0;
}