#ifndef VALUE_H
#define VALUE_H

#include <algorithm> // std::swap

template <typename T> class Value 
{
	
	//PUBLIC
	
	public:
	
	/** Costruttore di default */
	Value()
	{
		_value = 0;
	}
	
	/** Costruttore inizializza il valore 
		@param value valore inizializzato */
	Value(const T &value) 
	{
		_value = value;
	}
	
	/** Distruttore */
	~Value() 
	{
	}
	
	/** Copy constructor 
		@param oth valore che viene copiato */
	
	Value(const Value &oth) 
	{
		_value= oth._value; 
	}
	
	/** Restituzione costante reference valore 
		@return _value tramite reference costante */
	
	const T &value() const
	{
		return _value;
	}
	
	/** Restituzione reference valore 
		@return _value tramite reference */
	
	T &value() 
	{
		return _value;
	}
	
	/** Override operatore assegnamento
		@param _oth valore da copiare
		@return *this valore chiamante */
	
	Value &operator = (const Value &_oth)
	{
		if (this != &_oth)
		{
			Value _app(_oth);
			std::swap(_value, _app._value);
		}
		return *this;
	}
	
	// PRIVATE 
	
	private:
	T _value;
	
};

#endif
