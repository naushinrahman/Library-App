// Final Project Milestone 2
// LibApp Module
// File LibApp.cpp
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SDDS_LIBAPP_H_
#define SDDS_LIBAPP_H_
#include "Lib.h"
#include "Date.h"
#include "Menu.h"
#include "Book.h"
#include "Utils.h"
#include "Publication.h"
#include "PublicationSelector.h"
namespace sdds {
   class LibApp : public Menu {
      bool m_changed = false;
      char m_fileName[256 + 1]{};
      int m_LLRN{};
      int m_NOLP{};
      Menu m_exitMenu;
      Menu m_mainMenu;
      Menu m_pubMenu;
      Publication* m_PPA[SDDS_LIBRARY_CAPACITY]{};
      bool confirm(const char* message);
      void load();  
      void save();  
      int search(int searchType);
      void returnPub(); 
      Publication* getPub(int libRef);
      void newPublication();
      void removePublication();
      void checkOutPub();
   public:
      LibApp(const char* filename);
      ~LibApp();
      void run();
   };
}
#endif // !SDDS_LIBAPP_H



