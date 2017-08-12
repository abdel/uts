#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class employee
{
   /* Employee class to contain employee data
   */
   
   private:
      string surname;
      double hourlyRate;
      int empNumber;
     
   public:
      employee() 
      {
         hourlyRate = -1;
         empNumber = -1;
         surname = "";
      }
      
      employee(const employee &other) :
         surname(other.surname),
         hourlyRate(other.hourlyRate),
         empNumber(other.empNumber)
      {
         hourlyRate = other.hourlyRate;
         empNumber = other.empNumber;
         surname = other.surname;
      }
      
      void setEmployee(const string &name, double rate, int num) 
      { 
         surname = name;
         hourlyRate = rate;
         empNumber = num;
      }
      
      const string& getSurname() const 
      {
         return surname;
      }
      
      void printEmployee() 
      {
         cout << fixed << setprecision(2);
         cout << setw(20) << left << surname << setw(4) << empNumber << "  " << hourlyRate << "\n";
      }
      
      void loadEmployee(ifstream &fin) 
      {
         //fin << surname;
         //fin << hourlyRate;
         //fin << empNumber;
      }
};
      
#endif
