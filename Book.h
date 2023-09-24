// Final Project Milestone 4
// Book module
// File Book.h
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SDDS_BOOK_H_
#define SDDS_BOOK_H_
#include "Publication.h"
namespace sdds {
   class Book : public Publication {
      char* m_authorName;
   public:
      Book();
      Book(const Book& book);
      Book& operator=(const Book& book);
      ~Book();
      std::ostream& write(std::ostream& os) const;
      std::istream& read(std::istream& is);
      operator bool() const;
      char type()const;
      void set(int member_id);
   };
}
#endif // !SDDS_BOOK_H_
