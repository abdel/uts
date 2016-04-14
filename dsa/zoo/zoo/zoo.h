//
//  zoo.h
//  zoo
//
//  Created by Abdelrahman Ahmed on 5/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef zoo_h
#define zoo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>

#include "livestock.h"

using namespace std;

class zoo
{
   public:
      // Utility functions
      int numStock() const;
      int numPen(string pen) const;
      int numClass(string className) const;
      
      vector<livestock> * getPenStock(const string &pen) const;
      
      // File functions
      bool save(const char *filename) const;
      bool load(const char *filename);
      
   private:
      int stockCount;
      vector<livestock> stock;
};

vector<livestock> * zoo::getPenStock(const string &pen) const {
   vector<livestock> * stockInPen = new vector<livestock>;
   vector<livestock>::const_iterator i;
   int count = 0;
   
   for (i = stock.begin(); i != stock.end(); i++)
   {
      if (i->getPenID() == pen) {
         stockInPen->push_back(stock[count]);
      }
      
      count++;
   }
   
   return stockInPen;
}

int zoo::numStock() const
{
   return stockCount;
}

int zoo::numPen(string pen) const
{
   // Total count of matching stock pens
   int total = 0;
   
   for (int i = 0; i < stockCount; i++)
   {
      // Compare stock pens and increment counter
      if (pen.compare(stock[i].getPenID()) == 0)
      {
         total++;
      }
   }
   
   return total;
}

int zoo::numClass(string className) const
{
   // Total count of matching animal class
   int total = 0;
   
   for (int i = 0; i < stockCount; i++)
   {
      // Compare animal classes and increment counter
      if (className.compare(stock[i].getClass()) == 0)
      {
         total++;
      }
   }
   
   return total;
}

bool zoo::save(const char *filename) const
{
   ofstream db;
   
   // Open stream to db
   db.open(filename);
   
   if (!db.is_open())
   {
      throw out_of_range("Unable to open the file.");
   }
   
   // Total number of stock
   int count = 0;
   
   while (!db.eof())
   {
      // Make sure number of stock stored
      // matches total number of stock
      if (count == stockCount)
      {
         break;
      }
      
      // Write total number of stock to first line
      if (count == 0)
      {
         db << stockCount << endl;
      }
      
      /**
       Having an animal object alows us to easily
       add new or modify existing data if required
       */
      
      // Write animal properties to file
      db << stock[count].getID() << endl;
      db << stock[count].getGender() << endl;
      db << stock[count].getPenID() << endl;
      db << stock[count].getClass() << endl;
      db << stock[count].getGenus() << endl;
      db << stock[count].getSpecies() << endl;
      
      count++;
   }
   
   // Close streams
   db.close();
   
   return true;
}

bool zoo::load(const char *filename)
{
   ifstream db;
   string line;
   
   // Total number of stock
   int count = 0;
   
   // Open stream to zoo file
   db.open(filename);
   
   // Check if file can be read
   if (!db.is_open())
   {
      throw out_of_range("Unable to open the file.");
   }
   
   // Get total number of stock
   if (!db.eof())
   {
      getline(db, line);
      stockCount = atoi(line.c_str());
   }
   
   // Array of animal object
   livestock *s;
   
   // Read data till the end of file
   while (!db.eof())
   {
      // Make sure number of stock stored
      // matches total number of stock
      if (count == stockCount && db.eof())
      {
         // break;
      }
      
      // Initialise animal object
      s = new livestock();
      
      // Skip first line containing
      // total number of stock
      getline(db, line);
      if (atoi(line.c_str()) == stockCount)
      {
         getline(db, line);
      }
      
      // Validate & set stock ID
      if (!s->setID(line))
      {
         throw out_of_range("Invalid stock ID.");
      }
      
      // Validate & set stock gender
      getline(db, line);
      if (!s->setGender(line))
      {
         throw out_of_range("Invalid gender.");
      }
      
      // Validate & set stock pen
      getline(db, line);
      if (!s->setPenID(line))
      {
         throw out_of_range("Invalid stock pen.");
      }
      
      // Set animal class
      getline(db, line);
      s->setClass(line);
      
      // Set animal genus
      getline(db, line);
      s->setGenus(line);
      
      // Set animal species
      getline(db, line);
      s->setSpecies(line);
      
      // Insert animal object & add to counter
      stock.push_back(*s);
      count++;
   }
   
   // Incorrect number of stock entered
   if (db.eof() && count != stockCount) {
      throw out_of_range("Number of stock does not match the number of stock data.");
   }
   
   // Close input file
   db.close();
   
   return true;
}

#endif /* zoo_h */
