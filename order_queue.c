#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order_queue.h"

// Create a new order queue
OrderQueue* create_order_queue() {
    OrderQueue* queue = (OrderQueue*)malloc(sizeof(OrderQueue));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// Create a new order
Order* create_order(int order_id, const char* customer_name, OrderItem* items, int item_count, float total_amount) {
    Order* order = (Order*)malloc(sizeof(Order));
    if (order == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    order->order_id = order_id;
    strncpy(order->customer_name, customer_name, sizeof(order->customer_name) - 1);
    order->customer_name[sizeof(order->customer_name) - 1] = '\0';
    order->item_count = item_count;
    order->total_amount = total_amount;
    order->next = NULL;
    
    // Allocate memory for items array
    order->items = (OrderItem*)malloc(sizeof(OrderItem) * item_count);
    if (order->items == NULL) {
        printf("Memory allocation failed!\n");
        free(order);
        return NULL;
    }
    
    // Copy items
    for (int i = 0; i < item_count; i++) {
        strncpy(order->items[i].item_name, items[i].item_name, sizeof(order->items[i].item_name) - 1);
        order->items[i].item_name[sizeof(order->items[i].item_name) - 1] = '\0';
        order->items[i].quantity = items[i].quantity;
        order->items[i].price = items[i].price;
    }
    
    return order;
}

// Add an order to the rear of the queue
void enqueue_order(OrderQueue* queue, Order* order) {
    if (queue == NULL) {
        printf("Error: Queue is NULL!\n");
        return;
    }
    
    if (order == NULL) {
        printf("Error: Cannot enqueue NULL order!\n");
        return;
    }
    
    if (queue->rear == NULL) {
        queue->front = order;
        queue->rear = order;
    } else {
        queue->rear->next = order;
        queue->rear = order;
    }
    queue->size++;
}

// Remove and return the order from the front of the queue
Order* dequeue_order(OrderQueue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    
    Order* order = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    queue->size--;
    return order;
}

// View the front order without removing it
Order* peek_order(OrderQueue* queue) {
    return queue->front;
}

// Check if the queue is empty
int is_queue_empty(OrderQueue* queue) {
    return queue->front == NULL;
}

// Display all orders in the queue
void display_order_queue(OrderQueue* queue) {
    if (is_queue_empty(queue)) {
        printf("\nNo pending orders!\n\n");
        return;
    }
    
    printf("\n");
    printf("============================================================\n");
    printf("PENDING ORDERS (Queue)\n");
    printf("============================================================\n");
    
    Order* current = queue->front;
    int position = 1;
    while (current != NULL) {
        printf("%d. Order #%d | Customer: %s | Total: $%.2f\n", 
               position, current->order_id, current->customer_name, current->total_amount);
        printf("   Items: ");
        for (int i = 0; i < current->item_count; i++) {
            printf("%s x%d", current->items[i].item_name, current->items[i].quantity);
            if (i < current->item_count - 1) printf(", ");
        }
        printf("\n");
        current = current->next;
        position++;
    }
    
    printf("============================================================\n\n");
}

// Free an order
void free_order(Order* order) {
    if (order != NULL) {
        if (order->items != NULL) {
            free(order->items);
        }
        free(order);
    }
}

// Free all memory allocated for the queue
void free_order_queue(OrderQueue* queue) {
    if (queue == NULL) {
        return;
    }
    
    while (!is_queue_empty(queue)) {
        Order* order = dequeue_order(queue);
        free_order(order);
    }
    free(queue);
}

