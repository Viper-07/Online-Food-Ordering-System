#ifndef ORDER_HISTORY_H
#define ORDER_HISTORY_H

#include "order_queue.h"

// Order History Stack structure
typedef struct {
    Order** orders;
    int top;
    int capacity;
} OrderHistoryStack;

// Function declarations
OrderHistoryStack* create_history_stack(int capacity);
void push_order(OrderHistoryStack* stack, Order* order);
Order* pop_order(OrderHistoryStack* stack);
Order* peek_history(OrderHistoryStack* stack);
int is_stack_empty(OrderHistoryStack* stack);
int is_stack_full(OrderHistoryStack* stack);
void display_order_history(OrderHistoryStack* stack);
void free_history_stack(OrderHistoryStack* stack);

#endif

