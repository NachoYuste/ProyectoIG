// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h
//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz{
	
	public:
		LuzPosicional(Tupla3f posicion , GLenum idLuzOpenGL,
						  Tupla4f colorAmbiente ={0.0f, 0.0f, 0.0f, 1.0f},
						  Tupla4f colorEspecular =  {1.0f, 1.0f, 1.0f, 1.0f},
					 	  Tupla4f colorDifuso = {1.0f, 1.0f, 1.0f, 1.0f});
		void animar();
	
private:
	float suma_pos_x=5;
};


#endif
