//
//  MorseDecoder.h
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 29/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef MorseDecoder_h
#define MorseDecoder_h

#ifndef morseCodeSource
#define morseCodeSource "./morsecodes.txt"
#endif

#include <string>
#include <cctype>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "bintree.h"
#include "morseToEnglish.h"

using namespace std;

class MorseDecoder
{
   private:
      // Binary tree for morse codes
      treespc::bintree<morseToEnglish> bintreeMorse;
      
      void loadSourceIntoBinaryTree()
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
            morseToEnglish data;
            data.morse = morse;
            data.letter = letter;
            
            // Add to binary tree
            bintreeMorse.insert(data);
         }
         
         source.close();
      }
   
   public:
      MorseDecoder() {}
   
      // Handles the decoding process by using loadSource to load
      // the morse codes into a binary tree and balacnes the tree.
      // Loads the input & output files and using the morse:letter map, it goes through the
      // input file line by line first then checks character by character on that line.
      // Constructs a morse string from the characters, then outputs the associated letter.
      void decode(const char * filein, const char * fileout)
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
         
         // Load morse code source into binary tree
         loadSourceIntoBinaryTree();
         
         // Rebalance tree
         bintreeMorse.rebalance();
         
         // Read character by character
         while (in.get(c))
         {
            // Add morse only chars to output
            if (c == '*' || c == '-')
            {
               output += c;
            }
            else if (c != ' ' && c != '\n' && output == "")
            {
               // Retain regular characters
               out << c;
            }
            // If not in morse format, or approaching end of line
            else if (c == ' ' || c == '\n' || in.peek() == -1 || in.peek() == 10)
            {
               // Get letter from morse
               try {
                  treespc::const_iterator<morseToEnglish> iter;
                  morseToEnglish findMorse;
                  findMorse.morse = output;
                  
                  iter = bintreeMorse.find(findMorse);
                  out << iter->letter;
               }
               catch (exception &e)
               {
                  // Output line or space
                  out << c;
               }
               
               // Reset output
               output = "";
            }
         }

         in.close();
         out.close();
      }
};

#endif /* MorseDecoder_h */
