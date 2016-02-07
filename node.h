#ifndef NODE_H
#define NODE_H

#include "value.h"

/** Struttura rappresentante un nodo della classe cbuffer */

template <typename T> struct Node
{	
	Value <T> value; ///< Valore del nodo preso da value.h
	Node *next; ///< Puntatore al prossimo nodo
	
	/** Costruttore di default */
	Node ()
	{
		value = 0;
		next = 0;
	}
	/** Costruttore che inizializza con valore passato 
		@param _app valore che viene passato */
	Node (const T &_app)
	{
		value = _app;
		next = 0;
	}
	/** Distruttore */
	~Node() 
	{
	}
	
	/** Copy contructor
		@param oth nodo che viene copiato */
	Node (const Node &oth)
	{
		value = oth.value;
		next = oth.next;
	}
	
	/** Override operatore di assegnamento
		@param oth nodo da copiare */
	Node &operator = (const Node &oth)
	{
		if (this != &oth)
		{
			Node app(oth);
			
			std::swap(this->value, app.value);
			std::swap(this->next, app.next);
		}
		return *this;
	}
};

#endif
