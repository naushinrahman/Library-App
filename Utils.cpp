/***********************************************************************
// OOP244 Utils Module
// File	Utils.cpp
// Version 1.0
// Date 07/22/2023
// Author Naushin Rahman
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <limits>
#include <iostream>
#include <cstring>
#include "Utils.h"
using namespace std;
namespace sdds {

   int getIntInput(int min, int max) {
      int value;
      bool isValid = false;
      while (!isValid) {
         if (!(cin >> value)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Selection, try again: ";
         }
         else if (value < min || value > max) {
            cout << "Invalid Selection, try again: ";
         }
         else {
            isValid = true;
         }
      }
      return value;
   }
}