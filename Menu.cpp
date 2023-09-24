// Final Project Milestone 1 
// Menu Module
// File Menu.cpp
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include <cstring>
#include "Utils.h"
using namespace std;

namespace sdds {
   MenuItem::MenuItem() {
      m_item = nullptr;
   }
   MenuItem::MenuItem(const char* item) {
      m_item = nullptr;
      if (item != nullptr) {
         m_item = new char[strlen(item) + 1];
         strcpy(m_item, item);
      }
   }
   MenuItem::~MenuItem() {
      delete[] m_item;
   }
   std::ostream& MenuItem::displayItem(std::ostream& os)const {
      if (m_item != nullptr) {
         os << m_item;
      }
      return os;
   }
   MenuItem::operator bool()const {
      bool ret = false;
      if (m_item != nullptr) {
         ret = true;
      }
      return ret;
   }
   const char* MenuItem::item()const {
      return m_item;
   }

   Menu::Menu() {
      m_noOfMItems = 0;
      m_title = nullptr;
   }
   Menu::Menu(const char* title) {
      m_noOfMItems = 0;
      if (title != nullptr) {
         m_title = new MenuItem(title);
      }
   }
   Menu::~Menu() {
      delete m_title;  
      for (int i = 0; i < m_noOfMItems; i++) {
         delete m_menuItems[i];
      }
   }

   unsigned Menu::run()const {
      displayMenu();
      int var = getIntInput(0, m_noOfMItems);
      return var;
   }
   std::ostream& Menu::displayTitle(std::ostream& os)const {
      if (m_title != nullptr) {
         os << m_title->m_item;
      }
      return os;
   }
   std::ostream& Menu::displayMenu(std::ostream& os)const {
      if (m_title != nullptr) {
         os << m_title->m_item << endl;
      }
      for (int i = 0; i < m_noOfMItems; i++) {
         os.setf(ios::right);
         os.fill(' ');
         os.width(2);
         os << i + 1 << '-' << ' ' << m_menuItems[i]->m_item << endl;
      }
      os << " 0- Exit" << endl;
      os << "> ";
      os.unsetf(ios::right);
   return os;
   }

   unsigned Menu::operator~()const {
      displayMenu();
      int var = getIntInput(0, m_noOfMItems);
      return var;
   }
   Menu& Menu::operator<<(const char* menuitemConent) {
      int i;
      if (m_noOfMItems < MAX_MENU_ITEMS) {
         for (i = 0; i < MAX_MENU_ITEMS; i++) {
            if (m_menuItems[i] == nullptr) { break; }
         }
         if (i < MAX_MENU_ITEMS) {
            m_menuItems[i] = new MenuItem(menuitemConent);
            m_noOfMItems++;
         }
      }
      return *this;
   }
 
   const char* Menu::operator[](unsigned index)const {
      unsigned numLines = m_noOfMItems;

      if (index >= numLines) {
         index %= numLines;
      }
      return (m_menuItems[index]->m_item);
   }
   Menu::operator bool()const {
      return (m_noOfMItems > 0);
   }
   Menu::operator int()const {
      return m_noOfMItems;
   }
   Menu::operator unsigned()const {
      return m_noOfMItems;
   }

   std::ostream& operator<<(std::ostream& os, const Menu& menu) {
      menu.displayTitle();
      return os;
   }

}
