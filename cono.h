// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h
//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clase derivada de ObjRevolucion
//
// *****************************************************************************

// *****************************************************************************

class Cono : public ObjRevolucion
{
   public:
   	Cono(const int num_instancias_perf,
				const float altura, 
				const float radio);
	private:
		vector<Tupla3f> perfil_creado;
} ;

#endif
