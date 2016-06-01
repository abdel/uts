//
//  MorseEncoder.h
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 29/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef MorseEncoder_h
#define MorseEncoder_h

#ifndef morseCodeSource
#define morseCodeSource "./morsecodes.txt"
#endif

#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "englishToMorse.h"

using namespace std;

class MorseEncoder
{
   private:
      // Vector for morse codes
      vector<englishToMorse> vectorMorse;
   
      void loadSourceIntoVector()
      {
         string line;
         ifstream source;
         
         // Open stream to file
         source.open(morseCodeSource);
         
         // Check if file can be read
         if (!source.is_open())
         {
            throw runtime_error("ERROR unable to read morsecodes.txt");
         }
         
         // Read line by line
         while (getline(source, line))
         {
            char letter;
            string morse;
            stringstream linestream(line);
            
            // Split line into letter and associated morse code
            linestream >> letter >> morse;
            
            // Init struct values
            englishToMorse data;
            data.letter = letter;
            data.morse = morse;
            
            // Add to vector
            vectorMorse.push_back(data);
         }
         
         source.close();
      }
   
   public:
      MorseEncoder() {}
      
      // Handles the encoding process by using loadSource to load
      // the morse codes into a vector, loading the input & output files and
      // using the letter:morse map, it goes through the input file character by character
      // to output associated morse code to the output file.
      void encode(const char * filein, const char * fileout)
      {
         // Open input file
         ifstream in;
         in.open(filein);
         
         // Open output file
         ofstream out;
         out.open(fileout);
      
         // Check if file can be read
         if (!in.is_open() || !out.is_open())
         {
            throw runtime_error("ERROR unable to read file");
         }
         
         char c;
         string output;
         
         // Load morse code source into vector
         loadSourceIntoVector();
         
         // Read character by character
         while (in.get(c))
         {
            // Ignore Windows linebreaks
            if ( !in.good() || c  == '\r')
            {
               continue;
            }
            
            vector<englishToMorse>::iterator iter;
            iter = find(vectorMorse.begin(), vectorMorse.end(), c);
            
            // Print newline
            if (c == '\n')
            {
               // Print a newline
               out << endl;
            }
            else if (c == ' ')
            {
               // Print a space
               out << " ";
            }
            else if (iter != vectorMorse.end())
            {
               // Print associated morse with trailing space
               out << iter->morse << " ";
            }
            else
            {
               // Retain regular chars
               out << c;
            }
         }

         in.close();
         out.close();
      }
};

#endif /* MorseEncoder_h */
