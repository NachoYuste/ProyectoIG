// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: bailarina.h
//
// #############################################################################

#ifndef BAILARINA_H_INCLUDED
#define BAILARINA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "brazo.h"
#include "pierna.h"
#include "cabeza.h"
#include "cuerpo.h"

class Bailarina : public Malla3D
{
	public:
		Bailarina();
		
		void draw(set<modo_vis> modos, bool modo_dif);

		void rotaBrazoI(float rot_hombro, float ele_hombro, float giro_brazo, float codo);
		void rotaBrazoD(float rot_hombro, float ele_hombro, float giro_codo, float codo);
		void rotaPiernaD(float rot_cadera,float ele_cadera, float rodil180a);
		void rotaPiernaI(float rot_cadera,float ele_cadera, float rodilla);
		
		void activaMateriales(bool activar);
		void setTexturas();
		
		void setTPose();
		void setPoseBaile();
		
		void aumentaGradosLibBD(float gl);
		void aumentaGradosLibPD(float gl);
		void aumentaGradosLibBI(float gl);
		void aumentaGradosLibPI(float gl);

		bool brazoDPos0();
		bool brazoIPos0();
		bool piernaDPos0();
		bool piernaIPos0();

		void animar();
		void cambiaFactorVelocidad(float new_factor);
		
		void imprimeValores();

	private:

		Cuerpo *cuerpo = nullptr;
		Brazo *brazoi, *brazod = nullptr;
		Pierna *piernai, *piernad = nullptr;
		Cabeza *cabeza = nullptr;

		float rot_hombrod,rot_hombroi, ele_hombrod, ele_hombroi;
		float giro_brazod, giro_brazoi;
		float codod,codoi;
		float rot_caderad, rot_caderai, ele_caderad, ele_caderai;
		float rodillad, rodillai;

		//Materiales para modo con iluminación
		Material *piel = nullptr;
		Material *vestido = nullptr;
		bool mat_on;
		
		//variables animacion aux
		float factor_velocidad;
		bool moverBD, moverBI, moverPD;
		bool paso1, paso2, paso3;
		bool paso1p, paso2p;
		int giro_brazo_an=-90;
		
};

#endif
