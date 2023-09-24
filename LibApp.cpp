// Final Project Milestone 5
// LibApp Module
// File LibApp.cpp
// Version 1.0
// Author	Naushin Rahman
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "LibApp.h"
using namespace std;
namespace sdds {
   LibApp::LibApp(const char* filename) 
      : m_exitMenu("Changes have been made to the data, what would you like to do?"), 
      m_mainMenu("Seneca Library Application"),
      m_pubMenu("Choose the type of publication:") {
         m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
         m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
         m_pubMenu << "Book" << "Publication";
         m_changed = false;
         if (filename != nullptr) {
            strncpy(m_fileName, filename, 256);
         }
         load();
   }
   bool LibApp::confirm(const char* message) {
      bool ret = false;
      Menu m_conf(message);
      m_conf << "Yes";
      if (m_conf.run() == 1) {
         ret = true;
      }
      return ret;
   }
   void LibApp::load() {  // prints: "Loading Data"<NEWLINE>
      cout << "Loading Data" << endl;
      ifstream file;
      file.open(m_fileName);
      int i;
      char type{};
      for (i = 0; file; i++) {
         file >> type;
         file.ignore();
         if (file) {
            if (type == 'P') {
               m_PPA[i] = new Publication;
            }
            else if (type == 'B') {
               m_PPA[i] = new Book;
            }
            if (m_PPA[i]) {
               file >> *m_PPA[i];
               m_NOLP++;
               m_LLRN = m_PPA[i]->getRef();
            }
         }
      }
      file.close();
   }
   void LibApp::save() {  
      cout << "Saving Data" << endl;
      ofstream file;
      file.open(m_fileName);
      if (file) {
         for (int i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() != 0) {
               file << *m_PPA[i];
               file << endl;
            }
         }
      }
      file.close();
   }
   int LibApp::search(int searchType) {
      PublicationSelector ps("Select one of the following found matches:");
      int mode = ~m_pubMenu;
      cin.ignore(1000, '\n');
      char type;
      if (mode == 1) {
         type = 'B';
      }
      else if (mode == 2){
         type = 'P';
      }
      cout << "Publication Title: ";
      char temp[256]{};
      cin.getline(temp, 256);
      for (int i = 0; i < m_NOLP; i++) {
         if (m_PPA[i] && (type == m_PPA[i]->type()) && m_PPA[i]->operator==(temp)) {
            if (searchType == 1) {   //search all
               ps << m_PPA[i];
            }
            else if (searchType == 2) {  //search loan
               if (m_PPA[i]->onLoan()) {
                  ps << m_PPA[i];
               }
            }
            else if (searchType == 3) { //search available
               if (!(m_PPA[i]->onLoan())) {
                  ps << m_PPA[i];
               }
            }
         }
      }
      int retVal = 0;
      if (ps) {
         ps.sort();
         retVal = ps.run();
         if (retVal) {
            cout << *getPub(retVal) << endl;
         }
         else {
            cout << "Aborted!" << endl;
         }
      }
      else {
         cout << "No matches found!" << endl;
      }
      return retVal;
   }
   void LibApp::returnPub() {       
      cout << "Return publication to the library" << endl;
      int selection = search(2);
      if (selection) {
         if (confirm("Return Publication?")) {
            int dayDiff = Date() - getPub(selection)->checkoutDate();
            if (dayDiff > SDDS_MAX_LOAN_DAYS)
            {
               double penalty = 0.5 * (dayDiff - SDDS_MAX_LOAN_DAYS);
               cout << "Please pay $" << setprecision(2) << fixed
                  << penalty << " penalty for being "
                  << dayDiff - SDDS_MAX_LOAN_DAYS << " days late!"
                  << endl;
            }
            getPub(selection)->set(0);
            m_changed = true;
            cout << "Publication returned" << endl;
         }
      } 
   }
   void LibApp::newPublication() {
      if (m_NOLP == SDDS_LIBRARY_CAPACITY) {
         cout << "Library is at its maximum capacity!";
      }
      else {
         cout << "Adding new publication to the library" << endl;
         Publication* p = nullptr;
         int selection = ~m_pubMenu;         //get the publication type from the user 
         cin.ignore(1000, '\n');
         switch (selection)              //instantiate a dynamic "Publication" or "Book" based on the user's choice in pub pointer
         {
         case 1:
            p = new Book;
            cin >> *p;               //read the object from the cin object
            break;
         case 2:
            p = new Publication;
            cin >> *p;              //read the object from the cin object 
            break;
         case 0:
            cin.clear();
            cout << "Aborted!" << endl;
            break;
         }
         if (selection && cin.good()) {
            if (!confirm("Add this publication to the library?")) {
               cout << "Aborted!";
            }
            if (p) {
               m_LLRN++;
               p->setRef(m_LLRN);
               m_PPA[m_NOLP] = p;
               m_NOLP++;
               m_changed = true;
               cout << "Publication added" << endl;
            }
            else {
               cout << "Failed to add publication!" << endl;
               delete p;
            }
         }
      }
   }
   void LibApp::removePublication() {
      cout << "Removing publication from the library" << endl;
      int selection = search(1);
      if (selection) {
         if (confirm("Remove this publication from the library?")) {
            getPub(selection)->setRef(0);
            m_changed = true;
            cout << "Publication removed" << endl;
         }
      }
   }
   void LibApp::checkOutPub() {
      cout << "Checkout publication from the library" << endl;
      int selection = search(3);
      if (selection) {
         if (confirm("Check out publication?")) {
            cout << "Enter Membership number: ";
            int mem = 0, i = 1;
            do {
               cin.ignore(1000, '\n');
               cin >> mem;
               if (mem > 9999 && mem < 100000) {
                  getPub(selection)->set(mem);
                  m_changed = true;
                  cout << "Publication checked out" << endl;
                  i = 0;
               }
               else {
                  cout << "Invalid membership number, try again: ";
               }
            } while (i);
         }
      }
   }
   void LibApp::run() {
      bool selection = false;

      while (!selection) {
         unsigned i = ~m_mainMenu;
         if (i == 1) {
            newPublication();
            cout << endl;
         }
         else if (i == 2) {
            removePublication();
            cout << endl;
         }
         else if (i == 3) {
            checkOutPub();
            cout << endl;
         }
         else if (i == 4) {
            returnPub();
            cout << endl;
         }
         else if (i == 0) {
            if (m_changed) {
               unsigned j = ~m_exitMenu;
               switch (j) {
               case 1:
                  save();
                  selection = true;
                  break;
               case 2:
                  break;
               default:
                  if (confirm("This will discard all the changes are you sure?")) {
                     selection = true;
                  }
               }
               cout << endl;
            }
            else {
               cout << endl;
               selection = true;
            }
         }
      } 
      cout << "-------------------------------------------" << endl;
      cout << "Thanks for using Seneca Library Application" << endl;
   }
   Publication* LibApp::getPub(int libRef) {
      Publication* p = nullptr;
      for (int i = 0; i < m_NOLP; i++) {
         if (m_PPA[i]->getRef() == libRef) {
            p = m_PPA[i];
         }
      }
      return p;
   }
   LibApp::~LibApp() {
      for (int i = 0; i < m_NOLP; i++) {
         delete m_PPA[i];
         m_PPA[i] = nullptr;
      }
   }
}
