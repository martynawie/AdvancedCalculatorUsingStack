#include <iostream>
using namespace std;

/***************************************************************/
/* Programmer: Martyna Wieczorek                               */
/* Purpose: linked stack class                                 */ /***************************************************************/

#ifndef STACK_H
#define STACK_H

template <class T>
struct node
{
   T info;
   node *next;
};

template <class T>
class Stack
{
   private:
     node<T> *top;  

   public:
      //Constructor 
      Stack();
      //Destructor
      ~Stack();
      //Copy constructor
      Stack ( const Stack<T> & other);
      //Overloaded =  
      const Stack<T> & operator= (const Stack<T> & other);
      //Returns true if stack is empty, false otherwise
      bool isEmpty();
      //Insert an item
      void push(T item);
      //Deletes top item from stack. 
      void pop(); 
      //Return top of any data type
      T getTop ();
      //Copy function
      void copy (const Stack<T> & other);
      //Destroys the stack
      void destroy();    
};
#endif

