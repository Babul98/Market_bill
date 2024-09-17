#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

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
        cout << "\t1.ADD." << endl;
        cout << "\t2.Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate;
            int quantity;

            cout << "\tEnter Item Name:  ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quantity;
            b.setQuantity(quantity);

            ofstream out("C:\\Users\\kbhag\\Desktop\\movieapp\\oops project\\Bill.txt", ios::app);
            // to append the data on the file ow we loose the data
            // assigning to the member varible
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                // for saving  to txt file
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl;
                out.close();
                cout << "\tItem added successfully." << endl;
                Sleep(2000);
                // screen should be displayed for 3 sec
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
        system("cls");

        int choice;
        cout << "\t1.ADD." << endl;
        cout << "\t2.Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string item;
            int quant;
            cout << "\t Enter item:";
            cin >> item;
            cout << "\t Enter Quantity";
            cin >> quant;
            ifstream in("C:\\Users\\kbhag\\Desktop\\movieapp\\oops project\\Bill.txt");
            ofstream out("C:\\Users\\kbhag\\Desktop\\movieapp\\oops project\\temp.txt");

            string line;
            bool found = false;
            while (getline(in, line))
            {
                stringstream ss;
                ss << line;
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName)
                {
                    found = true;
                    if (quant == itemQuant)
                    {
                        int amt = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount  " << endl;
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << amt << endl;
                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        count += amt;
                        out << "\t" << itemName << " : " << itemRate << " : " << itemQuant << endl
                            << endl;
                    }
                    else
                    {
                        cout << "\t Sorry " << item << "Ended" << endl;
                    }
                }
                else
                {
                    out << line;
                    // save the old data in the file
                }
            }
            if (!found)
            {
                cout << "\t Item not Available" << endl;
            }
            out.close();
            in.close();
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
        // hide the previous output and shows the current output
        int choice;

        cout << "\t Welcome To Super Market Billing System" << endl;
        cout << "\t****************************************" << endl;
        cout << "\t\t1. Add Item" << endl;
        cout << "\t\t2. Print Bill" << endl;
        cout << "\t\t3. Exit" << endl;
        cout << "\t\tEnter Choice: ";
        cin >> choice;

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
            exit = true;
            cout << "\tExiting..." << endl;
            Sleep(2000);
        }
    }

    return 0;
}
