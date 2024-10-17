#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <limits>

using namespace std;

class Bill
{
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {} // constructor

    void setItem(string item)
    {
        Item = item;
    }

    void setRate(int rate)
    {
        Rate = rate;
    }

    void setQuantity(int quantity)
    {
        Quantity = quantity;
    }

    string getItem() const
    {
        return Item;
    }

    int getRate() const
    {
        return Rate;
    }

    int getQuantity() const
    {
        return Quantity;
    }
};

void addItem(Bill &b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. ADD." << endl;
        cout << "\t2. Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        // Clear input buffer if invalid
        if (cin.fail())
        {
            cout << "\tInvalid choice, please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate;
            int quantity;

            cout << "\tEnter Item Name:  ";
            cin.ignore();  // To clear the newline character from previous input
            getline(cin, item);  // Using getline to handle spaces in item names
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            while (cin.fail())
            {
                cout << "\tInvalid input, please enter a number for rate: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> rate;
            }
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quantity;
            while (cin.fail())
            {
                cout << "\tInvalid input, please enter a number for quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> quantity;
            }
            b.setQuantity(quantity);

            ofstream out("Bill.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl;
                out.close();
                cout << "\tItem added successfully." << endl;
                Sleep(2000);
            }
        }
        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tClosing..." << endl;
            Sleep(2000);
        }
    }
}

void printBill()
{
    system("cls");

    int count = 0;
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add item to bill" << endl;
        cout << "\t2. Close and print total bill" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        // Clear input buffer if invalid
        if (cin.fail())
        {
            cout << "\tInvalid choice, please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1)
        {
            string item;
            int quant;
            cout << "\tEnter item: ";
            cin.ignore();  // To clear the newline character from previous input
            getline(cin, item);
            cout << "\tEnter Quantity: ";
            cin >> quant;
            while (cin.fail())
            {
                cout << "\tInvalid input, please enter a number for quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> quant;
            }

            ifstream in("Bill.txt");
            ofstream out("temp.txt");

            string line;
            bool found = false;
            while (getline(in, line))
            {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimiter;

                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName)
                {
                    found = true;
                    if (quant <= itemQuant)
                    {
                        int amt = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount  " << endl;
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amt << endl;
                        int newQuant = itemQuant - quant;
                        count += amt;
                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    }
                    else
                    {
                        cout << "\t Sorry, only " << itemQuant << " of " << item << " available." << endl;
                        out << line << endl;
                    }
                }
                else
                {
                    out << line << endl;
                }
            }

            if (!found)
            {
                cout << "\t Item not available." << endl;
            }

            out.close();
            in.close();

            remove("Bill.txt");
            rename("temp.txt", "Bill.txt");
        }
        else if (choice == 2)
        {
            close = true;
            cout << "\t Counting Total Bill..." << endl;
            Sleep(3000);
            system("cls");
            cout << "\t Total Bill -------------------------- " << count << endl
                 << endl;
            cout << "\t Thanks for shopping!" << endl;
            Sleep(5000);
        }
        else
        {
            cout << "\tInvalid choice, please try again." << endl;
        }
    }
}

int main()
{
    Bill b;
    bool exit = false;

    while (!exit)
    {
        system("cls");
        int choice;

        cout << "\t Welcome To Super Market Billing System" << endl;
        cout << "\t****************************************" << endl;
        cout << "\t\t1. Add Item" << endl;
        cout << "\t\t2. Print Bill" << endl;
        cout << "\t\t3. Exit" << endl;
        cout << "\t\tEnter Choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cout << "\tInvalid choice, please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1)
        {
            system("cls");
            addItem(b);
            Sleep(2000);
        }
        else if (choice == 2)
        {
            printBill();
        }
        else if (choice == 3)
        {
            system("cls");
            exit = true;
            cout << "\tExiting..." << endl;
            cout << "\t Good Luck!" << endl;
            Sleep(2000);
        }
    }

    return 0;
}
