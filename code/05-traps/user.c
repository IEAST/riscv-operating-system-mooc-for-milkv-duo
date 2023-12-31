#include "include/os.h"

#define DELAY 1000

extern void trap_test(void);

void user_task0(void)
{
    trap_test();
    printf("Task 0: Created!\n");
    while (1)
    {
        printf("Task 0: Running...\n");
        task_delay(DELAY);
        task_yield();
    }
}

void user_task1(void)
{
    printf("Task 1: Created!\n");
    while (1)
    {
        printf("Task 1: Running...\n");
        task_delay(DELAY);
        task_yield();
    }
}

void os_main(void)
{
    task_create(user_task0);
    task_create(user_task1);
}