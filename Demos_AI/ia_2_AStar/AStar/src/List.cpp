// List.cpp: implementation of the Node class.
//
//////////////////////////////////////////////////////////////////////

#include "List.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

List::List()
{
   size = 0;
   prim = NULL;
}
	
Node* List::insert(Node *node, bool aloca)
{
   Node *n;
	 
   if(aloca==true)
      n = new Node(node);
   else
      n = node;
   if (prim==NULL)
   {
      prim = n;
      prim->next = prim->prev = NULL;
   }
   else
   {
      n->next = prim;
      prim->prev = n;
      n->prev = NULL; 
      prim = n;
   }
   size++;
   return n;
}


void List::remove(Node * node, bool libera)
{
   Node *n = find(node);
   //unico elemento
   if(n->prev==NULL && n->next==NULL)
   {
      prim = NULL;
   }
   //renove do inicio, com mais de um elemento
   else if(n->prev==NULL)
   {
      prim = prim->next;
      prim->prev = NULL;
   }
   //remove ultimo
   else if(n->next==NULL)
   {
      n->prev->next = NULL;
   }
   else //meio
   {
      n->prev->next = n->next;
      n->next->prev = n->prev;
   }	
   //indica se o no sera ou nao desalocado. Eh deletado em inOpen ou inClosed
   //Em caso de getMinF, nao eh deletado
   if(libera==true)
      delete n;
   size--;
}

Node* List::find(Node *node)
{
   Node *tmp = prim;

   while( tmp != NULL )
   {
      if( tmp->equals(node) ) 
      {
         return tmp;
      }
      tmp=tmp->next;
   }
   return NULL;
}

Node* List::find(int x, int y)
{
   Node *tmp = prim;
   while( tmp != NULL )
   {
      if( tmp->x == x && tmp->y == y ) 
	  {
         return tmp;
	  }
      tmp=tmp->next;
   }
   return NULL;
}


void List::clear()
{
   Node *tmp = prim, *prox;
   while(tmp!=NULL)
   {
      prox = tmp->next;
      delete tmp;
      tmp = prox;
   }/**/

   prim = NULL;	
   size=0;
}

//remove e retorna o no com menor valor de F=G+H
Node* List::getMinF(void)
{
   Node *min=prim, *tmp = prim;
   float f = prim->f;
   while( tmp != NULL )
   {
      if( tmp->f < f ) 
      {
          f = tmp->f;
          min = tmp;
      }
      tmp=tmp->next;
   }
   remove(min, false);
   return min;
}

bool List::isEmpty()
{
   return (prim == NULL);     
}

//implime a lista
void List::print()
{
   Node *tmp = prim;

   printf("\nCaminho: ");
   while( tmp != NULL )
   {
      printf("(%d,%d)=%.1f ", tmp->x, tmp->y, tmp->g);
   	  tmp = tmp->next;
   }
}

//diz se um vertice (x,y) pertence a lista
bool List::match(int x, int y)
{
   Node *tmp = prim;

   while( tmp != NULL )
   {
      if( tmp->x == x && tmp->y == y)
         return true;
   	  tmp = tmp->next;
   }
   return false;
}