//
//  main.cpp
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 21/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include "MorseEncoder.h"
#include "MorseDecoder.h"

using namespace std;

int main(int argc, const char * argv[])
{
   const char * filein = argv[2];
   const char * fileout = argv[3];

   // Check for argument syntax
   if (argc != 4)
   {
      cout << "Syntax: morse e|d filein fileout" << endl;
      return 1;
   }
   else if (strcmp(filein, fileout) == 0)
   {
      cout << "ERROR filein and fileout must be different files" << endl;
      return 1;
   }

   try
   {
      // Either (e) for encoding,
      // or, (d) for decoding
      if (strcmp(argv[1], "e") == 0)
      {
         MorseEncoder encoder = *new MorseEncoder();
         encoder.encode(filein, fileout);
      }
      else if (strcmp(argv[1], "d") == 0)
      {
         MorseDecoder decoder = *new MorseDecoder();
         decoder.decode(filein, fileout);
      }
      else
      {
         throw runtime_error("Syntax: morse e|d filein fileout");
      }
   }
   catch (exception& e)
   {
      cout << e.what() << endl;
      return 1;
   }
   
   return 0;
}
