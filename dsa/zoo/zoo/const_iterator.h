//
//  count_iterator.h
//  zoo
//
//  Created by Abdelrahman Ahmed on 13/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef VECTOR_CONST_ITERATOR_H_
#define VECTOR_CONST_ITERATOR_H_

#include "vector.h"

using namespace vectorspc;

template <typename dataType> class const_iterator
{
   private:
      // note parent is const
      const vector<dataType> *parent;
      int current;
      
   public:
      // constructor
      const_iterator() : parent(NULL), current(0)
      {
      }
      
      const_iterator(const vector<dataType> *myParent, int position) :
         parent(myParent), current(position)
      {
      }
      
      // overloaded dereference operator
      const dataType& operator * () const
      {
         // same code. Note return type is const
      }
      
      // overloaded arrow operator
      const dataType* operator -> () const
      {
         // same code. Note return type is const
      }
};

#endif