// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: caja.h
//
// #############################################################################

#ifndef BAILARINA_H_INCLUDED
#define BAILARINA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"

class Caja: public Malla3D{

	public:
		Caja();
		void draw(set<modo_vis>modos, bool modo_dif);
		void setMaterial(Material mat);
		void rotaTapa(float a);
		
	private:
		Cubo *caja = nullptr;
		Cubo *tapa = nullptr;
		Cilindro *base_gir = nullptr;
		
		float alfa;	
};

#endif
