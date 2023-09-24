// Final Project Milestone 3
// Publication module
// File Publication.h
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SDDS_PUBLICATION_H_
#define SDDS_PUBLICATION_H_
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"
using namespace std;
namespace sdds {
   class Publication : public Streamable {
      char* m_title;
      char m_shelfID[SDDS_SHELF_ID_LEN+1];
      int m_membership;
      int m_libRef;
      Date m_date;
   public:
      Publication();
      Publication(const Publication& pub);
      Publication& operator=(const Publication& pub);
      ~Publication();
      virtual void set(int member_id);
      void setRef(int value);
      void resetDate();
      virtual char type()const;
      bool onLoan()const;
      Date checkoutDate()const;
      bool operator==(const char* title)const;
      operator const char* ()const;
      int getRef()const;
      bool conIO(ios& ios) const;
      ostream& write(ostream& os) const;
      istream& read(istream& is);
      operator bool() const;
   };
}
#endif // !SDDS_PUB_H_
