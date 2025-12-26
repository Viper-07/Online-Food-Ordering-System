# Online Food Ordering System

A C programming implementation of an Online Food Ordering System using multiple data structures:
- **Menu**: Implemented using Linked List
- **Orders**: Implemented using Queue (FIFO)
- **Order History**: Implemented using Stack (Recent First)

## Features

1. **Menu Management (Linked List)**
   - View all menu items
   - Add menu items
   - Remove menu items
   - Find menu items by ID

2. **Order Management (Queue)**
   - Place new orders (enqueue)
   - View pending orders
   - Process orders (dequeue)

3. **Order History (Stack)**
   - View order history with most recent orders first
   - Automatic history management

## Compilation

### Using Makefile (Recommended)
```bash
make
```

### Manual Compilation
```bash
gcc -Wall -Wextra -std=c11 -o food_ordering_system main.c menu.c order_queue.c order_history.c
```

## Running the Program

```bash
./food_ordering_system
```

On Windows:
```bash
food_ordering_system.exe
```

## Usage

The program provides an interactive menu with the following options:

1. **View Menu (Linked List)** - Display all available menu items
2. **Place Order (Add to Queue)** - Create a new order and add it to the queue
3. **View Pending Orders (Queue)** - Display all orders waiting to be processed
4. **Process Order (Dequeue & Push to History Stack)** - Process the next order and add it to history
5. **View Order History (Stack - Recent First)** - Display order history with most recent orders first
6. **Exit** - Exit the program

## Data Structures Used

### Linked List (Menu)
- Dynamic size
- Efficient insertion and deletion
- Sequential access

### Queue (Orders)
- First-In-First-Out (FIFO) processing
- Efficient enqueue and dequeue operations
- Maintains order of arrival

### Stack (Order History)
- Last-In-First-Out (LIFO) for recent-first display
- Efficient push and pop operations
- Recent orders appear first

## File Structure

```
.
├── main.c              - Main program with user interface
├── menu.h              - Menu linked list header
├── menu.c              - Menu linked list implementation
├── order_queue.h       - Order queue header
├── order_queue.c       - Order queue implementation
├── order_history.h     - Order history stack header
├── order_history.c     - Order history stack implementation
├── Makefile            - Build configuration
└── README.md           - This file
```

## Example Usage Flow

1. Start the program
2. View the menu to see available items
3. Place an order by selecting items and quantities
4. View pending orders to see orders in queue
5. Process orders one by one (they move to history)
6. View order history to see processed orders (most recent first)

## Clean Up

To remove compiled files:
```bash
make clean
```

## Notes

- The program initializes with default menu items
- Order history has a maximum capacity (100 orders by default)
- When history is full, oldest orders are automatically removed
- All memory is properly managed and freed on exit

