#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Create a new menu list
MenuList* create_menu() {
    MenuList* menu = (MenuList*)malloc(sizeof(MenuList));
    if (menu == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    menu->head = NULL;
    menu->size = 0;
    return menu;
}

// Add a new menu item to the end of the linked list
void add_menu_item(MenuList* menu, int item_id, const char* name, const char* description, float price) {
    // Validate inputs
    if (menu == NULL) {
        printf("Error: Menu is NULL!\n");
        return;
    }
    
    // Check for duplicate item_id
    if (find_menu_item(menu, item_id) != NULL) {
        printf("Error: Menu item with ID %d already exists!\n", item_id);
        return;
    }
    
    // Validate price
    if (price <= 0) {
        printf("Error: Price must be greater than 0!\n");
        return;
    }
    
    MenuItem* new_item = (MenuItem*)malloc(sizeof(MenuItem));
    if (new_item == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    new_item->item_id = item_id;
    strncpy(new_item->name, name, sizeof(new_item->name) - 1);
    new_item->name[sizeof(new_item->name) - 1] = '\0';
    strncpy(new_item->description, description, sizeof(new_item->description) - 1);
    new_item->description[sizeof(new_item->description) - 1] = '\0';
    new_item->price = price;
    new_item->next = NULL;
    
    if (menu->head == NULL) {
        menu->head = new_item;
    } else {
        MenuItem* current = menu->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_item;
    }
    
    menu->size++;
    printf("Menu item added successfully!\n");
}

// Remove a menu item by ID
int remove_menu_item(MenuList* menu, int item_id) {
    if (menu->head == NULL) {
        return 0;
    }
    
    if (menu->head->item_id == item_id) {
        MenuItem* temp = menu->head;
        menu->head = menu->head->next;
        free(temp);
        menu->size--;
        return 1;
    }
    
    MenuItem* current = menu->head;
    while (current->next != NULL) {
        if (current->next->item_id == item_id) {
            MenuItem* temp = current->next;
            current->next = current->next->next;
            free(temp);
            menu->size--;
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

// Find a menu item by ID
MenuItem* find_menu_item(MenuList* menu, int item_id) {
    MenuItem* current = menu->head;
    while (current != NULL) {
        if (current->item_id == item_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Display all menu items
void display_menu(MenuList* menu) {
    if (menu->head == NULL) {
        printf("\nMenu is empty!\n\n");
        return;
    }
    
    printf("\n");
    printf("============================================================\n");
    printf("MENU\n");
    printf("============================================================\n");
    printf("%-5s %-20s %-25s %-10s\n", "ID", "Name", "Description", "Price");
    printf("------------------------------------------------------------\n");
    
    MenuItem* current = menu->head;
    while (current != NULL) {
        printf("%-5d %-20s %-25s $%-9.2f\n", 
               current->item_id, 
               current->name, 
               current->description, 
               current->price);
        current = current->next;
    }
    
    printf("============================================================\n\n");
}

// Free all memory allocated for the menu
void free_menu(MenuList* menu) {
    if (menu == NULL) {
        return;
    }
    
    MenuItem* current = menu->head;
    while (current != NULL) {
        MenuItem* temp = current;
        current = current->next;
        free(temp);
    }
    free(menu);
}

