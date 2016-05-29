#ifndef BINTREE_H_
#define BINTREE_H_

#include <stdexcept>
    
namespace treespc
{
   // forward class declaration
   template <typename dataType> class bintree;
   template <typename dataType> class binnode;

   #include "const_iterator.h"
   #include "binnode.h"

   /********************************************************\
      template class for a binary tree
   \********************************************************/
      
   template <typename dataType> class bintree
   {
      friend const_iterator<dataType>;
   
      private:
         binnode<dataType> *root;
         int numItems;
         
         void throw_exception(const char* message)
         {
            throw ::std::invalid_argument(message);
         }

         double lg(int a) const
         {
            // return log base 2 of a
            
            return (log((double) a) / log(2.0));
         }
         
      public:
        
         /*******************************************************\
            constructors & destructors
         \*******************************************************/
         
         // constructor
         bintree() : root(NULL), numItems(0) {}

         // copy constructor
         bintree(const bintree<dataType> &other) : numItems(other.numItems) 
         {
            if (other.root != NULL) 
            {
               root = new binnode<dataType>(*(other.root));
            }
            else 
            {
               root = NULL;
            }
         }
         
         // destructor
         ~bintree() 
         {
            if (root != NULL) delete root;
         }
              
         /*******************************************************\
            tree information
         \*******************************************************/
         
         bool empty() const 
         {
            return (numItems == 0);
         }
         
         int size() const 
         {
            return numItems;
         }
           
         /*******************************************************\
            iterator functions
         \*******************************************************/
         
         const_iterator<dataType> begin() const
         {
            return const_iterator<dataType>(this);
         }
         
         const_iterator<dataType> end() const
         {
            return const_iterator<dataType>(this, NULL);
         }
         
         /*******************************************************\
            insertion erasure and find functions
         \*******************************************************/
         
         void insert(const dataType& newData) 
         {
            if (root == NULL) 
            {
               root = new binnode<dataType>(newData, NULL);
            } 
            else 
            {
               root->insert(newData);
            }
            numItems++;
         }
         
         void erase(const dataType& delData) 
         {
            if (root == NULL) 
            {
               throw_exception("data does not exist in tree to erase");
            }
            
            root->erase(root, delData);
            
            numItems--;
         }
         
         const_iterator<dataType> find(const dataType &findData) const 
         {
            if (root == NULL) 
            {
               return end();
            }
            else 
            {
               return const_iterator<dataType>(this, root->find(findData));
            }
         }    

         void rebalance()
         {
            // Rebalance tree using the AVL algorithm
            // While this does not guarantee a perfectly balanced tree
            // it does make it mostly balanced by guaranteeing that the difference
            // in depth between every right and left subtree is at most 1
            
            if (root != NULL) 
            {
               while (root->rebalance(root));
            }
         }
         
         /*******************************************************\
            tree analysis
         \*******************************************************/
         
         double balance() const
         {
            // Returns a measure of how balanced a tree is.
            // a perfectly balanced tree will have a balance of 1.
            // a reasonably balanced tree will have a balance >= 0.5 and < 1
            // an unbalanced tree will have a balance < 0.5
            
            if (numItems == 0) return 1.0;
            
            return lg(numItems+1) / root->height();
         }
         
         int height() const
         {
            if (numItems == 0) return 0;
            return root->height();
         }
         
         int numLeafNodes() const
         {
            if (numItems == 0) return 0;
            return root->numLeafNodes();
         }

         /*******************************************************\
            overloaded operators 
         \*******************************************************/

         bintree<dataType>& operator = (const bintree<dataType> &other) 
         {
            if (root != NULL) 
            {
               delete root;
               numItems = 0;
            }
            
            if (other.root != NULL) 
            {
               root = new binnode<dataType>(*(other.root));
               numItems = other.numItems;
            }
            return *this;
         }
   };
}

#endif
