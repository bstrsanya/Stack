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

    StackPush (&stk, 1);
    StackPush (&stk, 2);
    StackPush (&stk, 3);
    StackPush (&stk, 4);
    StackPush (&stk, 5);
    StackPush (&stk, 6);
    StackPush (&stk, 7);
    StackPush (&stk, 8);
    StackPush (&stk, 9);
    StackPush (&stk, 10);
    StackPush (&stk, 11);

    StackDump (&stk, file_output, __FILE__, __LINE__);

    int x = 0; 
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &x)));

    int y = 0;
    printf ("%s\n", StackErrDescr((error) StackPop (&stk, &y)));

    StackDump (&stk, file_output, __FILE__, __LINE__);

    FreeStack (&stk);
    fclose (file_output);
}




