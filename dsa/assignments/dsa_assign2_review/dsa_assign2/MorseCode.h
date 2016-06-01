//
//  MorseCode.h
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 21/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef MorseCode_h
#define MorseCode_h
#define morseCodeSource "/Users/Abdel/Projects/uts/dsa/assignments/dsa_assign2/dsa_assign2/morsecodes.txt"

#include <list>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "bintree.h"

using namespace std;

class MorseCode
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
   
      struct morseToEnglish
      {
         string morse;
         char letter;
         
         bool operator ==(const morseToEnglish& l) const
         {
            return morse == l.morse;
         }
         
         bool operator <(const morseToEnglish& l) const
         {
            return morse < l.morse;
         }
      };

      // Vector for morse codes
      vector<englishToMorse> vectorMorse;

      // Binary tree for morse codes
      treespc::bintree<morseToEnglish> bintreeMorse;
   
      // Code (either e or d)
      char code;

      // Input file
      const char * filein;
   
      // Output file
      const char * fileout;
   
      void loadSource()
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
            
            // Encoding
            if (code == 'e')
            {
               // Init struct values
               englishToMorse data;
               data.letter = letter;
               data.morse = morse;
               
               // Add to vector
               vectorMorse.push_back(data);
            }
            
            // Decoding
            else if (code == 'd')
            {
               // Init struct values
               morseToEnglish data;
               data.morse = morse;
               data.letter = letter;
               
               // Add to binary tree
               bintreeMorse.insert(data);
            }
         }
         
         // Close file
         source.close();
      }
   
      void encode()
      {
         char c;
         ifstream in;
         ofstream out;
         
         // Open stream to file
         in.open(filein);
         out.open(fileout);
         
         // Check if file can be read
         if (!in.is_open())
         {
            throw runtime_error("ERROR unable to read file");
         }
         
         // Check if we're on a new line
         bool newLine = true;
         
         // Read character by character
         while (in.get(c))
         {
            // Ignore Windows linebreaks
            if (in.good() && c != '\r')
            {
               vector<englishToMorse>::iterator iter;
               iter = find(vectorMorse.begin(), vectorMorse.end(), c);
               
               // Print newline character
               if (c == '\n')
               {
                  out << endl;
                  newLine = true;
               }
               
               // Or, print a space
               else if (c == ' ')
               {
                  out << " ";
               }
               
               // Or, print the morse code
               else if (iter != vectorMorse.end())
               {
                  // To avoid trailing space, print morse with preceding space
                  if (newLine == false) out << " " << iter->morse;
                  
                  // If beginning new line, print without a space
                  else
                  {
                     out << iter->morse;
                     newLine = false;
                  }
               }
            }
         }
         
         // Close all connections
         in.close();
         out.close();
      }
      
      void decode()
      {
         ifstream in;
         ofstream out;
         
         // Open stream to file
         in.open(filein);
         out.open(fileout);
         
         // Check if file can be read
         if (!in.is_open())
         {
            throw runtime_error("ERROR unable to read file");
         }
         
         // Read character by character
         string line;
         string morse;
         string output;
         char c;
         
         bintreeMorse.rebalance();
        
         // Read character by character
         while (getline(in, line))
         {
            istringstream buffer(line);
            
            while (buffer.get(c))
            {
               if (c != ' ')
               {
                  if (morse == " ") morse = c;
                  else morse += c;
               }
               
               if (c == ' ' || buffer.peek() == -1)
               {
                  if (morse == " ")
                  {
                     out << " ";
                     morse = "";
                  }
                  else
                  {
                     treespc::const_iterator<morseToEnglish> iter;
                     morseToEnglish findMorse;
                     findMorse.morse = morse;
                     
                     iter = bintreeMorse.find(findMorse);
                     out << iter->letter;
                     
                     morse = " ";
                  }
               }

            }
            
            out << endl;
         }
         
         // Close all connections
         in.close();
         out.close();
      }
   
   public:
      MorseCode(char code, const char * filein, const char * fileout)
      {
         this->code = code;
         this->filein = filein;
         this->fileout = fileout;
      }
   
      // Public function to handle the translation depending
      // on the code passed to the constructor
      void translate()
      {
         // Load the morse codes from source and insert to specified data structures
         loadSource();
         
         if (code == 'e') encode();
         else if (code == 'd') decode();
      }
};


#endif /* MorseCode_h */
