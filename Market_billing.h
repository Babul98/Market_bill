#pragma once
#include <chrono> 
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <thread>

// Removing windows dependency for sleep and using threads
// for better waiting of process on any machine

using namespace std;

// Macro for clearing screen depending on system
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

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
