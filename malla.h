// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################


#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
#include <iostream>


// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {PUNTOS, LINEAS, SOLIDO, AJEDREZ, LUZ, TEXTURA}modo_vis;

class Malla3D
{
	 public:

		// función que redibuja el objeto
		// está función llama a 'draw_ModoInmediato' (modo inmediato)
		// o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
		void draw(set<modo_vis> modos, bool modo_dif);
		void setMaterial(Material mat); 
		void setTextura(Textura* tex);

	protected:

		// dibuja el objeto en modo inmediato
		void draw_ModoInmediato();

		// dibuja el objeto en modo diferido (usando VBOs)
		void draw_ModoDiferido();

		void calcular_normales(); // calcula tabla de normales de vértices 
		
		//Calcula los vectores normales a los caras de la malla
		vector<Tupla3f> calcular_normales_caras();
		
		// Crea un objeto GLuint inicializado a 0
		GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

		// Pinta las caras de los polígonos
		void PintaCaras();

		// Pinta las lineas de los polígonos
		void PintaLineas();
		
		void setModos(set<modo_vis> modos);	//Funcion aux para actualizar modos de visualizacion
		
		set<modo_vis> modos_vis;	//modos de dibujado
		
		//ED de malla
		vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por 	értice, con tres floats)
		vector<Tupla2f> ct;
		vector<Tupla3f> nv;	// array de normales de vértices
		vector<Tupla3i> f ; 	// una terna de 3 enteros por cada cara o triángulo
		vector<Tupla3i> f_par;		//ternas para caras pares
		vector<Tupla3i> f_impar;	//ternas para caras impares
		vector<Tupla3f> c;	// array de colores
		vector<Tupla3f> c1;	// array de colores caras pares
		vector<Tupla3f> c2;	// array de colores impares impares
		
		int tam_vcaras;	//Tamaño del vector de caras para implementación de tapas
		
		Material *m = nullptr;	//Material de la malla para iluminación
		Textura *text = nullptr; //Textura del objeto
		
		//VBOs
   	GLuint id_vbo_ver = 0;	
		GLuint id_vbo_nv = 0;	//VBO para normales de vértices
   	GLuint id_vbo_tri = 0;	     //Caras para modos lineas-puntos-solido
		GLuint id_vbo_tri_par = 0;   //Caras pares para modo ajedrez
		GLuint id_vbo_tri_impar = 0; //Caras impares para modo ajedrez
		GLuint id_vbo_c = 0;	 //Colores para modo solido
		GLuint id_vbo_c1 = 0; //Colores para caras pares de modo ajedrez
		GLuint id_vbo_c2 = 0; //Colores para caras impares de modo ajedrez
		
} ;


#endif
