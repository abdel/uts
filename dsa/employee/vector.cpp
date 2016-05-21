#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>

#include "employee.h"

using namespace std;
      
void swap(vector<employee> employees, int a, int b);
void sortEmployees(vector<employee> &employees);
void printEmployees(vector<employee> &employees);
void loadEmployees(vector<employee> &employees, const char *file);

int main(int argc, char *argv[])
{
   vector<employee> employees;

   if (argc == 2) 
   {
      loadEmployees(employees, argv[1]);
      printEmployees(employees);
      //sortEmployees(employees);
      //printEmployees(employees);
   }
   else
   {
      cout << "Syntax : " << argv[0] << " employeefile\n";
   }

   return 0;
}

void loadEmployees(vector<employee> &employees, const char *file)
{
   ifstream fin;
   employee emp;
   string line;
   
   fin.open(file);

   if (!fin) 
   {
      cout << "Unable to read from " << file << "\n";
      exit(0);
   }
   
	 while(getline(fin, line))
	 {
    	stringstream linestream(line);
    	string data;
	
			string surname;
		  double hourlyRate;
			int empNumber;

    	linestream >> surname >> hourlyRate >> empNumber;
      emp.setEmployee(surname, hourlyRate, empNumber);

		  employees.push_back(emp);
	 }

   fin.close();   
}

void printEmployees(vector<employee> &employees)
{
   unsigned int i;

   for (i=0; i<employees.size(); i++) 
   {
      employees[i].printEmployee();
   }
   cout << "\n";
}

void swap(vector<employee> employees, int a, int b)
{
   employee temp(employees[a]);

   employees[a] = employees[b];
   employees[b] = temp;
}

void sortEmployees(vector<employee> &employees)
{
   /* use selection sort to order employees, 
      in employee name order
   */

   int number = employees.size();
   int inner, outer, max;

   for (outer=number-1; outer>0; outer--)
   {
      // run though array number of times
      max = 0;
      for (inner=1; inner<=outer; inner++)
      {
         // find alphabetically largest surname
         if (employees[inner].getSurname() > employees[max].getSurname())
            max = inner;
      }
      if (max != outer)
      {
         // swap largest with last element in array
         swap(employees, max, outer);
      }
   }
}
