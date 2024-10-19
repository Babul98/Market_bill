#include "Market_billing.h"

void listItems() {
  system(CLEAR);
  ifstream in("Bill.txt");

  if (!in) {
    cout << "+---------------------------------------+" << endl;
    cout << "|       No items found.                 |" << endl;
    cout << "+---------------------------------------+" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return;
  }

  string line;
  cout << "+-------------------------+" << endl;
  cout << "| Item     | Rate | Qty   |" << endl;
  cout << "+-------------------------+" << endl;

  while (getline(in, line)) {
    stringstream ss(line);
    string itemName;
    int itemRate, itemQuant;
    char delimiter;

    ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;
    cout << "| " << left << setw(8) << itemName
         << "| " << setw(4) << itemRate
         << "| " << setw(4) << itemQuant << "    |" << endl;
  }

  in.close();
  cout << "+-------------------------+" << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void addItem(Bill &b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "+---------------------------------------+" << endl;
        cout << "|                 Menu                  |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "| 1. ADD                                |" << endl;
        cout << "| 2. Close                              |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        // Clear input buffer if invalid
        if (cin.fail())
        {
            cout << RED << "\tInvalid choice, please enter a number." <<  RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1)
        {
            system(CLEAR);
            string item;
            int rate;
            int quantity;

            cout << "\tEnter Name Of Item: ";
            cin.ignore();  // To clear the newline character from previous input
            getline(cin, item);  // Using getline to handle spaces in item names
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            while (cin.fail())
            {
                cout << RED << "\tInvalid input, please enter a number for rate: " << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> rate;
            }
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quantity;
            while (cin.fail())
            {
                cout << RED << "\tInvalid input, please enter a number for quantity: " << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> quantity;
            }
            b.setQuantity(quantity);

            ofstream out("Bill.txt", ios::app);
            if (!out)
            {
                cout << RED << "\tError: File Can't Open!" << RESET << endl;
            }
            else
            {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl;
                out.close();
                cout << GREEN << "\tItem added successfully." << RESET << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        else if (choice == 2)
        {
            system(CLEAR);
            close = true;
            cout << "\tClosing..." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void printBill() {
    system(CLEAR);
    int count = 0;
    bool close = false;

    while (!close) {
        int choice;
        cout << "+---------------------------------------+" << endl;
        cout << "|           Print Bill Menu             |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "| 1. Add item to bill                   |" << endl;
        cout << "| 2. Close and print total bill         |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "| Enter Choice: ";
        cin >> choice;

        // Clear input buffer if invalid
        if (cin.fail()) {
            cout << RED << "\tInvalid choice, please enter a number." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter item: ";
            cin.ignore();  // To clear the newline character from previous input
            getline(cin, item);

            while (true) { // Loop until a valid quantity is entered
                cout << "\tEnter Quantity: ";
                cin >> quant;
                while (cin.fail()) {
                    cout << RED << "\tInvalid input, please enter a number for quantity: " << RESET;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tEnter Quantity: ";
                    cin >> quant;
                }

                // Check available quantity
                ifstream in("Bill.txt");
                string line;
                bool found = false;
                int itemQuant = 0;  // Declare itemQuant here
                while (getline(in, line)) {
                    stringstream ss(line);
                    string itemName;
                    int itemRate;
                    char delimiter;

                    ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                    if (item == itemName) {
                        found = true;
                        if (quant <= itemQuant) {
                            int amt = itemRate * quant;
                            cout << "+---------------------------------------+" << endl;
                            cout << "| Item | Rate | Quantity | Amount       |" << endl;
                            cout << "+---------------------------------------+" << endl;
                            cout << "| " << left << setw(8) << itemName
                                 << "| " << setw(4) << itemRate
                                 << "| " << setw(4) << quant
                                 << "| " << setw(9) << amt << " |" << endl;
                            int newQuant = itemQuant - quant;
                            count += amt;

                            // Update the item quantity in the file
                            ofstream out("temp.txt");
                            in.clear();
                            in.seekg(0, ios::beg); // Reset the file pointer to the beginning
                            while (getline(in, line)) {
                                if (item == itemName) {
                                    out << itemName << " : " << itemRate << " : " << newQuant << endl;
                                } else {
                                    out << line << endl;
                                }
                            }
                            out.close();
                        } else {
                            cout << RED << "\tSorry, only " << itemQuant << " of " << item << " available." << RESET << endl;
                        }
                        break;
                    }
                }
                in.close();
                if (!found) {
                    cout << RED << "\tItem not available." << RESET << endl;
                }
                if (found && quant <= itemQuant) {
                    break;
                }
            }
        } else if (choice == 2) {
            close = true;
            cout << YELLOW << "\tCounting Total Bill..." << RESET << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            system(CLEAR);
            cout << "+---------------------------------------+" << endl;
            cout << "| Total Bill: " << count << "                    |" << endl;
            cout << "+---------------------------------------+" << endl;
            cout << "| Thanks for shopping!                  |" << endl;
            cout << "+---------------------------------------+" << endl;

            cout << "\tPress Enter to continue...";
            cin.ignore();
            cin.get();
        } else {
            cout << RED << "\tInvalid choice, please try again." << RESET << endl;
        }
    }
}

void displayMainMenu() {
    cout << "+----------------------------------------+" << endl;
    cout << "| Welcome To Super Market Billing System |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "| 1. Add Item                            |" << endl;
    cout << "| 2. Print Bill                          |" << endl;
    cout << "| 3. List Items                          |" << endl;
    cout << "| 4. Exit                                |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "| Enter Choice: ";
}

int main()
{
    Bill b;
    bool exit = false;

    while (!exit) {
        system(CLEAR);
        displayMainMenu();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cout << RED << "\tInvalid choice, please enter a number." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                system(CLEAR);
                addItem(b);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
            case 2:
                printBill();
                break;
            case 3:
                listItems();
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get(); 
                break; 
            case 4:
                system(CLEAR);
                exit = true;
                cout << CYAN << "\tExiting..." << RESET << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
            default:
                cout << RED << "\tInvalid choice, please try again." << RESET << endl;
                break;
        }
    }

    return 0;
}
