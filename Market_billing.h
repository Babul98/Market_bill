#pragma once
#include <chrono> 
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

// Clear Macro
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class Bill {
private:
  string Item;
  int Rate, Quantity;

public:
  Bill() : Item(""), Rate(0), Quantity(0) {}

  void setItem(string item) { Item = item; }

  void listItems() {}

  void setRate(int rate) { Rate = rate; }

  void setQuantity(int quantity) { Quantity = quantity; }

  string getItem() const { return Item; }

  int getRate() const { return Rate; }

  int getQuantity() const { return Quantity; }
};
