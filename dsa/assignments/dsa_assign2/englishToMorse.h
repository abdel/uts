//
//  englishToMorse.h
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 29/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef englishToMorse_h
#define englishToMorse_h

#include <string>

struct englishToMorse
{
   char letter;
   std::string morse;

   bool operator ==(char l) const
   {
      return letter == l;
   }
};

#endif /* englishToMorse_h */
