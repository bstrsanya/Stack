#ifndef STACK_H
#define STACK_H

typedef int StackElem_t;

struct stack_t
{
    StackElem_t* data;     // указатель на массив стэка
    int  size;     // последний элемент
    int  capacity; // вместимость
};

#endif
