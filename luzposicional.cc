#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f pos, GLenum idLuzOpenGL, Tupla4f cAmb, Tupla4f cEsp, Tupla4f cDif){
	
	posicion = {pos(0), pos(1), pos(2), 1};
	colorAmbiente = cAmb;
	colorDifuso = cDif;
	colorEspecular = cEsp;
	id = idLuzOpenGL;
}

void LuzPosicional::animar(){
	
	
	if(posicion(0)>300)
		suma_pos_x *=-1;
	if(posicion(0)<-300)
		suma_pos_x *=-1;
		
	posicion(0)+=suma_pos_x;
}
	
