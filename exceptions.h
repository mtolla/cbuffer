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
class Error_nEle : public std::runtime_error 
{
	public:
	/** Costruttore che riceve un messaggio		
		@param mes messaggio dell'errore */
	Error_nEle(const char *mes) : std::runtime_error(mes) 
	{
	}	
};

/** Eccezione custom
	Errore fuoriuscita dal buffer */
class IndexOutOfBound : public std::runtime_error 
{
	public:
	/** Costruttore che riceve un messaggio		
	@param mes messaggio dell'errore */
	IndexOutOfBound(const char *mes) : std::runtime_error(mes) 
	{
	}	
};

#endif
