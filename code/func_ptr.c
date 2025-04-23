/*
    Function pointers are used to pass functions as arguments to other functions.
    They are also used to return functions from other functions.
    They are also used to store functions in arrays.
    They are also used to store functions in structures.
    They are also used to store functions in linked lists.
    They are also used to store functions in binary trees.
    They are also used to store functions in hash tables.

    works well for menu systems, state machines, and replacing algorithms easily.
*/


#include <stdio.h>

#define NUM_FUNCS 3


void func0(int a, int b){
    printf("func0: %d, %d\n", a, b);
}

void func1(int a, int b){
    printf("func1: %d, %d\n", a, b);
}

void func2(int a, int b){
    printf("func2: %d, %d\n", a, b);
}


int main(int argc, char **argv){
    void (*func_ptr[NUM_FUNCS])(int, int) = {func0, func1, func2};

    for (int i = 0; i < NUM_FUNCS; i++){
        func_ptr[i](i, i+1);
    }
    return 0;
}