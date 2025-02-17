#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the stack

// Stack structure definition
struct Stack {
    int data[MAX]; // Array to store stack elements
    int top;       // Index to the top of the stack
};

// Function to initialize the stack
void initStack(struct Stack* stack) {
    stack->top = -1; // Set top to -1, indicating an empty stack
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    stack->data[++stack->top] = value; // Increment top and add the value
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! No element to pop.\n");
        return -1; // Return -1 if stack is empty
    }
    return stack->data[stack->top--]; // Return the top element and decrement top
}

void displayStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack contents (top to bottom): ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack; // Create a stack
    initStack(&stack);  // Initialize the stack

    // Push elements onto the stack
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    push(&stack, 50);
    push(&stack, 60);

    // Display the stack contents
    displayStack(&stack);

    return 0;
}
