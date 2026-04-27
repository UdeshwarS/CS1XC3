#ifndef STACK_H
#define STACK_H

int isEmpty(const long *start, const long *end);
void push(long **start, long **end, long value);
long pop(long **start, long **end);
void print_stack(const long *start, const long *end);

#endif