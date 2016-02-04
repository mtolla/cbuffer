#include "cbuffer.h"

struct tVocali 
{
	bool operator()(char _app) const 
	{
		return (_app == 'a'|| _app == 'e'|| _app == 'i'|| _app == 'o'|| _app == 'u'
				||_app == 'A'|| _app == 'E'|| _app == 'I'|| _app == 'O'|| _app == 'U');
	}
};

template<typename T>
void print_buffer(cbuffer<T> &buffer) 
{
	std::cout << buffer << std::endl;
	std::cout << "Numero elementi: " << buffer.nEle() << std::endl;
	std::cout << "Dimensione massima: " << buffer.dim() << std::endl;
	std::cout << std::endl;
}

void test() 
{
	std::cout << "Creazione di un buffer di caratteri con grandezza fissata a 7: " << std::endl;
	std::cout << "cbuffer<char> buffer(7): ";
	cbuffer<char> buffer(7);
	print_buffer(buffer);
	std::cout << "Stampa del buffer: "<<std::endl;
	std::cout << "Cattura eccezione: cbuffer<char> bufferError(0)" << std::endl;
	try 
	{
		cbuffer<char> bufferError(0);
	}
	catch (std::runtime_error &e) 
	{
		std::cout << e.what() << std::endl;
		std::cout << std::endl;
	}
	
	std::cout << "Inserimento di 7 caratteri:" << std::endl;
	buffer.add('a');
	std::cout << "a:" << std::endl;
	std::cout << buffer << std::endl;
	buffer.add('b');
	std::cout << "b:" << std::endl;
	std::cout << buffer << std::endl;
	buffer.add('c');
	std::cout << "c:" << std::endl;
	std::cout << buffer << std::endl;
	buffer.add('d');
	std::cout << "d:" << std::endl;
	std::cout << buffer << std::endl;
	buffer.add('e');
	std::cout << "e:" << std::endl;
	std::cout << buffer << std::endl;
	buffer.add('o');
	std::cout << "o:" << std::endl;
	std::cout << buffer << std::endl;
	buffer.add('u');
	std::cout << "u:" << std::endl;
	std::cout << buffer << std::endl<< std::endl;
	
	std::cout << "Inserimento di un ulteriore carattere, test buffer circolare:" << std::endl;
	buffer.add('K');
	std::cout << "buffer.add('K')" << std::endl;
	std::cout << buffer << std::endl<< std::endl;
	
	
	std::cout << "Stampa e modifica del quinto elemento: " << std::endl;
	std::cout << "old: buffer[4]: " ;
	std::cout << buffer[4] << std::endl;
	std::cout << "new: buffer[4] = K" << std::endl;
	buffer[4] = 'K';
	std::cout << buffer << std::endl<< std::endl;
	std::cout << "Modifica del quinto elemento: " << std::endl;
	std::cout << ">> buffer[4]" << std::endl<< std::endl;
	try 
	{
		buffer[0];
	}
	catch (std::runtime_error &e) 
	{
		std::cout << e.what() << std::endl;
		std::cout << std::endl<< std::endl;
	}
	
	std::cout << "Test con funzione globale check, controllo se il carattere è una vocale: " << std::endl;
	std::cout << ">> check(buffer, vocali)" << std::endl;
	tVocali vocali;
	check(buffer, vocali);
	std::cout << std::endl;
	
	std::cout << "Creazione di un puntatore a char collegato al buffer: " << std::endl;
	cbuffer<char> *nBuffer;
	std::cout << "nBuffer = buffer" << std::endl;
	nBuffer = &buffer;
	std::cout << "nBuffer: ";
	print_buffer(*nBuffer);
	
	std::cout << "Eliminazione elementi: " << std::endl;
	int _dim = buffer.dim();
	for(int i = 0; i < _dim; i++) {
		std::cout << "buffer.del()" << std::endl;
		buffer.del();
		print_buffer(buffer);
	}
	std::cout << "Test cattura eccezione, da buffer vuoto: buffer.del()" << std::endl;
	try {
		buffer.del();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
	}
}

int main() {
	test();
	
	return 0;
}
