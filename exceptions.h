#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept> // std::runtime_error

/** Eccezione custom
	Buffer già vuoto */
class emptyBuffer : public std::runtime_error {
	public:
	/** Costruttore che riceve un messaggio		
		@param message messaggio dell'errore */
	emptyBuffer(const char *message) : std::runtime_error(message) 
	{
	}	
};

/** Eccezione custom
	Errore dimensione buffer */
class errorNEle : public std::runtime_error 
{
	public:
	/** Costruttore che riceve un messaggio		
		@param mes messaggio dell'errore */
	errorNEle(const char *mes) : std::runtime_error(mes) 
	{
	}	
};

/** Eccezione custom
	Errore fuoriuscita dal buffer */
class indexOutOfBound : public std::runtime_error 
{
	public:
	/** Costruttore che riceve un messaggio		
	@param mes messaggio dell'errore */
	indexOutOfBound(const char *mes) : std::runtime_error(mes) 
	{
	}	
};

#endif
