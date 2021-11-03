// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: pierna.h
//
// #############################################################################

#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"

class Pierna : public Malla3D
{
	class Pie{
		public:
			Pie();
		
			void draw(set<modo_vis> modos, bool modo_dif);
			void setMaterial(Material mat);
			
		
		private:
			Cubo *pie = nullptr;
			Cilindro *pierna = nullptr;
			Esfera *rodilla = nullptr;
	};
	
	public:
		Pierna();
		
		void draw(set<modo_vis> modos, bool modo_dif);
		void setMaterial(Material mat);
		void elevaRodilla(float a=0);
		
	private:
		Cilindro *muslo = nullptr;
		Esfera *cadera = nullptr;
		Pie *pie = nullptr;
		float alfa; 
		
	
};

#endif
