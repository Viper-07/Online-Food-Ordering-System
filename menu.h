#ifndef MENU_H
#define MENU_H

// Menu Item structure
typedef struct MenuItem {
    int item_id;
    char name[100];
    char description[200];
    float price;
    struct MenuItem* next;
} MenuItem;

// Menu Linked List structure
typedef struct {
    MenuItem* head;
    int size;
} MenuList;

// Function declarations
MenuList* create_menu();
void add_menu_item(MenuList* menu, int item_id, const char* name, const char* description, float price);
int remove_menu_item(MenuList* menu, int item_id);
MenuItem* find_menu_item(MenuList* menu, int item_id);
void display_menu(MenuList* menu);
void free_menu(MenuList* menu);

#endif

