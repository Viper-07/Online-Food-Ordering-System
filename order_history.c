#include <stdio.h>
#include <stdlib.h>
#include "order_history.h"

// Create a new order history stack
OrderHistoryStack* create_history_stack(int capacity) {
    OrderHistoryStack* stack = (OrderHistoryStack*)malloc(sizeof(OrderHistoryStack));
    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    stack->orders = (Order**)malloc(sizeof(Order*) * capacity);
    if (stack->orders == NULL) {
        printf("Memory allocation failed!\n");
        free(stack);
        return NULL;
    }
    
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Push an order onto the stack (recent orders first)
void push_order(OrderHistoryStack* stack, Order* order) {
    if (stack == NULL) {
        printf("Error: Stack is NULL!\n");
        return;
    }
    
    if (order == NULL) {
        printf("Error: Cannot push NULL order!\n");
        return;
    }
    
    if (is_stack_full(stack)) {
        // Remove oldest order (at bottom) and shift
        free_order(stack->orders[0]);
        for (int i = 0; i < stack->top; i++) {
            stack->orders[i] = stack->orders[i + 1];
        }
        stack->top--;
    }
    
    stack->top++;
    stack->orders[stack->top] = order;
}

// Pop an order from the stack
Order* pop_order(OrderHistoryStack* stack) {
    if (is_stack_empty(stack)) {
        return NULL;
    }
    
    Order* order = stack->orders[stack->top];
    stack->top--;
    return order;
}

// Peek at the top order without removing it
Order* peek_history(OrderHistoryStack* stack) {
    if (is_stack_empty(stack)) {
        return NULL;
    }
    return stack->orders[stack->top];
}

// Check if the stack is empty
int is_stack_empty(OrderHistoryStack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
int is_stack_full(OrderHistoryStack* stack) {
    return stack->top == stack->capacity - 1;
}

// Display order history (recent first)
void display_order_history(OrderHistoryStack* stack) {
    if (is_stack_empty(stack)) {
        printf("\nNo order history!\n\n");
        return;
    }
    
    printf("\n");
    printf("============================================================\n");
    printf("ORDER HISTORY (Stack - Recent First)\n");
    printf("============================================================\n");
    
    // Display from top to bottom (most recent first)
    for (int i = stack->top; i >= 0; i--) {
        Order* order = stack->orders[i];
        printf("%d. Order #%d | Customer: %s | Total: $%.2f\n", 
               stack->top - i + 1, order->order_id, order->customer_name, order->total_amount);
        printf("   Items: ");
        for (int j = 0; j < order->item_count; j++) {
            printf("%s x%d", order->items[j].item_name, order->items[j].quantity);
            if (j < order->item_count - 1) printf(", ");
        }
        printf("\n");
    }
    
    printf("============================================================\n\n");
}

// Free all memory allocated for the stack
void free_history_stack(OrderHistoryStack* stack) {
    if (stack != NULL) {
        for (int i = 0; i <= stack->top; i++) {
            free_order(stack->orders[i]);
        }
        free(stack->orders);
        free(stack);
    }
}

