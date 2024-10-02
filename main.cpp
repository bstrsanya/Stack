#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

void StackCtor (stack_t *stk, int capacity);
void StackDump (stack_t *stk, FILE *file_output);
void StackPush (stack_t *stk, StackElem_t value);
void StackPop (stack_t *stk, StackElem_t *x);
void FreeStack (stack_t *stk);

int main()
{
    //const int b = __LINE__;
    //const char* a = __FILE__;
    //printf ("%s:%d\n", a, b);
    FILE* file_output = fopen ("result.txt", "wb");

    stack_t stk = {};
    StackCtor (&stk, 10);
    //StackDump (&stk, file_output);

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
    StackPush (&stk, 12);
    StackPush (&stk, 13);
    StackPush (&stk, 14);
    StackPush (&stk, 15);
    StackPush (&stk, 16);
    StackPush (&stk, 17);
    StackPush (&stk, 18);
    StackPush (&stk, 19);
    StackPush (&stk, 20);
    StackPush (&stk, 21);

    StackDump (&stk, file_output);
    FreeStack (&stk);
    StackDump (&stk, file_output);
    fclose (file_output);
}

void StackCtor (stack_t *stk, int capacity)
{
    stk->data = (StackElem_t*) calloc (capacity, sizeof (StackElem_t));
    stk->capacity = capacity;
    stk->size = 0;
}



void StackDump (stack_t *stk, FILE *file_output)
{
    fprintf (file_output, "stack address - %p\n", stk);
    fprintf (file_output, "elements address - %p\n", stk->data);
    fprintf (file_output, "stack capacity - %d\n", stk->capacity);
    fprintf (file_output, "stack occupancy - %d\n", stk->size);
    if (stk->data == NULL) fprintf (file_output, "Pointer is NULL, because of this, the elements were not found\n");
    else 
    {
        fprintf (file_output, "stack elements:\n");
        for (int i = 0; i < stk->capacity; i++)
            fprintf (file_output, "index #%d: value - %d\n", i, stk->data[i]);
    }
}

void StackPush (stack_t *stk, StackElem_t value)
{
    if ((stk->size) < (stk->capacity))
    {
        stk->data[stk->size++] = value;
    }
    else
    {
        stk->data = (StackElem_t*) realloc (stk->data, (stk->capacity) * 2 * sizeof (StackElem_t));
        assert (stk->data != NULL);
        stk->capacity *= 2;
        stk->data[stk->size++] = value;
    }
}

void StackPop (stack_t *stk, StackElem_t *x)
{
    if (stk->size > 0)
    {
        *x = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        stk->size -= 1;
    }
}

void FreeStack (stack_t *stk)
{
    free (stk->data); stk->data = NULL;
    stk->size = 0;
    stk->capacity = 0;
}


