// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objrevolucion.h
//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************


class ObjRevolucion : public Malla3D
{
   public:
		ObjRevolucion();
   
		ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   
		ObjRevolucion(std::vector<Tupla3f> per, int num_instancias, bool tapa_sup, bool tapa_inf) ;
		
		void setTapas(bool act);
		void calculaCT();
		
	protected:
		void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);

		//Métodos extra
		bool sentidoAscendente(vector<Tupla3f> perfil);
		void aniadeTapaSuperior(Tupla3f poloN, vector<Tupla3f> perfil_mod);
		void aniadeTapaInferior(Tupla3f poloS, vector<Tupla3f> perfil_mod);

		//Variables de clase
		vector<Tupla3f>perfil;
		int instancias;
		bool tapaS = false;
		bool tapaI = false;
		int tam_sin_caras;
		
};




#endif
