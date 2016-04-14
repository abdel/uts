//
//  iterator.h
//  zoo
//
//  Created by Abdelrahman Ahmed on 13/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef VECTOR_ITERATOR_H_
#define VECTOR_ITERATOR_H_

/***********************************************\
 template iterator class for vector
 \***********************************************/

template <typename dataType> class iterator
{
   friend vector<dataType>;
   
private:
   vector<dataType> *parent;
   int current;
   
public:
   // constructor
   iterator() :
   parent(NULL), current(0)
   {
   }
   
   iterator(vector<dataType> *myParent, int position) :
   parent(myParent), current(position)
   {
   }
   
   /********************************************\
    access operators
    \********************************************/
   
   // overloaded dereference operator
   dataType& operator * () const
   {
      if (current < 0 || current >= parent->numItems)
      {
         throw std::invalid_argument("Attempting to dereference outside vector");
      }
      return parent->theData[current];
   }
   
   // overloaded arrow operator
   dataType* operator -> () const
   {
      if (current < 0 || current >= parent->numItems)
      {
         throw std::invalid_argument("Attempting to reference outside vector");
      }
      return &(parent->theData[current]);
   }
   
   /********************************************\
    increment operators
    \********************************************/
   
   // overloaded prefix increment operator. eg ++i;
   iterator<dataType>& operator ++ ()
   {
      if (current >= parent->numItems)
      {
         throw std::invalid_argument("Attempting to advance past end of vector");
      }
      current++;
      return *this;
   }
   
   // overloaded postfix increment operator. eg i++;
   iterator<dataType> operator ++ (int)
   {
      iterator<dataType> current_data = *this;
      ++(*this);
      return current_data;
   }
   
   /********************************************\
    decrement operators
    \********************************************/
   
   // overloaded prefix decrement operator. eg --i;
   iterator<dataType>& operator -- ()
   {
      if (current <= 0)
      {
         throw std::invalid_argument("Attempting to advance before start of vector");
      }
      current--;
      return *this;
   }
   
   // overloaded postfix decrement operator. eg i--;
   iterator<dataType> operator -- (int)
   {
      iterator<dataType> current_data = *this;
      --(*this);
      return current_data;
   }
   
   /********************************************\
    equality operators
    \********************************************/
   
   // overloaded equality operator
   bool operator == (const iterator &other) const
   {
      return (parent == other.parent && current == other.current);
   }
   
   // overloaded inequality operator
   bool operator != (const iterator &other) const
   {
      return (parent != other.parent || current != other.current);
   }
};
#endif