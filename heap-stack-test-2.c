#include "heap-stack-tests.h"

#include <unistd.h>
#include <pthread.h>


int foo_1(void)
{
    stack_scope;

    int_array_t array = create_simple_int_array(10);

    if (!array.len) {
        return -1;
    }
    print_int_array(array, 10);

    return 0;
}

int foo_2(void)
{
    stack_scope;
    int_array_t array = create_simple_int_array(10);

    if (!array.len) {
        return -1;
    }
    print_int_array(array, 10);

    return 0;
}

void foo_3(void)
{
    stack_scope;
    int_array_t array;

    for (int i = 0; i < 100; i++) {
        array = create_simple_int_array(4096);

        if (!array.len) {
            printf("maximum size of the heap stack reach could not "
                   " allocate more.\n");
            return;
        }
    }

    (void)array;
}

void *thread_func(void *vargp)
{
    stack_scope;
    int_array_t array;

    for (int i = 0; i < 3; i++) {
        array = create_simple_int_array(10);
        print_int_array(array, 10);
        sleep(1);
    }

    (void)vargp;
    return NULL;
}

void foo_4(void)
{
    pthread_t thread_id_1;
    pthread_t thread_id_2;

    pthread_create(&thread_id_1, NULL, thread_func, NULL);
    pthread_create(&thread_id_2, NULL, thread_func, NULL);

    pthread_join(thread_id_1, NULL);
    pthread_join(thread_id_2, NULL);
}

int test_2(void)
{
    /* Init and delete two heap stack in the same process */
    foo_1();
    foo_2();

    /* exceed limit size of the heap stack */
    foo_3();

    /* Test thread independance */
    foo_4();
    return 0;
}
