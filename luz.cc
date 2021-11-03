#include "luz.h"

void Luz::activar(){
	
	if(luz_activa){
		glLightfv(id, GL_POSITION, posicion);
		glLightfv(id, GL_AMBIENT, colorAmbiente );
		glLightfv(id, GL_SPECULAR, colorEspecular );
		glLightfv(id, GL_DIFFUSE, colorDifuso );
	}
}

void Luz::setActivacion(const bool act){
	
	if(act)
		glEnable(id);
	else
		glDisable(id);
	
	luz_activa = act;
}

bool Luz::getLuzActivada(){
	return luz_activa;
}





