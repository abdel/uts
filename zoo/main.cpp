#include <iostream>
#include "zoo.h"

using namespace std;

int main(int argc, char*argv[])
{
   if (argc == 3)
   {
      try
      {
         zoo myZoo;
         myZoo.load(argv[1]);
         
         cout << "Num Stock = " << myZoo.numStock() << "\n";
         cout << "Num pen C43 = " << myZoo.numPen("C43") << "\n";
         cout << "Num Mammalia = " << myZoo.numClass("Mammalia") << "\n\n";
         
         cout << "Stock found in pen C43" << "\n\n";
      
         vector<livestock> * stockInPen = myZoo.getPenStock("C43");
         vector<livestock>::const_iterator i;
         
         for (i = stockInPen->begin(); i != stockInPen->end(); i++)
         {
            cout << i->getID() << endl;
            cout << i->getGender() << endl;
            cout << i->getPenID() << endl;
            cout << i->getClass() << endl;
            cout << i->getGenus() << endl;
            cout << i->getSpecies() << endl;
            cout << endl;
         }
         
         delete(stockInPen);
         
         // myZoo.save(argv[2]);
      }
      catch (exception &ex)
      {
         cout << "\nERROR - Exception thrown\n" << ex.what() << "\n";
      }
   }
   else
   {
      cout << "\nERROR - Invalid command line arguments\n";
   }
   
   return 0;
}
