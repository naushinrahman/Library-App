// Final Project Milestone 4
// Book module
// File Book.cpp
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
#include "Lib.h"
#include "Book.h"
using namespace std;
namespace sdds {
   Book::Book() : Publication() {
      m_authorName = nullptr;
   }
   Book::Book(const Book& book) {
      if (book) {
         *this = book;
      }
   }
   Book& Book::operator=(const Book& book) {
      if (this != &book) {
         if (book.m_authorName && book.m_authorName[0] != '\0') {
            if (m_authorName) {
               delete[] m_authorName;
               m_authorName = nullptr;
            }
            m_authorName = new char[strlen(book.m_authorName) + 1];
            strcpy(m_authorName, book.m_authorName);
            Publication::operator=(book);
         }
      }
      return *this;
   }
   Book::~Book() {
      delete[] m_authorName;
      m_authorName = nullptr;
   }
   ostream& Book::write(ostream& os) const {
      Publication::write(os);
      if (Publication::conIO(os)) {
         os << ' ';
         if (strlen(m_authorName) < SDDS_AUTHOR_WIDTH) {
            os << setw(SDDS_AUTHOR_WIDTH) << m_authorName;
         }
         else {
            for (int i = 0; i < SDDS_AUTHOR_WIDTH && m_authorName[i] != '\0'; i++) {
               os << m_authorName[i];
            }
            os << left << setfill(' ');
         }
         os << " |";
      }
      else {
         os << '\t' << m_authorName;
      }
      return os;
   }
   istream& Book::read(istream& is) {
      Publication::read(is);
      if (m_authorName != nullptr) {
         delete[] m_authorName;
         m_authorName = nullptr;
      }
      char author[256]{};
      if (Publication::conIO(is)) {
         is.ignore(1);
         cout << "Author: ";
         is.get(author, 256);
      }
      else {
         is.ignore(1);
         is.get(author, 256);
      }
      if (is) {
         m_authorName = new char[strlen(author) + 1];
         strcpy(m_authorName, author);
      }
      return is;
   }
   Book::operator bool() const {
      bool ret = false;
      if (m_authorName && Publication::operator bool()) {
         ret = true;
      }
      return ret;
   }
   char Book::type()const {
      return 'B';
   }
   void Book::set(int member_id) {
      Publication::set(member_id);
      Publication::resetDate();
   }
}