#ifndef _BINTREE_CONST_ITERATOR_H
#define _BINTREE_CONST_ITERATOR_H

/**************************************************\ 
   template const_iterator class for binary tree 
\**************************************************/ 

template <typename dataType> class const_iterator 
{ 
   private: 
      const bintree<dataType> *parent; 
      const binnode<dataType> *current;
 
   public: 
      // constructor 
      const_iterator() : parent(NULL), current(NULL) 
      { 
      } 
      
      const_iterator(const bintree<dataType> *myParent, const binnode<dataType> *position) : 
         parent(myParent), current(position) 
      { 
      } 
         
      const_iterator(const bintree<dataType> *myParent) : parent(myParent)
      { 
         // create iterator and set it pointing to 
         // node with lowest value in tree
         current = parent->root;
         while (current->left != NULL) current = current->left;
      } 
 
      /********************************************\
         access operators
      \********************************************/
         
      // overloaded dereference operator 
      const dataType& operator * () const 
      { 
         if (current == NULL) 
         { 
            throw std::invalid_argument("Attempting to dereference outside tree"); 
         } 
         return current->nodeData; 
      } 
         
      // overloaded arrow operator 
      const dataType* operator -> () const 
      { 
         if (current == NULL) 
         { 
            throw std::invalid_argument("Attempting to reference outside tree"); 
         } 
         return &(current->nodeData); 
      } 
         
      /********************************************\
         increment operators
      \********************************************/
 
      // overloaded prefix increment operator. eg ++i;
      const_iterator<dataType> operator ++ () 
      { 
         if (current == NULL) 
         { 
            throw std::invalid_argument("Attempting to increment outside tree"); 
         } 
         
         if (current->right != NULL)
         {
            // there is a right sub-branch.
            // move down to smallest node in that branch
            current = current->right;
            while (current->left != NULL) current = current->left;
         }
         else
         {
            // otherwise move up tree till we find a greater value
            const dataType *currentData = &(current->nodeData);
            do
            {
               current = current->root;
            } while (current != NULL && current->nodeData < *currentData);
         }
         return *this; 
      } 
 
      // overloaded postfix increment operator. eg i++;
      const_iterator<dataType> operator ++ (int) 
      { 
         const_iterator<dataType> current_data = *this; 
         ++(*this); 
         return current_data; 
      } 
         
      /********************************************\
         decrement operators
      \********************************************/
         
      // overloaded prefix decrement operator. eg --i;
      const_iterator<dataType> operator -- () 
      { 
         if (current == NULL) 
         { 
            throw std::invalid_argument("Attempting to decrement outside tree"); 
         } 
         
         if (current->left != NULL)
         {
            // there is a left sub-branch.
            // move down to largest node in that branch
            current = current->left;
            while (current->right != NULL) current = current->right;
         }
         else
         {
            // otherwise move up tree till we find a smaller value
            dataType *currentData = &(current->nodeData);
            do
            {
               current = current->root;
            } while (current != NULL && current->nodeData > *currentData);
         }
         return *this; 
      } 
 
      // overloaded postfix decrement operator. eg i--;
      const_iterator<dataType> operator -- (int) 
      { 
         const_iterator<dataType> current_data = *this; 
         --(*this); 
         return current_data; 
      } 
         
      /********************************************\
         equality operators
      \********************************************/
         
      // overloaded equality operator 
      bool operator == (const const_iterator<dataType> &other) const
      { 
         return (current == other.current); 
      } 
 
      // overloaded inequality operator 
      bool operator != (const const_iterator<dataType> &other) const
      { 
         return (current != other.current); 
      } 
}; 

#endif