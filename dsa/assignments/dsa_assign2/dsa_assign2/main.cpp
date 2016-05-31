//
//  main.cpp
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 21/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#include <fstream>
#include <iostream>
#include "MorseEncoder.h"
#include "MorseDecoder.h"

using namespace std;

int main(int argc, const char * argv[])
{
   try
   {
      // Check for argument syntax
      if (argc != 4 || (argv[1][0] != 'd' && argv[1][0] != 'e') || argv[2] == argv[3])
      {
         string message = "Syntax: morse e|d filein fileout\n"
         "e for encoding english to morse, filein to fileout\n"
         "d for decoding morse to english, filein to fileout\n"
         "filein and fileout must be different files";
         
         throw runtime_error(message);
      }
      
      // Open input file
      ifstream in;
      in.open(argv[2]);
      
      // Open output file
      ofstream out;
      out.open(argv[3]);
      
      // Either (e) for encoding,
      // or, (d) for decoding
      if (argv[1][0] == 'e')
      {
         MorseEncoder encoder = *new MorseEncoder();
         encoder.encode(in, out);
      }
      else if (argv[1][0] == 'd')
      {
         MorseDecoder decoder = *new MorseDecoder();
         decoder.decode(in, out);
      }
      
      in.close();
      out.close();
   }
   catch (exception& e)
   {
      cout << e.what() << endl;
      return 1;
   }
   
   return 0;
}
