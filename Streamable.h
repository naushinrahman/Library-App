// Final Project Milestone 3
// Streamable Interface
// File Streamable.h
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_
#include <iostream>
using namespace std;
namespace sdds {
   class Streamable {
      virtual ostream& write(ostream& os) const = 0;
      virtual istream& read(istream& is) = 0;
      virtual bool conIO(ios& ios) const = 0;
      virtual operator bool() const = 0;
   public:
      virtual ~Streamable();
      friend istream& operator>>(istream& is, Streamable& stream);
      friend ostream& operator<<(ostream& os, const Streamable& stream);
   };
}

#endif // !SDDS_STREAMABLE_H_
