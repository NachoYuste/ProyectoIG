// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuerpo.h
//
// #############################################################################

#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cono.h"

class Cuerpo: public Malla3D
{

	public:
		Cuerpo();
		
		void draw(set<modo_vis> modos, bool modo_dif);
		void setMaterial(Material mat);
		void setTexturas();
		
	private:
		Cono *partesup = nullptr;
		Cono *parteinf = nullptr;
		
		Textura *tex_falda = nullptr;
};

#endif
