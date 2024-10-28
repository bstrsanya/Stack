#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

int main()
{
    FILE* file_output = fopen ("result.txt", "wb");
    if (file_output == NULL) printf ("ERROR OPENING THE FILE\n");

    stack_t stk = {};
    StackCtor (&stk, 10);

    StackDump (&stk, file_output, __FILE__, __LINE__);

    StackPush (&stk, 1.5);
    StackPush (&stk, 2.98);
    StackPush (&stk, 3.45);
    StackPush (&stk, 4);
    StackPush (&stk, 5);

    StackDump (&stk, file_output, __FILE__, __LINE__);
    // StackPush (&stk, 6);
    // StackPush (&stk, 7);
    // StackPush (&stk, 8);
    // StackPush (&stk, 9);
    // StackPush (&stk, 10);
    // StackPush (&stk, 11);

    double x = 0; 
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &x)));

    double y = 0;
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));

    StackPush (&stk, 1);
    StackPush (&stk, 2);
    StackPush (&stk, 3);
    StackPush (&stk, 4);
    StackPush (&stk, 5);

    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));

    StackDump (&stk, file_output, __FILE__, __LINE__);

    FreeStack (&stk);

    fclose (file_output);
}

// стек не защищен канарейками

// нельзя вызвать стек длиной 0

// если стоит DUMP после создания стэка с capacity = 1, то значение второй ячейки получается мусорное