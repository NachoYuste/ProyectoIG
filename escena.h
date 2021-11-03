#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"
#include "luz.h"
#include "material.h"
#include "textura.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++

#include "bailarina.h"
#include "cajamusical.h"



typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO, ANIMACION} menu;
typedef enum {VACIO, TETRAEDRO, CUBO, PLY, PLY_REV, CILINDRO, CONO, ESFERA, MULTIPLE, MOD_JER} objeto_sel; 
typedef enum {NINGUNA, BD, BI, PD, PI} parte_bailarina;

class Escena
{

	private:
	// ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   // Transformación de cámara
   void change_projection( const float ratio_xy );
   void change_observer();

   void clear_window();

	//Menu
	void printMenu();
	void printEstadoMenu();
	bool esConTapas();
	
   menu modoMenu = NADA;
   objeto_sel objSeleccionado = VACIO;
	set<modo_vis> visualizacion;
	bool modo_dif = false;
	bool tapas = false;
	float alfa = 0;
	float beta = 0;

	//Animacion
	void animacionManual();
	float factor_velocidad;
	bool animacionAutomatica;
	float grado_libertad;
	parte_bailarina parte_sel;
	

   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * ply = nullptr;
	ObjRevolucion * ply_rev = nullptr;
	ObjRevolucion *coke = nullptr; 
	Cilindro * cilindro = nullptr;
	Cono * cono = nullptr;
	Esfera * esfera = nullptr;
	
	
	//Modelo jerárquico
	Bailarina *bailarina = nullptr;
	CajaMusical *cajamusical = nullptr;
	
	//Luces de la escena
	LuzPosicional * luz0 = nullptr;
	LuzDireccional * luz1 = nullptr;
	LuzPosicional * luz2 = nullptr;
	LuzPosicional * luz3 = nullptr;
	bool variarAlfa = false;
	bool variarBeta = false;
	void activaLuces();
   
	//Materiales de la escena
	void aplicaMateriales();
	
	//Texturas de la escena
	bool tex_on = false;
	void aplicaTexturas();
	bool tieneTextura();
 
public:

    Escena();
    void inicializar( int UI_window_width, int UI_window_height );
    void redimensionar( int newWidth, int newHeight ) ;

    // Dibujar
    void dibujar() ;

    // Interacción con la escena
    bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
    void teclaEspecial( int Tecla1, int x, int y );

	 void animar();
};
#endif
