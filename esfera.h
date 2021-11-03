// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: esfera.h
//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clase derivada de ObjRevolucion
//
// *****************************************************************************

// *****************************************************************************

class Esfera : public ObjRevolucion
{
   public:
   	Esfera(const int num_ver_perfil,
					const int num_instancias_perf, 
					const float radio) ;
	private:
		vector<Tupla3f> perfil_creado;
} ;

#endif
