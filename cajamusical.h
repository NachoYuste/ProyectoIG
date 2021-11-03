// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cajamusical.h
//
// #############################################################################

#ifndef CAJAMUSICAL_H_INCLUDED
#define CAJAMUSICAL_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "bailarina.h"
#include "textura.h"

class CajaMusical: public Malla3D{

	class BailarinaGiratoria{
		public:
			BailarinaGiratoria();
			
			void draw(set<modo_vis>modos, bool modo_dif);
			
			void activaMateriales(bool activar);
			void setTexturas();
			
			void rotaBailarina(float b);
		
			void animar();
			void cambiaFactorVelocidad(float new_factor);
			void setTPose();
			void setPoseBaile();
			
			void aumentaGradosLibBD(float gl);
			void aumentaGradosLibPD(float gl);
			void aumentaGradosLibBI(float gl);
			void aumentaGradosLibPI(float gl);
			
			void imprimeValores();
			
		private:
			Cilindro *base= nullptr;
			Bailarina *bailarina = nullptr;
			float beta;
			
			Material *mat_base = nullptr;
			bool mat_on;
	};
	
	public:
		CajaMusical();
		
		void draw(set<modo_vis>modos, bool modo_dif);
		
		void activaMateriales(bool activar);
		void setTexturas();
		
		void rotaTapa(float a);
		void rotaBailarina(float giro);
		void subeBase(float ele, float giro);
		
		void animar();
		void animaBailarina();
		void cambiaFactorVelocidad(float new_factor);
		void setTPose();
		void setPoseBaile();
		
		void aumentaGradosLibBD(float gl);
		void aumentaGradosLibPD(float gl);
		void aumentaGradosLibBI(float gl);
		void aumentaGradosLibPI(float gl);
		
		bool estaArriba();
		void imprimeValores();

	private:
		Cubo *caja = nullptr;
		Cubo *tapa = nullptr;
		Cubo *agujero = nullptr;
		BailarinaGiratoria *bailarinagir = nullptr;

		float alfa;
		float elevacion;
		
		//Materiales
		bool mat_on;
		Material *caja_tapa = nullptr;
		Material *mat_agujero = nullptr;
		
		//Texturas
		Textura * tex_caja = nullptr;
		
		//Animacion
		float factor_velocidad;
		bool esta_arriba;
};

#endif
