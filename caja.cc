#include "caja.h"

Caja::Caja(){
	caja = new Cubo(1);
	tapa = new Cubo(1);
	base_gir = new Cilindro(20,80,1,1);
	
	alfa = 0;
}

void Caja::draw(set<modo_vis> modos, bool modo_dif){
	glPushMatrix();
		
		//Caja
		glPushMatrix();
			glScalef(400,400,400);
			caja->draw(modos,modo_dif);
		glPopMatrix();
		
		//Tapa
		glPushMatrix();
			glTranslatef(0,415,0);
			glRotatef(alfa,1,0,0);
			glScalef(400,30,400);
			tapa->draw(modos,modo_dif);
		glPopMatrix();
		
		//Base
		

	glPopMatrix();
	
	
	
}
