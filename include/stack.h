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
    Stack_Pointer_Stk_NULL    = 108
};


#endif


