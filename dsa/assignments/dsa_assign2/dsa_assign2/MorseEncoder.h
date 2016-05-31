//
//  MorseEncoder.h
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 29/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef MorseEncoder_h
#define MorseEncoder_h
#define morseCodeSource "/Users/Abdel/Projects/uts/dsa/assignments/dsa_assign2/dsa_assign2/morsecodes.txt"

#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

class MorseEncoder
{
   private:
      struct englishToMorse
      {
         char letter;
         string morse;
         
         bool operator ==(char l) const
         {
            return letter == l;
         }
      };
      
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
            throw runtime_error("ERROR unable to read file");
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
      void encode(ifstream &in, ofstream &out)
      {
         // Check if file can be read
         if (!in.is_open() || !out.is_open())
         {
            throw runtime_error("ERROR unable to read file");
         }
         
         char c;
         string output;
         bool newLine = true;
         
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
            
            // Print newline character
            if (c == '\n')
            {
               out << endl;
               newLine = true;
            }
            else if (c == ' ')
            {
               // Print a space
               out << " ";
            }
            else if (iter != vectorMorse.end())
            {
               // Print the morse code
               output = iter->morse;
               
               // To avoid trailing space, print morse with preceding space
               if (newLine == false)
               {
                  out << " " << output;
               }
               else
               {
                  // If beginning new line, print without a space
                  out << iter->morse;
                  newLine = false;
               }
            }
            else
            {
               out << c;
            }
         }
      }
};

#endif /* MorseEncoder_h */
