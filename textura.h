// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Textura.h
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include "jpg_imagen.hpp"

class Textura{
	
	public:
		Textura(const string& archivo);
		void activar();
	
	private:
		GLuint textura_id = 0;
		vector<unsigned char> data;
		int width,height;
};

#endif
