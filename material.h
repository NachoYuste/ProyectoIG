// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material{
	
	public:
		Material(Tupla4f amb, Tupla4f dif, Tupla4f esp, GLfloat bri);
		Material(Material &mat);
		void aplicar();
		
		
	
	private:
		Tupla4f especular;
		Tupla4f ambiente;
		Tupla4f difuso;
		GLfloat brillo;
};

#endif

