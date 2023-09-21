// Final Project Milestone 3
// Streamable Interface
// File Streamable.cpp
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#include <iostream>
#include "Streamable.h"
using namespace std;
namespace sdds {
   istream& operator>>(istream& is, Streamable& stream) {
      return stream.read(is);
   }
   ostream& operator<<(ostream& os, const Streamable& stream) {
      if (stream) {
         stream.write(os);
      }
      return os;
   }
   Streamable::~Streamable() { }
}
