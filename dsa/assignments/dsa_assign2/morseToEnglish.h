//
//  morseToEnglish.h
//  dsa_assign2
//
//  Created by Abdelrahman Ahmed on 29/05/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef morseToEnglish_h
#define morseToEnglish_h

#include <string>

struct morseToEnglish
{
   std::string morse;
   char letter;
         
   bool operator ==(const morseToEnglish& l) const
   {
      return morse == l.morse;
   }

   bool operator !=(const morseToEnglish& l) const
   {
      return morse != l.morse;
   }

   bool operator <(const morseToEnglish& l) const
   {
      return morse < l.morse;
   }

   bool operator >(const morseToEnglish& l) const
   {
      return morse > l.morse;
   }
};

#endif /* morseToEnglish_h */
