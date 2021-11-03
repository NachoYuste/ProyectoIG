#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla2f dir, GLenum idLuzOpenGL, Tupla4f cAmb, Tupla4f cEsp, Tupla4f cDif)
{
	posicion = {dir(0), dir(1), 0, 0};
	id = idLuzOpenGL;
	colorAmbiente = cAmb;
	colorDifuso = cDif;
	colorEspecular = cEsp;
	
}

void LuzDireccional::variarAnguloAlpha(float incremento){
	
	alpha = alpha+incremento;
	alpha = alpha*(M_PI*2);
	
	//Calcular las coordenadas cartesianas a partir de las esféricas con el nuevo valor de alpha
	
	posicion(0) = sin(alpha) * cos(beta) * sqrt(posicion.lengthSq());
	posicion(1) = sin(alpha) * sqrt(posicion.lengthSq());
	posicion(2) = sin(alpha) * sin(beta) * sqrt(posicion.lengthSq());
}

void LuzDireccional::variarAnguloBeta(float incremento){
	
	beta = beta + incremento;
	beta = beta*(M_PI*2);
	
	//Calcular las coordenadas cartesianas a partir de las esféricas con el nuevo valor de beta
	
	posicion(0) = sin(alpha) * cos(beta) * sqrt(posicion.lengthSq());
	posicion(1) = sin(alpha) * sqrt(posicion.lengthSq());
	posicion(2) = sin(alpha) * sin(beta) * sqrt(posicion.lengthSq());	
}



