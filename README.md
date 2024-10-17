# Supermarket Billing System

A simple C++ console application that simulates a supermarket billing system. It allows users to add items, manage inventory, and calculate the total bill, using file handling for persistence.

## Features
Add Items: Add item name, rate, and quantity to the bill.
Print Bill: View a summary of purchased items and their total amount.
Persistent Storage: Saves items in a text file (Bill.txt) for continuous sessions.
Input Validation: Ensures only valid data is entered for rate and quantity.
Simple Menu Interface: A clear, interactive console-based system for user operations.

## How It Works
### Add Items:
Users can input item details like the name, rate, and quantity, which will be stored in Bill.txt. The system validates input to ensure correct data.

### Print Bill:
Users can generate a bill for selected items, specifying the quantity they wish to purchase. The system checks available inventory, updates the bill, and calculates the total.

### Exit:
The program allows users to exit at any time, with data stored in a file for later retrieval.
![image](https://github.com/user-attachments/assets/16644c40-adac-4ceb-841f-1d91fdc9e576)

## Project Structure
### Bill Class:
Stores details like item name, rate, and quantity.
Provides methods to set and get item properties.
### File Handling:
Uses Bill.txt to store and retrieve item data.
Utilizes a temporary file (temp.txt) to update the bill before renaming it back to Bill.txt.

## Technology Stack
Language: C++
Libraries Used:
<iostream> for basic input and output.
<fstream> for file handling (reading and writing to Bill.txt).
<sstream> for parsing strings.
<limits> for input validation.
<windows.h> for using Sleep() and clearing the console with system("cls").

## Getting Started
Prerequisites
A C++ compiler such as GCC or MinGW (for Windows).

Installation
Clone the repository:

git clone https://github.com/yourusername/supermarket-billing-system.git 

Compile the C++ program:

g++ -o billing_system main.cpp

Run the program:

./billing_system

## Future Enhancements
Improved Inventory Management: Load items dynamically from a database or external file at the start.
Additional Features: Add support for discounts, taxes, and multi-user management.
Advanced Reporting: Include features for tracking sales history and generating reports.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.




