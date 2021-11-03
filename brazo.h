// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: brazo.h
//
// #############################################################################

#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "esfera.h"
#include "cilindro.h"

class Brazo : public Malla3D
{
	class Antebrazo{
		public:
			Antebrazo();
			void draw(set<modo_vis> modos, bool modo_dif);
			void setMaterial(Material mat);
			
		private:
			Esfera * codomunieca = nullptr;
			Cilindro * antebrazo = nullptr;
	};
	
	public:
		Brazo();
		void draw(set<modo_vis> modos, bool modo_dif);
		void rotaCodo(float a);
		void setMaterial(Material mat);
		
		
	private:
		Esfera * hombro = nullptr;
		Cilindro * brazo = nullptr;
		Antebrazo * antebrazo = nullptr;
		
		float flex_codo;	
		
};

#endif
