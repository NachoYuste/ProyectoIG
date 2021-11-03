#include "cabeza.h"

Cabeza::Cabeza(){
	cuello = new Cilindro(10,40,1,1);
	cab = new Esfera(10,40,1);
}

void Cabeza::draw(set<modo_vis> modos, bool modo_dif){
	
	glPushMatrix();
		glTranslatef(0,14,0);
		glScalef(10,10,10);
		cab->draw(modos,false);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,3,0);
		glScalef(4,6,4);
		cuello->draw(modos, modo_dif);
	glPopMatrix();
	
}

void Cabeza::setMaterial(Material mat){
	cab->setMaterial(mat);
	cuello->setMaterial(mat);
}


