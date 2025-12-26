#ifndef ORDER_QUEUE_H
#define ORDER_QUEUE_H

// Order Item structure
typedef struct OrderItem {
    char item_name[100];
    int quantity;
    float price;
} OrderItem;

// Order structure
typedef struct Order {
    int order_id;
    char customer_name[100];
    OrderItem* items;
    int item_count;
    float total_amount;
    struct Order* next;
} Order;

// Order Queue structure
typedef struct {
    Order* front;
    Order* rear;
    int size;
} OrderQueue;

// Function declarations
OrderQueue* create_order_queue();
void enqueue_order(OrderQueue* queue, Order* order);
Order* dequeue_order(OrderQueue* queue);
Order* peek_order(OrderQueue* queue);
int is_queue_empty(OrderQueue* queue);
void display_order_queue(OrderQueue* queue);
void free_order_queue(OrderQueue* queue);
Order* create_order(int order_id, const char* customer_name, OrderItem* items, int item_count, float total_amount);
void free_order(Order* order);

#endif

