//
//  main.cpp
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 21/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#include <list>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "bintree.h"
#include "MorseCode.h"

using namespace std;

void printList(const list<char> &myList);
void fillList(list<char> &myList, const string &vowels);
void changeCase(list <char> &myList);

void printList(const list<char> &myList)
{
   list<char>::const_iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      cout << ' ' << *itr;
   }
   cout << '\n';
}

void fillList(list<char> &myList, const string &vowels)
{
   for (int i = 0; i<vowels.length(); i++) {
      myList.push_back(vowels[i]);
   }
}

void changeCase(list <char> &myList)
{
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (islower(*itr)) *itr = toupper(*itr);
      else *itr = toupper(*itr);
   }
}

int main(int argc, const char * argv[])
{
   try
   {
      // Check for argument syntax
      if (argc != 4)
      {
         throw runtime_error("ERROR Syntax: program e|d filein fileout");
      }
      
      char code = argv[1][0];
      const char * filein = argv[2] ? argv[2] : "";
      const char * fileout = argv[3] ? argv[3] : "";
      
      if (code == 'e' || code == 'd')
      {
         MorseCode morse = *new MorseCode(code, filein, fileout);
         morse.translate();
      }
   }
   catch (exception& e)
   {
      cout << e.what() << endl;
   }
   
   return 0;
}
