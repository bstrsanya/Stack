#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "stack_func.h"

//#define StackASSERT(stk) StackAssertFunc(stk, __FILE__, __LINE__) 

void StackCtor (stack_t *stk, int capacity)
{
    stk->data = (StackElem_t*) calloc (capacity + 2, sizeof (StackElem_t)); // +2 для канареек
    stk->capacity = capacity;
    stk->size = 0;

    // Установка канареек
    stk->data[0] = CANARY;
    stk->data[capacity + 1] = CANARY;

    StackASSERT (stk);
}

void StackPush (stack_t *stk, StackElem_t value)
{
    StackASSERT (stk);

    if ((stk->size) < (stk->capacity))
        stk->data[stk->size++ + 1] = value; // +1 из-за левой канарейки

    else
    {
        stk->data = (StackElem_t*) realloc (stk->data, (stk->capacity) * 2 * sizeof (StackElem_t) + 2);
        StackASSERT (stk);

        stk->capacity *= 2;
        stk->data[stk->capacity+1] = CANARY;
        stk->data[stk->size++ + 1] = value; // убрать повторение строк, выдвинуть realloc вверх
    }                                       // проверять указатель на стэк
    StackASSERT (stk);
}

void StackPop (stack_t *stk, StackElem_t *x)  // void -> int 
{                                             // Myrealloc
    StackASSERT (stk);
    if (stk->size > 0)
    {
        *x = stk->data[stk->size];
        stk->data[stk->size] = 0;
        stk->size -= 1;
    }
    if (stk->capacity > 2 * stk->size)
    {
        stk->data = (StackElem_t*) realloc (stk->data, (stk->capacity) * 0.5 * sizeof (StackElem_t) + 2);
        StackASSERT (stk);

        stk->capacity /= 2;
        stk->data[stk->capacity+1] = CANARY;
    }
    StackASSERT (stk);
}

void StackDump (stack_t *stk, FILE *file_output, const char* name_file, const int n_str)
{
    fprintf (file_output, "stack_t [%p] at %s:%d\n", stk, name_file, n_str);
    fprintf (file_output, "size     = %d\n", stk->size);
    fprintf (file_output, "capacity = %d\n", stk->capacity);
    fprintf (file_output, "data [%p]:\n", stk->data);

    if (stk->data == NULL) 
        fprintf (file_output, "Pointer is NULL, because of this, the elements were not found\n");
    
    else 
    {
        fprintf (file_output, "{\n");
        fprintf (file_output, " CANARY_LEFT = %d\n", stk->data[0]);
        for (int i = 1; i < stk->capacity + 1; i++)
        {
            if (i < stk->size + 1)
                fprintf (file_output, "*[%d] = %d\n", i, stk->data[i]);
            else
                fprintf (file_output, " [%d] = %d\n", i, stk->data[i]);
        }
        fprintf (file_output, " CANARY_RIGHT = %d\n", stk->data[stk->capacity + 1]);
        fprintf (file_output, "}\n");
    }
}

void FreeStack (stack_t *stk)
{
    StackASSERT (stk);
    free (stk->data); stk->data = NULL;
    stk->size = 0;
    stk->capacity = 0;
}

int StackOK (stack_t *stk) // stk chek
{
    if (stk == NULL)
        return Stack_Pointer_Stk_NULL;

    if (stk->capacity < stk->size) 
        return Stack_Little_Capacity;

    if (stk == NULL) 
        return Stack_Pointer_Struct_NULL;

    if (stk->data == NULL) 
        return Stack_Pointer_Data_NULL;

    if (stk->capacity < 0) 
        return Stack_Capacity_Negative;  

    if (stk->size < 0) 
        return Stack_Size_Negative;

    if (stk->data[0] != CANARY)
        return Stack_CanaryLeft_Wrong;

    if (stk->data[stk->capacity + 1] != CANARY)
        return Stack_CanaryRight_Wrong;
        
    return 0; 
}

void StackASSERT (stack_t *stk) // сделать эту функцию в макрос (чтоб отключать)
{
    error stack_error = (error) StackOK (stk);
    if (stack_error != 0)
    {
        printf ("%s\n", StackErrDescr (stack_error));
        assert (0);
    }
}

const char* StackErrDescr (error stack_error)
{
    #define ERROR(stack_error) case stack_error: return #stack_error

    switch (stack_error)
    {
        ERROR (Stack_Little_Capacity);
        ERROR (Stack_Pointer_Struct_NULL);
        ERROR (Stack_Pointer_Data_NULL);
        ERROR (Stack_Capacity_Negative);
        ERROR (Stack_Size_Negative);
        ERROR (Stack_CanaryLeft_Wrong);
        ERROR (Stack_CanaryRight_Wrong);
        ERROR (Stack_Pointer_Stk_NULL);
    }

    #undef ERROR
}