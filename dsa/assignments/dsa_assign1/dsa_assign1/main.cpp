//
//  main.cpp
//
//  Data Structures & Algorithms
//  Assignment 1
//
//  Created by Abdelrahman Ahmed on 25/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#include <iostream>

#include "EuroConverter.h"

using namespace std;

int main(int argc, const char * argv[])
{
   const char * filename = argv[1] ? argv[1] : "";
   
   cout << "Euro Converter by Abdelrahman Ahmed (12445336)" << endl;
   
   try
   {
      // Check for argument syntax
      if (argc != 2)
      {
         throw runtime_error("ERROR Syntax: ./euro filename");
      }
      
      // Input filename and convert to Euro English
      EuroConverter convert = *new EuroConverter(filename);
      convert.toEuroEnglish();

   }
   catch (exception& e)
   {
      cout << e.what() << filename << endl;
   }
   
   return 0;
}
