# How to Run the Food Ordering System

## Quick Start (Executable Already Compiled)

Since the executable `food_ordering_system.exe` is already compiled, you can run it directly:

### On Windows (Command Prompt or PowerShell):
```bash
.\food_ordering_system.exe
```

Or simply:
```bash
food_ordering_system.exe
```

## If You Need to Recompile

### Method 1: Using GCC directly
```bash
gcc -Wall -Wextra -std=c11 -o food_ordering_system.exe main.c menu.c order_queue.c order_history.c
```

### Method 2: Using Makefile (if you have make installed)
```bash
make
```

Then run:
```bash
.\food_ordering_system.exe
```

## Running the Program

1. **Open Command Prompt or PowerShell** in the project directory
2. **Run the executable**: `food_ordering_system.exe`
3. **Follow the menu prompts**:
   - Enter `1` to view the menu
   - Enter `2` to place an order
   - Enter `3` to view pending orders
   - Enter `4` to process an order
   - Enter `5` to view order history
   - Enter `6` to exit

## Example Session

```
============================================================
    ONLINE FOOD ORDERING SYSTEM
    Using Linked List, Queue, and Stack
============================================================

============================================================
MAIN MENU
============================================================
1. View Menu (Linked List)
2. Place Order (Add to Queue)
3. View Pending Orders (Queue)
4. Process Order (Dequeue & Push to History Stack)
5. View Order History (Stack - Recent First)
6. Exit
============================================================
Enter your choice: 1
```

## Troubleshooting

- **If the executable doesn't exist**: Recompile using the gcc command above
- **If you get permission errors**: Make sure you're in the correct directory
- **If you get "command not found"**: Make sure gcc is in your PATH

