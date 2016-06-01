//
//  EuroConverter.h
//
//  Data Structures & Algorithms
//  Assignment 1
//
//  Created by Abdelrahman Ahmed on 25/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef EuroConverter_h
#define EuroConverter_h

#include <list>
#include <cctype>
#include <fstream>
#include <stdexcept>

using namespace std;

class EuroConverter
{
   private:
      // LinkedList, data sourced from file
      list<char> text;
   
      // Name of input file
      const char * filename;

      // LinkedList/File-handling
      void insertEnglishText();
      unsigned short getHash();
      void printText();
   
      // EuroEnglish
      void applyRules();
      char changeChar(char replace, char with);
      bool matches(int rule, list<char>::iterator &itr, int &charCount);
   
   public:
      EuroConverter(const char * filename);
      void toEuroEnglish();
};

// Store the filename of the English data
EuroConverter::EuroConverter(const char * filename)
{
   this->filename = filename;
}

// Insert the English text and apply the EuroEnglish rules.
// Print original and converted versions for comparison with a HASH value.
void EuroConverter::toEuroEnglish()
{
   // Insert English text from source file
   this->insertEnglishText();
   
   // Print out the English text with a hash value
   this->printText();
   
   // Apply conversion rules to text
   this->applyRules();
   
   // Print new text
   this->printText();
}

// Open and read the data source file, add each character to a LinkedList
void EuroConverter::insertEnglishText()
{
   ifstream db;
   char c;
   
   // Open stream to file
   db.open(filename);
   
   // Check if file can be read
   if (!db.is_open())
   {
      throw runtime_error("ERROR unable to read ");
   }
   
   // Read character by character
   while (db.get(c))
   {
      // Don't enter Windows linebreaks
      if (db.good() && c != '\r')
      {
         // Add each character to the linked list
         text.push_back(c);
      }
   }
}

// Loop through the LinkedList and output the content to the command line,
// and get a HASH value for the text.
void EuroConverter::printText()
{
   list<char>::const_iterator itr;
   
   cout << endl;
   
   for (itr = text.begin(); itr != text.end(); itr++ ) {
      cout << *itr;
   }
   
   // Get hash, add some spacing for clarity
   cout << endl << "Hash = " << getHash() << endl;
}

// Iterates through the linked list and calculates the hash value.
unsigned short EuroConverter::getHash()
{
   unsigned short shift, hash = 0;
   list<char>::const_iterator itr;
   
   for (itr = text.begin(); itr != text.end(); itr++)
   {
      hash ^= *itr;
      shift = (hash & 15);
      hash = (hash << shift) | (hash >> (16 - shift));
   }
   
   return hash;
}

// Replaces a character with the another, and maintains the case.
char EuroConverter::changeChar(char replace, char with) {
   if (isupper(replace)) {
      return toupper(with);
   }
   
   return tolower(with);
}

// Iterates through the linked list and checks words (alphanumeric) against
// each rule. If a match is found, the rules are checked again against the same character.
// Using rule to keep track of which rule we're currently checking.
// Using charCount to check if we're still in the same word,
// and get character count of the word thus far.
void EuroConverter::applyRules()
{
   int charCount = 1;
   list<char>::iterator itr = text.begin();
   
   // Go through the linkedlist until the
   // last character is matched.
   while (itr != text.end())
   {
      // Only apply rules to words (alphanumeric)
      if (isalnum(*itr))
      {
         int rule = 1;
         
         // Attempt to match character against every rule
         // continue till no more matches are found.
         while (rule <= 10)
         {
            // Match rules on the same character again
            if (matches(rule, itr, charCount))
            {
               rule = 1;
            }
            else
            {
               rule++;
            }
         }
         
         charCount++;
      }
      else
      {
         // Reset count for non-words
         charCount = 1;
      }
      
      itr++;
   }
}

// Checks the current character against the specified rule in order to convert to Euro English,
// it compares characters in lowercase for consistency, and uses changeChar for any modifications.
bool EuroConverter::matches(int rule, list<char>::iterator &itr, int &charCount)
{
   // Next & previous pointers
   list<char>::iterator next = itr;
   list<char>::iterator prev = itr;
   ++next;
   --prev;
   
   // Convert chars to lowercase
   // for accurate comparison
   char p = tolower(*prev);
   char c = tolower(*itr);
   char n = tolower(*next);
   
   switch (rule)
   {
         // Replace all instances of 'w' with 'v'.
      case 1:
         if (c == 'w')
         {
            *itr = changeChar(*itr, 'v');
            return true;
         }
         break;
         
         // Replace all double characters with a single instance of the character.
      case 2:
         if (c == n)
         {
            text.erase(next);
            return true;
         }
         break;
         
         // Replace all instances of "ph" with the character 'f'.
      case 3:
         if (c == 'p' && n == 'h')
         {
            *itr = changeChar(*itr, 'f');
            text.erase(next);
            return true;
         }
         break;
         
         // Replace all instances of "th" with 'z'.
      case 4:
         if (c == 't' && n == 'h')
         {
            *itr = changeChar(*itr, 'z');
            text.erase(next);
            return true;
         }
         break;
         
         // Replace all instances of "ou" with 'u'.
      case 5:
         if (c == 'o' && n == 'u')
         {
            *itr = changeChar(*itr, 'u');
            text.erase(next);
            return true;
         }
         break;
         
         // Replace all instances of "ea" with 'e'.
      case 6:
         if (c == 'e' && n == 'a')
         {
            text.erase(next);
            return true;
         }
         break;
         
         // Replace all 'c' with 's' if followed by the characters 'e', 'i' or 'y'.
      case 7:
         if (c == 'c' && (n == 'e' || n == 'i' || n == 'y'))
         {
            *itr = changeChar(*itr, 's');
            return true;
         }
         break;
         
         // Replace 'c' with 'k'
      case 8:
         if (c == 'c')
         {
            *itr = changeChar(*itr, 'k');
            return true;
         }
         break;
         
         // If a word is more than 3 characters long and ends with an 'e' then it can be removed.
      case 9:
         if (c == 'e' && charCount > 3 && !isalnum(n))
         {
            text.erase(itr);
            return false; // Can't recheck deleted character
         }
         break;
         
      case 10:
         if (p == 'e' && c == 'd' && !isalnum(n))
         {
            text.erase(prev);
            return true;
         }
         break;
         
   }
   
   return false;
}

#endif /* EuroConverter_h */
