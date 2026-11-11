#include <stdio.h>
#define SIZE 5

/* Improved version: push/pop return a status (1 = success, 0 = failure),
   and pop hands the value back through a pointer, so a stored -1 can no
   longer be confused with the "underflow" error value. */
int stack[SIZE];
int top = -1;

int push(int item)
{
    if (top == SIZE - 1) { printf("Stack Overflow\n"); return 0; }
    stack[++top] = item;
    printf("Pushed: %d\n", item);
    return 1;
}

int pop(int *item)
{
    if (top == -1) { printf("Stack Underflow\n"); return 0; }
    *item = stack[top--];
    return 1;
}

void display(void)
{
    int i;
    if (top == -1) { printf("Stack is Empty\n"); return; }
    printf("Stack:");
    for (i = 0; i <= top; i++) printf(" %d", stack[i]);
    printf("\n");
}

int main(void)
{
    int item;
    push(-1);
    if (pop(&item)) printf("Popped: %d\n", item);   /* prints Popped: -1 (a real value) */
    if (pop(&item)) printf("Popped: %d\n", item);   /* prints Stack Underflow only      */
    display();
    return 0;
}
