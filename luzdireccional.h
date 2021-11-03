// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h
//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz{
	
	protected:
		float alpha;
		float beta;
		
	public:
		
		LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL,
							Tupla4f colorAmbiente ={0.0f, 0.0f, 0.0f, 1.0f},
							Tupla4f colorEspecular =  {1.0f, 1.0f, 1.0f, 1.0f},
							Tupla4f colorDifuso = {1.0f, 1.0f, 1.0f, 1.0f});
		
		void variarAnguloAlpha(float incremento);
		void variarAnguloBeta(float incremento);
	
};
#endif
