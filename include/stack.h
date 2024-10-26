#ifndef STACK_H
#define STACK_H

typedef int StackElem_t;

struct stack_t
{
    StackElem_t* data;     // указатель на массив стэка
    size_t  size;          // последний элемент
    size_t  capacity;      // вместимость
};

enum error
{
    Stack_Little_Capacity     = 101,
    Stack_Pointer_Struct_NULL = 102,
    Stack_Pointer_Data_NULL   = 103,
    Stack_Capacity_Negative   = 104,
    Stack_Size_Negative       = 105,
    CANARY                    = 2147483640,
    Stack_CanaryLeft_Wrong    = 106,
    Stack_CanaryRight_Wrong   = 107,
    Stack_Is_Empty            = 108,
    Stack_Pop_Ok              = 109
};

void StackCtor (stack_t *stk, int capacity);
void StackPush (stack_t *stk, StackElem_t value);
int StackPop (stack_t *stk, StackElem_t *x);
void StackDump (stack_t *stk, FILE *file_output, const char* file, const int n_str);
void FreeStack (stack_t *stk);
int StackOK (stack_t *stk);
void StackASSERT (stack_t *stk);
const char* StackErrDescr (error stack_error);
void MyRealloc (stack_t *stk, double coef);
void Dump (stack_t *stk, const char* name_file, const int n_str);


#endif


