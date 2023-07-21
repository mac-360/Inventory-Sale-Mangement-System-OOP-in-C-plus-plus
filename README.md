# *Inventory Management System*

## *Overview:*
The Inventory Management System is a simple command-line application written in C++ that helps manage a store's inventory, credits, and sales records. The program reads and writes data from/to text files and allows users to perform various tasks, such as adding new items to the inventory, updating item quantities, recording sales, and tracking customer credits.

## *Features:*
1. Add new items to the inventory.
2. Update the quantity of items in the inventory.
3. Record a sale and update the inventory accordingly.
4. Track customer credit accounts.
5. View the current items in the inventory.
6. View the recorded sales transactions.
7. View the customer credit details.

## *File Structure:*
- `main.cpp`: Contains the main function to run the program.
- `Products.h`: This Header file contains all the methods to Add/Remove/update/Display Data from a file.
- `Ledger.h` : This Header File contains all the methods to Calculate Sales/Credit, Generate Bill etc.

## *Data Files:*
The program reads and writes data from/to the following text files:
1. `Inventory.txt`: Stores the inventory data.
2. `Credit.txt`: Keeps track of customer credit details.
3. `Sales.txt`: Records the sales transactions.

## *Compilation and Execution:*
To compile the program, add the following header and txt files 
`1. Ledger.h`  
`2. Products.h`  
`3. Source.cpp`  
`4. Sales.txt`  
`5. Credit.txt`  
`6. Inventory.txt`  

## *Note:*

```
Dummy Data for the txt files have been provided.
```

## *Usage:*
Upon running the program, the user is presented with a menu of options to choose from. Each option corresponds to a specific task or information the user can access.

## *Sample Usage:*
```
Press 1 for adding a new entry to the file:
Press 2 for removing an entry from the file:
Press 3 for updating an entry from the file:
Press 4 for displaying an entry from the file according to your search criteria:
Press 5 for displaying total sales done in a certain year/month/day:
Press 6 for displaying a certain consumer credit:
Press 7 for displaying the total credit:
Press 8 for adding a new sale:
Press 9 for checking if a person has credit account with you :
Press 10 to exit the program:
1
Enter the name of the product :GOOGLE_PIXEL_7A
Enter the Number of Items : 50
Enter the Type of Product: SMARTPHONE
Enter the Purchase Price of the Product: 550
Enter the Sale Price of the Product: 700
Record Added successfully
```

## *Note:*
This is a simplified inventory management system and may not be suitable for large-scale or production use. Additional features like data validation, error handling, and security measures should be implemented for real-world applications.

### If you have any inquiries or require further clarification regarding the code, please feel free to contact me via email at akhyach307@gmail.com or l227461@lhr.nu.edu.pk . Your valuable feedback concerning this matter would be highly appreciated. Thank you for your kind attention and assistance.
