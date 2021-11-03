// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cabeza.h
//	
// #############################################################################

#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "esfera.h"
#include "cilindro.h"

class Cabeza : public Malla3D
{
	public:
		Cabeza();
		void draw(set<modo_vis> modos, bool modo_dif);
		void setMaterial(Material mat);

	private:
		Cilindro *cuello = nullptr;
		Esfera *cab = nullptr;
};

#endif
