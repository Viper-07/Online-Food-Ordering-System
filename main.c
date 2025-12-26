#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "order_queue.h"
#include "order_history.h"

#define MAX_HISTORY 100

// Function prototypes
void print_menu();
void initialize_default_menu(MenuList* menu);
void place_order(MenuList* menu, OrderQueue* queue, int* order_counter);
void process_order(OrderQueue* queue, OrderHistoryStack* history);
void view_menu(MenuList* menu);
void view_pending_orders(OrderQueue* queue);
void view_order_history(OrderHistoryStack* history);

int main() {
    MenuList* menu = create_menu();
    OrderQueue* order_queue = create_order_queue();
    OrderHistoryStack* history = create_history_stack(MAX_HISTORY);
    int order_counter = 1;
    int choice;
    
    // Check for memory allocation failures
    if (menu == NULL || order_queue == NULL || history == NULL) {
        printf("Error: Failed to initialize system. Exiting...\n");
        if (menu != NULL) free_menu(menu);
        if (order_queue != NULL) free_order_queue(order_queue);
        if (history != NULL) free_history_stack(history);
        return 1;
    }
    
    // Initialize with some default menu items
    initialize_default_menu(menu);
    
    printf("============================================================\n");
    printf("    ONLINE FOOD ORDERING SYSTEM\n");
    printf("    Using Linked List, Queue, and Stack\n");
    printf("============================================================\n");
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        getchar(); // Consume newline
        
        switch (choice) {
            case 1:
                view_menu(menu);
                break;
            case 2:
                place_order(menu, order_queue, &order_counter);
                break;
            case 3:
                view_pending_orders(order_queue);
                break;
            case 4:
                process_order(order_queue, history);
                break;
            case 5:
                view_order_history(history);
                break;
            case 6:
                printf("\nThank you for using the Online Food Ordering System!\n");
                free_menu(menu);
                free_order_queue(order_queue);
                free_history_stack(history);
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n\n");
        }
    }
    
    return 0;
}

void print_menu() {
    printf("\n");
    printf("============================================================\n");
    printf("MAIN MENU\n");
    printf("============================================================\n");
    printf("1. View Menu (Linked List)\n");
    printf("2. Place Order (Add to Queue)\n");
    printf("3. View Pending Orders (Queue)\n");
    printf("4. Process Order (Dequeue & Push to History Stack)\n");
    printf("5. View Order History (Stack - Recent First)\n");
    printf("6. Exit\n");
    printf("============================================================\n");
}

void initialize_default_menu(MenuList* menu) {
    add_menu_item(menu, 1, "Burger", "Classic beef burger", 8.99f);
    add_menu_item(menu, 2, "Pizza", "Margherita pizza", 12.99f);
    add_menu_item(menu, 3, "Pasta", "Spaghetti carbonara", 10.99f);
    add_menu_item(menu, 4, "Salad", "Caesar salad", 7.99f);
    add_menu_item(menu, 5, "Soup", "Tomato soup", 5.99f);
    add_menu_item(menu, 6, "Sandwich", "Grilled chicken sandwich", 9.99f);
    add_menu_item(menu, 7, "Fries", "French fries", 4.99f);
    add_menu_item(menu, 8, "Drink", "Soft drink", 2.99f);
}

void view_menu(MenuList* menu) {
    display_menu(menu);
}

void place_order(MenuList* menu, OrderQueue* queue, int* order_counter) {
    char customer_name[100];
    int item_id, quantity;
    OrderItem items[50];
    int item_count = 0;
    float total_amount = 0.0;
    char continue_order;
    
    printf("\n");
    printf("============================================================\n");
    printf("PLACE ORDER\n");
    printf("============================================================\n");
    
    display_menu(menu);
    
    printf("Enter customer name: ");
    if (fgets(customer_name, sizeof(customer_name), stdin) == NULL) {
        printf("Error reading customer name!\n");
        return;
    }
    customer_name[strcspn(customer_name, "\n")] = 0; // Remove newline
    
    // Validate customer name is not empty
    if (customer_name[0] == '\0') {
        printf("Customer name cannot be empty!\n");
        return;
    }
    
    do {
        printf("\nEnter item ID: ");
        if (scanf("%d", &item_id) != 1) {
            printf("Invalid input! Please enter a number.\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        getchar();
        
        MenuItem* menu_item = find_menu_item(menu, item_id);
        if (menu_item == NULL) {
            printf("Item not found! Please try again.\n");
            continue;
        }
        
        printf("Enter quantity: ");
        if (scanf("%d", &quantity) != 1) {
            printf("Invalid input! Please enter a number.\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        getchar();
        
        if (quantity <= 0) {
            printf("Invalid quantity! Please try again.\n");
            continue;
        }
        
        // Check array bounds
        if (item_count >= 50) {
            printf("Maximum 50 items per order! Order will be finalized.\n");
            break;
        }
        
        // Add to order items
        strncpy(items[item_count].item_name, menu_item->name, sizeof(items[item_count].item_name) - 1);
        items[item_count].item_name[sizeof(items[item_count].item_name) - 1] = '\0';
        items[item_count].quantity = quantity;
        items[item_count].price = menu_item->price;
        
        float item_total = menu_item->price * (float)quantity;
        total_amount += item_total;
        item_count++;
        
        printf("Added: %s x%d ($%.2f)\n", menu_item->name, quantity, item_total);
        
        printf("\nAdd more items? (y/n): ");
        if (scanf(" %c", &continue_order) != 1) {
            printf("Invalid input! Assuming 'n' (no).\n");
            continue_order = 'n';
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
    } while (continue_order == 'y' || continue_order == 'Y');
    
    if (item_count > 0) {
        Order* new_order = create_order(*order_counter, customer_name, items, item_count, total_amount);
        if (new_order == NULL) {
            printf("\nError: Failed to create order. Please try again.\n");
            return;
        }
        enqueue_order(queue, new_order);
        printf("\nOrder #%d placed successfully! Total: $%.2f\n", *order_counter, total_amount);
        (*order_counter)++;
    } else {
        printf("\nNo items added. Order cancelled.\n");
    }
}

void view_pending_orders(OrderQueue* queue) {
    display_order_queue(queue);
}

void process_order(OrderQueue* queue, OrderHistoryStack* history) {
    if (is_queue_empty(queue)) {
        printf("\nNo pending orders to process!\n\n");
        return;
    }
    
    Order* order = dequeue_order(queue);
    if (order != NULL) {
        push_order(history, order);
        printf("\nOrder #%d processed successfully!\n", order->order_id);
        printf("Order moved to history (stack).\n\n");
    }
}

void view_order_history(OrderHistoryStack* history) {
    display_order_history(history);
}

