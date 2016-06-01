//
//  livestock.h
//  zoo
//
//  Created by Abdelrahman Ahmed on 6/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef livestock_h
#define livestock_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"

using namespace std;

class livestock: public animal
{
   private:
      int id;
      string gender, pen_id;
      
   public:
      bool setID(string id);
      bool setPenID(string pen_id);
      bool setGender(string gender);
      
      int getID() const;
      string getGender() const;
      string getPenID() const;
   
      void print();
};

bool livestock::setID(string id)
{
   // Make sure the livestock id is exactly 6 digits
   if (id.length() != 6 || id[0] == '-')
   {
      return false;
   }
   
   livestock::id = atoi(id.c_str());
   return true;
}

bool livestock::setPenID(string pen_id)
{
   // Make sure livestock pen is 3 characters long with 1 uppercase letter and 2 digits
   if (pen_id.length() != 3 || !isupper(pen_id[0]) || !isdigit(pen_id[1]) || !isdigit(pen_id[2]))
   {
      return false;
   }
   
   livestock::pen_id = pen_id;
   return true;
}

bool livestock::setGender(string gender)
{
   // Make sure the gender is either 'm' for male, or 'f' for females
   if (gender.compare("m") != 0 && gender.compare("f") != 0)
   {
      return false;
   }
   
   livestock::gender = gender;
   return true;
}

int livestock::getID() const
{
   return livestock::id;
}

string livestock::getGender() const
{
   return livestock::gender;
}

string livestock::getPenID() const
{
   return livestock::pen_id;
}

void livestock::print()
{
   
}

#endif /* livestock_h */
