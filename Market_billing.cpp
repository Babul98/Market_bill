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

            ofstream out("C:\\Users\\kbhag\\Desktop\\movieapp\\oops project\\Bill.txt", ios::app); // Corrected file path
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
    ifstream in("C:\\Users\\kbhag\\Desktop\\movieapp\\oops project\\Bill.txt"); // Corrected file path

    if (!in)
    {
        cout << "\tError: File Can't Open!" << endl;
    }
    else
    {
        cout << "\t---- Bill Summary ----" << endl;
        string line;
        while (getline(in, line))
        {
            cout << line << endl;
        }
        in.close();
    }
    Sleep(3000);
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

        if (choice == 1)
        {
            addItem(b);
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
