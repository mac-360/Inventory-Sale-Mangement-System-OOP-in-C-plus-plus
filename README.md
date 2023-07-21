# Inventory-Sale-Mangement-System-OOP-in-C-plus-plus
**Inventory Management System**

**Overview:**
The Inventory Management System is a simple command-line application written in C++ that helps manage a store's inventory, credits, and sales records. The program reads and writes data from/to text files and allows users to perform various tasks, such as adding new items to the inventory, updating item quantities, recording sales, and tracking customer credits.

**Features:**
1. Add new items to the inventory.
2. Update the quantity of items in the inventory.
3. Record a sale and update the inventory accordingly.
4. Track customer credit accounts.
5. View the current items in the inventory.
6. View the recorded sales transactions.
7. View the customer credit details.

**File Structure:**
- `main.cpp`: Contains the main function to run the program.
- `Inventory.h` and `Inventory.cpp`: Define the Inventory class, which represents the store's inventory and manages related operations.
- `Credit.h` and `Credit.cpp`: Define the Credit class, which handles customer credit operations.
- `Sale.h` and `Sale.cpp`: Define the Sale class, which manages sales transactions and updates inventory accordingly.
- `Utils.h` and `Utils.cpp`: Provide utility functions for file handling and other tasks.

**Data Files:**
The program reads and writes data from/to the following text files:
1. `Inventory.txt`: Stores the inventory data.
2. `Credit.txt`: Keeps track of customer credit details.
3. `Sales.txt`: Records the sales transactions.

**Compilation and Execution:**
To compile the program, use a C++ compiler such as `g++`:
```
g++ main.cpp Inventory.cpp Credit.cpp Sale.cpp Utils.cpp -o InventoryManagementSystem
```

To execute the program:
```
./InventoryManagementSystem
```

**Usage:**
Upon running the program, the user is presented with a menu of options to choose from. Each option corresponds to a specific task or information the user can access.

**Sample Usage:**
```
Welcome to the Inventory Management System!
--------------------------------------------
1. Add new item to the inventory
2. Update item quantity
3. Record a sale
4. View inventory items
5. View sales transactions
6. View customer credits
0. Exit

Enter your choice: 3

--- Recording a Sale ---
Date: 2023-07-21
Customer Name: John Doe
Item: Widget-A
Quantity: 10

Sale recorded successfully!

Enter your choice: 5

--- Sales Transactions ---
Date       | Customer Name | Item       | Quantity
2023-07-21 | John Doe      | Widget-A   | 10
...

Enter your choice: 0

Exiting the Inventory Management System. Goodbye!
```

**Note:**
This is a simplified inventory management system and may not be suitable for large-scale or production use. Additional features like data validation, error handling, and security measures should be implemented for real-world applications.
