// Final Project Milestone 1 
// Menu Module
// File Menu.h
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#define MAX_MENU_ITEMS 20
#include <iostream>
namespace sdds {
   class Menu;
   class MenuItem {
      char* m_item;
      MenuItem();
      MenuItem(const char* item);
      MenuItem(const MenuItem& MI) = delete;
      MenuItem& operator=(const MenuItem& MI) = delete;
      ~MenuItem();
      std::ostream& displayItem(std::ostream& os = std::cout)const;
      operator bool()const;
      const char* item()const;
      friend class Menu;
   };

   class Menu {
   protected:
      MenuItem* m_title;
      MenuItem* m_menuItems[MAX_MENU_ITEMS] = {nullptr};
      int m_noOfMItems;
   public:
      Menu();
      Menu(const char* title);
      Menu(const Menu& menu) = delete;
      Menu& operator=(const Menu& menu) = delete;
      ~Menu();
      unsigned run()const;
      std::ostream& displayTitle(std::ostream& os = std::cout)const;
      std::ostream& displayMenu(std::ostream& os = std::cout)const;
      unsigned operator~()const;
      Menu& operator<<(const char* menuitemConent);
      const char* operator[](unsigned index)const;
      operator bool()const;
      operator int()const;
      operator unsigned()const;
      friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
   };
}
#endif // !SDDS_MENU_H_
