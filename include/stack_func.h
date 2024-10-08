#ifndef StackCtor_H
#define StackCtor_H

#include "stack.h"

void StackCtor (stack_t *stk, int capacity);
void StackPush (stack_t *stk, StackElem_t value);
void StackPop (stack_t *stk, StackElem_t *x);
void StackDump (stack_t *stk, FILE *file_output, const char* file, const int n_str);
void FreeStack (stack_t *stk);
int StackOK (stack_t *stk);
void StackASSERT (stack_t *stk);
const char* StackErrDescr (error stack_error);

#endif 