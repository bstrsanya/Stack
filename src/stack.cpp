#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "./../include/stack.h"

//#define StackASSERT(stk) StackAssertFunc(stk, __FILE__, __LINE__) 

void StackCtor (stack_t *stk, int capacity)
{
    if (stk == NULL)
    {
        printf ("Pointer to the stack is NULL\n");
        assert (0);
    }

    if (capacity < 1)
    {
        printf ("Capacity is negative\n");
        assert (0);
    }

    stk->data = (StackElem_t*) calloc ((size_t) capacity + 2, sizeof (StackElem_t)); // +2 для канареек

    if (stk->data == NULL)
    {
        printf ("Pointer to the data is NULL\n");
        assert (0);
    }

    stk->capacity = (size_t) capacity;
    stk->size = 0;

    // Установка канареек
    DEBUG_ON (
    stk->data[0] = CANARY;
    stk->data[capacity + 1] = CANARY; )

    DEBUG_ON (StackASSERT (stk);)
}

void StackPush (stack_t *stk, StackElem_t value)
{
    DEBUG_ON (StackASSERT (stk);)

    if ((stk->size) == (stk->capacity)) {
        //printf ("Now be realloc\n");
        //Dump (stk, __FILE__, __LINE__);
        MyRealloc (stk, 2); }
    
    stk->data[stk->size++ + 1] = value; // +1 из-за левой канарейки

    DEBUG_ON (StackASSERT (stk);)
}

int StackPop (stack_t *stk, StackElem_t *x) 
{                                           
    DEBUG_ON (StackASSERT (stk);)

    if (stk->size > 0)
    {
        *x = stk->data[stk->size];
        stk->data[stk->size] = 0;
        stk->size -= 1;
    }
    
    else
        return Stack_Is_Empty;

    if ((stk->capacity > 2 * stk->size) && (stk->capacity > 1))
        MyRealloc (stk, 0.5);

    DEBUG_ON (StackASSERT (stk);)
    return Stack_Pop_Ok;
}

#ifdef DEBUG
void StackDump (stack_t *stk, FILE *file_output, const char* name_file, const int n_str)
{
    if (stk == NULL)
    {
        printf ("Pointer to the stack is NULL\n");
        assert (0);
    }

    fprintf (file_output, "stack_t [%p] at %s:%d\n", stk, name_file, n_str);
    //fprintf (file_output, "at %s:%d\n", stk->name_file, stk->n_str);
    fprintf (file_output, "size     = %lu\n", stk->size);
    fprintf (file_output, "capacity = %lu\n", stk->capacity);
    fprintf (file_output, "data [%p]:\n", stk->data);

    if (stk->data == NULL) 
        fprintf (file_output, "Pointer is NULL, because of this, the elements were not found\n");
    else 
    {
        fprintf (file_output, "{\n");
        fprintf (file_output, " CANARY_LEFT = %lf\n", stk->data[0]);
        for (int i = 1; i < (int) stk->capacity + 1; i++)
        {
            if (i < (int) stk->size + 1)
                fprintf (file_output, "*[%d] = %lf\n", i, stk->data[i]);
            else
                fprintf (file_output, " [%d] = %lf\n", i, stk->data[i]);
        }
        fprintf (file_output, " CANARY_RIGHT = %lf\n", stk->data[stk->capacity + 1]);
        fprintf (file_output, "}\n");
    }
}
#endif

void FreeStack (stack_t *stk)
{
    DEBUG_ON (StackASSERT (stk);)
    free (stk->data); stk->data = NULL;
    stk->size = 0;
    stk->capacity = 0;
}

#ifdef DEBUG
int StackOK (stack_t *stk)
{
    if (stk == NULL)
        return Stack_Pointer_Struct_NULL;

    if (stk->capacity < stk->size) 
        return Stack_Little_Capacity;

    if (stk->data == NULL) 
        return Stack_Pointer_Data_NULL;

    // if (stk->capacity < 0) 
    //     return Stack_Capacity_Negative;  

    // if (stk->size < 0) 
    //     return Stack_Size_Negative;

    if ((int) stk->data[0] != CANARY)
        return Stack_CanaryLeft_Wrong;

    if ((int) stk->data[stk->capacity + 1] != CANARY)
        return Stack_CanaryRight_Wrong;
        
    return 0; 
}

void StackASSERT (stack_t *stk) 
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
        ERROR (Stack_Is_Empty);
        ERROR (Stack_Pop_Ok);
        ERROR (CANARY);
        default: break;
    }
    return "s";
    #undef ERROR
}
#endif

void MyRealloc (stack_t *stk, double coef)
{
    DEBUG_ON (StackASSERT (stk);)
    StackElem_t* new_pointer = (StackElem_t*) realloc (stk->data, (size_t) ((int) stk->capacity * coef * sizeof (StackElem_t) + 2 * sizeof (StackElem_t)));
    if (new_pointer == NULL)
    {
        printf ("Additional memory allocation error\n");
        free (stk->data); stk->data = NULL;
        assert (0);
    }

    else
    {
        stk->data = new_pointer; //!!!
        if ((int) coef == 2) stk->data[stk->capacity+1] = 0;
        stk->capacity = (size_t) (((int) stk->capacity) * coef);
        DEBUG_ON (
        stk->data[stk->capacity + 1] = CANARY;      
        StackASSERT (stk);)
    }
}

#ifdef DEBUG
void Dump (stack_t *stk, const char* name_file, const int n_str)
{
    if (stk == NULL)
    {
        printf ("Pointer to the stack is NULL\n");
        assert (0);
    }

    printf ("stack_t [%p] at %s:%d\n", stk, name_file, n_str);
    //fprintf (file_output, "at %s:%d\n", stk->name_file, stk->n_str);
    printf ("size     = %lu\n", stk->size);
    printf ("capacity = %lu\n", stk->capacity);
    printf ("data [%p]:\n", stk->data);

    if (stk->data == NULL) 
        printf ("Pointer is NULL, because of this, the elements were not found\n");
    else 
    {
        printf ("{\n");
        printf (" CANARY_LEFT = %lf\n", stk->data[0]);
        for (int i = 1; i < (int) stk->capacity + 1; i++)
        {
            if (i < (int) stk->size + 1)
                printf ("*[%d] = %lf\n", i, stk->data[i]);
            else
                printf (" [%d] = %lf\n", i, stk->data[i]);
        }
        printf (" CANARY_RIGHT = %lf\n", stk->data[stk->capacity + 1]);
        printf ("}\n");
    }
}
#endif