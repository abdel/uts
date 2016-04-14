//
//  vector.h
//  zoo
//
//  Created by Abdelrahman Ahmed on 13/04/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdexcept>

namespace vectorspc
{
   // forward declaration of vector class
   template<typename dataType> class vector;
   
   #include "iterator.h"
   #include "const_iterator.h"
   
   /***********************************************\
    template class for vector
    \***********************************************/
   
   template<typename dataType> class vector
   {
      // add iterators as friends
      friend class iterator<dataType>;
      friend class const_iterator<dataType>;
      
   private:
      static const int INITIAL_CAPACITY = 100;
      
      int currentCapacity;
      int numItems;
      dataType* theData;
      
      /*****************************************\
       resize functions
       \*****************************************/
      
      dataType* buildDataArray(int capacity) const
      {
         dataType* theData = new dataType[capacity];
         if (theData == NULL)
         {
            throw std::runtime_error("Unable to allocate memory for data array");
         }
         return theData;
      }
      
      void resize(int newCapacity)
      {
         if (newCapacity > currentCapacity)
         {
            // set aside space with extra capacity
            currentCapacity = newCapacity;
            dataType *newData = buildDataArray(newCapacity);
            
            // copy the items across to the new space
            for (int i=0; i<numItems; i++)
            {
               newData[i] = theData[i];
            }
            
            // delete the old data array
            delete[] theData;
            
            // make theData equal to the newly allocated array
            theData = newData;
         }
      }
      
      void resize()
      {
         resize(currentCapacity * 2);
      }
      
   public:
      
      /*****************************************\
       constructors and destructors
       \*****************************************/
      
      // default constructor
      vector() :
      currentCapacity(INITIAL_CAPACITY),
      numItems(0)
      {
         theData = buildDataArray(currentCapacity);
      }
      
      vector(int starting_capacity) :
      currentCapacity(starting_capacity),
      numItems(0)
      {
         theData = buildDataArray(currentCapacity);
      }
      
      // copy constructor
      vector(const vector<dataType> &other) :
      currentCapacity(0),
      numItems(0),
      theData(NULL)
      {
         // make use of overloaded equals operator to reduce duplication of code
         *this = other;
      }
      
      // destructor
      ~vector()
      {
         delete [] theData;
      }
      
      /*****************************************\
       vector size functions
       \*****************************************/
      
      bool isEmpty() const
      {
         return (numItems == 0);
      }
      
      int size() const
      {
         return numItems;
      }
      
      /*****************************************\
       insertion and push functions
       \*****************************************/
      
      iterator<dataType> insert(iterator<dataType> iter, const dataType &item)
      {
         insert(item, iter.current);
         
         return iter;
      }
      
      void insert(const dataType &newData, int index)
      {
         // check index range
         if (index < 0 || index > numItems)
         {
            throw std::out_of_range("Index to insert is out of range");
         }
         
         // ensure there is enough capacity to insert newData
         if (numItems >= currentCapacity)
         {
            // current capacity insufficient for inserting newData
            resize();
         }
         
         // make space for inserting newData
         for (int i=numItems; i > index; i--)
         {
            theData[i] = theData[i-1];
         }
         
         // insert the newData
         theData[index] = newData;
         numItems++;
      }
      
      void push_back(const dataType &newData)
      {
         // append newData to the end of the vector
         insert(newData, numItems);
      }
      
      void push_front(const dataType &newData)
      {
         // insert newData into the front of the vector
         insert(newData, 0);
      }
      
      /*****************************************\
       erase and pop functions
       \*****************************************/
      
      void clear()
      {
         numItems = 0;
      }
      
      iterator<dataType> erase(iterator<dataType> &iter)
      {
         erase(iter.current);
         
         return iter;
      }
      
      void erase(int index)
      {
         // check index range
         if (index < 0 || index >= numItems)
         {
            throw std::out_of_range("Index to erase is out of range");
         }
         
         // close up data and overwrite data to be erased
         for (int i= index+1; i<numItems; i++)
         {
            theData[i-1] = theData[i];
         }
         numItems--;
      }
      
      void pop_back()
      {
         erase(numItems-1);
      }
      
      void pop_front()
      {
         erase(0);
      }
      
      /******************************************\
       const and non-const iterators for vector
       \******************************************/
      
      iterator<dataType> begin()
      {
         return iterator<dataType>(this, 0);
      }
      
      const_iterator<dataType> begin() const
      {
         return const_iterator<dataType>(this, 0);
      }
      
      iterator<dataType> end()
      {
         return iterator<dataType>(this, numItems);
      }
      
      const_iterator<dataType> end() const
      {
         return const_iterator<dataType>(this, numItems);
      }
      
      /******************************************\
       find
       \******************************************/
      
      iterator<dataType> find(const dataType &searchData)
      {
         // look for searchData in vector.
         // if found return iterator where found
         // otherwise return end iterator.
         
         for (int i=0; i<numItems; i++)
         {
            if (theData[i] == searchData) return iterator<dataType>(this, i);
         }
         return end();
      }
      
      /*****************************************\
       overloaded operators
       \*****************************************/
      
      // overloaded [] operator
      dataType& operator [] (int index)
      {
         if (index < 0 || index >= numItems)
         {
            throw std::out_of_range("Index to operator [] is out of range");
         }
         return theData[index];
      }
      
      // overloaded const [] operator
      const dataType& operator [] (int index) const
      {
         if (index < 0 || index >= numItems)
         {
            throw std::out_of_range("Index to operator [] is out of range");
         }
         return theData[index];
      }
      
      // overloaded assignment operator
      vector<dataType>& operator = (const vector<dataType> &other)
      {
         // get rid of current data in this vector
         if (theData != NULL) delete [] theData;
         
         // set vector capacity and number of items stored
         currentCapacity = other.currentCapacity;
         numItems = other.numItems;
         
         // allocate memory to accept copies of data from other vector
         theData = buildDataArray(currentCapacity);
         
         // copy data from other vector into this vector
         for (int i=0; i<numItems; i++)
         {
            theData[i] = other.theData[i];
         }
         
         return *this;
      }
   };
}

#endif