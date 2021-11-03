// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h
//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clase derivada de ObjRevolucion
//
// *****************************************************************************

// *****************************************************************************

class Cilindro : public ObjRevolucion
{
   public:
   	Cilindro(const int num_ver_perfil,
					const int num_instancias_perf,
					const float altura, 
					const float radio) ;
	private:
		vector<Tupla3f> perfil_creado;
} ;

#endif
