//
//  animal.h
//  zoo
//
//  Created by Abdelrahman Ahmed on 6/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef animal_h
#define animal_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class animal
{
   protected:
      string classification, genus, species;
   
   public:
      void setClass(string classification);
      void setGenus(string genus);
      void setSpecies(string species);
   
      string getClass() const;
      string getGenus() const;
      string getSpecies() const;
};

void animal::setClass(string classification)
{
   animal::classification = classification;
}

void animal::setGenus(string genus)
{
   animal::genus = genus;
}

void animal::setSpecies(string species)
{
   animal::species = species;
}

string animal::getClass() const
{
   return animal::classification;
}

string animal::getGenus() const
{
   return animal::genus;
}

string animal::getSpecies() const
{
   return animal::species;
}

#endif /* animal_h */
