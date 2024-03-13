#include "Stack.h"

/***************************************************************/
/* Programmer: Martyna Wieczorek                               */ 
/* Purpose: Linked Stack class  -   implementation file        */
/***************************************************************/

template <class T>
Stack<T> :: Stack ()
{
  top = NULL; 
}

template <class T>
Stack<T> :: ~Stack()
{
   destroy();
}

template <class T>
Stack<T> :: Stack ( const Stack<T> & other )
{
   copy (other);
}

template <class T>
const Stack<T> & Stack<T> :: operator= ( const Stack<T> & other )
{
  if ( this != &other )
   {
      destroy();
      copy (other);
   }
   return *this;
}

template <class T>
bool Stack<T> :: isEmpty ()
{
    return top == NULL; 
}

template <class T>
void Stack<T> :: push ( T item )
{
   node<T> *temp = new node<T>;			
   temp->info = item;						
   temp->next = top;			
   top = temp;			
}                               

template <class T>
void Stack<T> :: pop ()
{
   if ( !isEmpty())
   {
      node<T> *temp = top;		
      top = top->next;		
      delete temp;		
   }
}

template <class T>
T Stack<T>::getTop() 
{
    if (!isEmpty())
      return top->info;
    else
    {
      cout << "Error: Stack is empty." << endl;
      return 0;
    }
}

template <class T>
void Stack<T> :: copy (const Stack<T> & other)
{
   if ( other.top == NULL )
      top = NULL;
   else
   {
      top = new node<T>;
      top->info = other.top->info;
      node<T> *p = other.top->next;
      node<T> *q = top;

      while ( p != NULL )
        {
           q->next = new node<T>;
           q = q->next;
           q->info = p->info;
           p = p->next;
        }

       q->next = NULL;
   }
}

template <class T>
void Stack<T> :: destroy()
{
  node<T> *p;

    while ( top != NULL )
      {
         p = top;
         top = top->next;
         delete p;
      }
}