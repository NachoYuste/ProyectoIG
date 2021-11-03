// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
//
// #############################################################################


#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos de luz
//
// *****************************************************************************



class Luz{
	
	public:
		void activar();
		bool getLuzActivada();	//Devuelve si la luz está activa o no
		void setActivacion(const bool act);	//Activa o desactiva la luz

	protected:
		Tupla4f posicion;
		Tupla4f colorAmbiente;
		Tupla4f colorDifuso;
		Tupla4f colorEspecular;
		GLenum id;
		float x = posicion(0);
		float y = posicion(2);
		
		bool luz_activa = false;	//Luz desactivada por defecto
	
	
};




#endif







