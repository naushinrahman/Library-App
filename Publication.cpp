// Final Project Milestone 3
// Publication module
// File Publication.cpp
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Publication.h"
#include "Date.h"
#include "Lib.h"
using namespace std;
namespace sdds {
   Publication::Publication() : m_title(nullptr), m_membership(0), m_libRef(-1), m_date(Date()) {
      m_shelfID[0] = {'\0'};
   }
   Publication::Publication(const Publication& pub) {
      if (pub.m_title && pub.m_title[0] != '\0') {
         m_title = new char[strlen(pub.m_title) + 1];
         strcpy(m_title, pub.m_title);
         strcpy(m_shelfID, pub.m_shelfID);
         setRef(pub.m_libRef);
         m_date = pub.m_date;
      }
   }
   Publication& Publication::operator=(const Publication& pub) {
      if (this != &pub) {
         if (pub.m_title && pub.m_title[0] != '\0') {
            if (m_title) {
               delete[] m_title;
               m_title = nullptr;
            }
            m_title = new char[strlen(pub.m_title) + 1];
            strcpy(m_title, pub.m_title);
            strcpy(m_shelfID, pub.m_shelfID);
            set(pub.m_membership);
            setRef(pub.m_libRef);
            m_date = pub.m_date;
         }
      }
      return *this;
   }
   Publication::~Publication() {
      if (m_title != nullptr) {
         delete[] m_title;
         m_title = nullptr;
      }
   }

   void Publication::set(int member_id) { //Sets the membership attribute to either zero or a five-digit integer.
      m_membership = member_id;
   }
   void Publication::setRef(int value) { //Sets the **libRef** attribute value
      m_libRef = value;
   }
   void Publication::resetDate() { //Sets the date to the current date of the system.
      m_date = Date();
   }
   char Publication::type()const { //Returns the character 'P' to identify this object as a "Publication object"
      return 'P';
   }
   bool Publication::onLoan()const { //Returns true is the publication is checkout (membership is non-zero)
      bool ret = false;
      if (m_membership != 0) {
         ret = true;
      }
      return ret;
   }
   Date Publication::checkoutDate()const { //Returns the date attribute
      return m_date;
   }
   bool Publication::operator==(const char* title)const { //Returns true if the argument title appears anywhere in the title of the publication. Otherwise, it returns false; (use strstr() function in <cstring>)
      bool ret = false;
      if (strstr(m_title, title)) {
         ret = true;
      }
      return ret;
   }
   Publication::operator const char* ()const { //Returns the title attribute
      return m_title;
   }
   int Publication::getRef()const { //Returns the libRef attirbute. 
      return m_libRef;
   }
   bool Publication::conIO(ios& ios)const {
      bool ret = false;
      if (&ios == &cout || &ios == &cin) {
         ret = true;
      }
      return ret;
   }
   ostream& Publication::write(ostream& os) const {
      if (conIO(os)) {
         os << "| " << m_shelfID << " | ";
         if (strlen(m_title) < SDDS_TITLE_WIDTH) {
            os << left << setw(SDDS_TITLE_WIDTH) << setfill('.') << m_title;
         }
         else {
            for (int i = 0; i < SDDS_TITLE_WIDTH && m_title[i] != '\0'; i++) {
               os << m_title[i];
            }
            os << setfill('.');
         }
         os << " | ";
         if (m_membership == 0) {
            os << " N/A ";
         }
         else {
            os << m_membership;
         }
         os << " | " << m_date << " |";
      }
      else {
         os << type();
         os << "\t" << m_libRef << "\t" << m_shelfID << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
      }
      return os;
   }
   istream& Publication::read(istream& is) {
      if (m_title != nullptr) {
         delete[] m_title;
         m_title = nullptr;
      }
      m_shelfID[0] = { '\0' };
      m_membership = 0;
      m_libRef = -1;
      m_date = Date();

      char title[256]{};
      char shelf[SDDS_SHELF_ID_LEN + 1]{};
      int mem = 0;
      int ref = -1;
      Date chk;
      
      if (conIO(is)) {
         cout << "Shelf No: ";
         is.getline(shelf, SDDS_SHELF_ID_LEN + 1);
         if (strlen(shelf) != SDDS_SHELF_ID_LEN) {
            is.setstate(ios::failbit);
         }
         cout << "Title: ";
         is.getline(title, 256);
         cout << "Date: ";
         is >> chk;
      }
      else {
         is >> ref;
         is.ignore(1);
         is.getline(shelf, SDDS_SHELF_ID_LEN + 1, '\t');
         is.getline(title, 256, '\t');
         is >> mem;
         is.ignore();
         is >> chk;
      }
      if (!chk) {
         is.setstate(ios::failbit);
      }
      if (is) {
         m_title = new char[strlen(title) + 1];
         strcpy(m_title, title);
         strcpy(m_shelfID, shelf);
         m_date = chk;
         Publication::set(mem);
         setRef(ref);
      }
      return is;
   }
   Publication::operator bool() const {
      bool ret = false;
      if (m_title != nullptr && m_shelfID[0] != '\0') {
         ret = true;
      }
      return ret;
   }
}