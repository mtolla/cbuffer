#ifndef CBUFFER_H
#define CBUFFER_H

#include <iostream>
#include "node.h"
#include "exceptions.h"

/** Implementazione di una classe per la gestione di un buffer circolare.
	
	Essendo una classe templata alla creazione di un suo oggetto andrà specificato 
	il tipo di elementi che verranno utilizzati
	
	Dimensione di default: 1 cella */

template <typename T> class cbuffer 
{
	//PUBLIC
	
	public:
	
	/** Costruttore di default */
	cbuffer()
	{
		_begin = 0;
		_end = 0;
		_nEle = 0;
		_dim = 1;
		// Genero il tutto
		create(1);
	}
	
	/** Costruttore avente grandezza impostata */
	cbuffer(int _app)
	{
		_begin = 0;
		_end = 0;
		_nEle = 0;
		_dim = _app;
		// Genero il tutto
		create(_app);
	}
	
	/** Distruttore */
	~cbuffer()
	{
		Node<T> *_app = _begin;
		Node<T> *_app2 = 0;
		for(int i = 0; i <= _dim; i++) 
		{
			_app2 = _app->next;
			delete _app;
			_app = _app2;
		}
	}
	
	/** Copy constructor
		@param oth nodo che viene copiato */
	cbuffer(const cbuffer &oth)
	{
		_begin = new Node<T>(oth._begin->value.value());
		Node<T> *_app = _begin;
		Node<T> *_app2 = oth._begin->next;
		for (int i = 1; i <= _dim; i++)
		{
			_app->next = new Node<T>(_app2->value.value());
			_app = _app->next;
			_app2 = _app2->next;
		}
		_app->next = _begin;
		_end = _app;
		
	}
	
	/** Override operatore di assegnamento
		@param oth nodo da copiare 
		@return *this */
	cbuffer &operator = (const cbuffer &oth) 
	{
		if(this != &oth) 
		{
			cbuffer<T> _app(oth);
			
			std::swap(this->_begin, _app._begin);
			std::swap(this->_end, _app._end);
			std::swap(this->_nEle, _app._nEle);
			std::swap(this->_dim, _app._dim);
		}
		return *this;
	}
	
	/** Operatore di indirizzamento richiesto dal progetto.
		@param _index indice del nodo
		@return reference richiesto
		@throw IndexOutOfBound errorein caso di uscita dal buffer */
	T &operator [] (const int _index) 
	{
		if(_index < _nEle) 
		{
			Node<T> *_app = _begin;
			
			for(int i = 0; i != _index; i++) 
			{
				_app = _app->next;
			}
			
			return _app->value.value();
		}
		else 
			throw indexOutOfBound("Error: Index out of bound.");
	}
	
	/** Operatore di indirizzamento costante richiesto dal progetto.
		@param _index indice del nodo
		@return reference richiesto costante
		@throw indexOutOfBound errorein caso di uscita dal buffer */
	const T &operator[](const int _index) const 
	{
		if(_index < _nEle) 
		{
			Node<T> *_app = _begin;
			
			for(int i = 0; i != _index; i++) 
			{
				_app = _app->next;
			}
			
			return _app->value.value();
		}
		else 
			throw indexOutOfBound("Error: Index out of bound.");
	}
	
	/** Inserimento di un valore in coda
		@param value valore da inserire */
	void add(const T &value) 
	{
		if(_nEle == _dim) 
		{
			_begin = _begin->next;
			_end->value.value() = value;
			_end = _end->next;
		}
		else
		{
			_end->value.value() = value;
			_end = _end->next;
			_nEle++;
		}
	}
	
	/** Eliminazione di un valore dalla testa
		@throw emptyBuffer se non sono presenti valori da eliminare */
	void del() 
	{
		if(_nEle != 0) 
		{
			_begin->value.value() = 0;
			_begin = _begin->next;
			_nEle--;
		}
		else
			throw emptyBuffer("Error: Buffer already empty.");
	}
	
	/** Restituzione dimensione attuale del buffer 
		@return _Ele numero degli elementi presenti */
	int nEle() 
	{
		return _nEle;
	}
	
	/** Restituzione dimensione massima del buffer
		@return _dim variabile impostata durante la creazione del buffer */
	int dim()
	{
		return _dim;
	}
	
	/** Implementazione classe iteratore costante */
	
	class Iterator
	{
		const Node<T> *node; ///< nodo 
		friend class cbuffer; ///< da l'accessibilità alla classe cbuffer
	
		//PUBLIC
		
		public:
		
		typedef std::forward_iterator_tag iterator_category;
		typedef Node<T> value_type;
		typedef const Value<T>* pointer;
		typedef const Value<T>& reference;
		
		/** Costruttore di default */
		Iterator()
		{
			node = 0;
		}
		
		/** Distruttore */
		~Iterator() 
		{
		}
		
		/** Copy constructor	
			@param oth iteratore che viene copiato */
		Iterator(const Iterator &oth)
		{
			node = oth.node;
		}
		
		/** Override operatore di assegnamento
			@param oth iteratore da copiare
			@return *this */
		Iterator &operator=(const Iterator &oth) 
		{
			if(this != &oth) 
			{
				Iterator _app(oth);
				
				std::swap(this->node, _app.node);
			}
			return *this;
		}
		
		/** Dereferenziamento per reference
			@return riferimento costante all'oggetto che contiene il valore */
		const Value<T> &operator* () const 
		{
			return node->value;
		}
		
		/** Dereferenziamento per puntatore
			@return puntatore costante all'oggetto che contiene il valore */
		const Value<T> *operator-> () const 
		{
			return &(node->value);
		}
		
		/** Post-incremento
			@return iteratore alla value precedente */
		Iterator operator++(int) 
		{
			Iterator _app(*this);
			node = node->next;
			return _app;
		}
		
		/** Pre-incremento			
			@return iteratore al nodo successivo */
		Iterator &operator++ () 
		{
			node = node->next;
			return *this;
		}
		
		/** Confronto uguaglianza			
			@oth iteratore da confrontare
			@return true se i due iteratori puntano al medesimo nodo, altrimenti false
		*/
		bool operator==(const Iterator &oth) const 
		{
			return node == oth.node;
		}
		
		/** Confronto diversità			
			@oth iteratore da confrontare
			@return true se i due iteratori non puntano al medesimo nodo, altrimenti false
		*/
		bool operator!= (const Iterator &oth) const 
		{
			return node != oth.node;
		}
		
		//PRIVATE
		
		private:
		
		/**
			Costruttore secondario di inizializzazione.
			@param _node puntatore ad un nodo del buffern*/
		Iterator(const Node<T> *_node) : node(_node) 
		{
		}
	
	};
	
	/** Iteratore dell inizio della sequenza
		@return l'iteratore dell inizio della sequenza */
	Iterator begin() const 
	{
		return Iterator(_begin);
	}
	
	/** Iteratore della fine della sequenza		
		@return l'iteratore della fine della sequenza */
	Iterator end() const 
	{
		return Iterator(_end);
	}
	
	//PRIVATE
	
	private:
	Node<T> *_begin; ///< Puntatore al nodo iniziale
	Node<T> *_end; ///< Puntatore al nodo finale
	int _nEle; ///< Numero di elementi attualmente presenti
	int _dim; ///< Dimensione totale del buffer
	
	/** Metodo di creazione di un buffer a dimensione impostata
		@param _app dimensione del buffer
		@throw errorNEle grandezza incorretta */
	void create (int _dim)
	{
		if (_dim >=1)
		{
			_begin = new Node<T>();
			_end = _begin;
			Node<T> *_app = _begin;
			for (int i = 1; i <= _dim; i++)
			{
				_app->next = new Node<T>();
				_app = _app->next;
				
			}
			_app->next = _begin;
		}
		else throw errorNEle("Error: The buffer size must be greather than 0");
	}

};

/**	Stampa a video del buffer
	@param oS stream di output
	@param buf buffer da stampare
	@return oS stream di output
*/
template <typename T> std::ostream &operator<<(std::ostream &oS, cbuffer<T> &buf) 
{
	typename cbuffer<T>::Iterator iter;
	
	oS << "[";
	for(iter = buf.begin(); iter != buf.end(); iter++) 
	{
		if(iter != buf.begin()) 
		{
			oS << ",";
		}
		oS << iter->value();
	}
	oS << "]";
	return oS;
}

/** Test dei valori del cbuffer rispetto al predicato
	@param buf buffer da valutare
	@param pred predicato con cui valutare gli elementi del buffer
*/
template <typename T, typename P> void check(cbuffer<T> &buf, P &pred) 
{
	typename cbuffer<T>::Iterator bu;
	int i;
	for(bu = buf.begin(), i = 0; bu != buf.end(); bu++, i++) 
	{
		if(pred(bu->value())) 
		{
			std::cout << i << ": true" << std::endl;
		}
		else 
		{
			std::cout << i << ": false" << std::endl;
		}
	}
}

#endif
