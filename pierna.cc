#include "pierna.h"

Pierna::Pierna(){
	muslo = new Cilindro(10,20,1,1);
	cadera = new Esfera(10,20,1);
	pie = new Pie();	
	alfa = 360;
}

Pierna::Pie::Pie(){
	pie = new Cubo(1);
	pierna = new Cilindro(10,20,1,1);
	rodilla = new Esfera(10,20,1);
}

void Pierna::Pie::draw(set<modo_vis> modos, bool modo_dif){
	glPushMatrix();
		
		//Pie
		glPushMatrix();
			glTranslatef(1,-18,0);
			glScalef(8,6,6);
			pie->draw(modos,modo_dif);
		glPopMatrix();
		
		//Pierna
		glPushMatrix();
			glTranslatef(0,-9,0);
			glScalef(3,16,3);
			pierna->draw(modos,modo_dif);
		glPopMatrix();
		
		//Rodilla
		glPushMatrix();
			glScalef(3,3,3);
			rodilla->draw(modos,modo_dif);
		glPopMatrix();
		
	glPopMatrix();
}

void Pierna::draw(set<modo_vis> modos, bool modo_dif){
	
	//Muslo
	glPushMatrix();
		glTranslatef(0,-6.5,0);
		glScalef(3,12,3);
		muslo->draw(modos,modo_dif);
	glPopMatrix();
	
	//Cadera
	glPushMatrix();
		glScalef(3,3,3);
		cadera->draw(modos,modo_dif);
	glPopMatrix();
	
	//Pie
	glPushMatrix();
		glTranslatef(0,-15,0);
		glRotatef(alfa,0,0,1);
		pie->draw(modos,modo_dif);
	glPopMatrix();
}

void Pierna::elevaRodilla(float a){
	alfa -= a;
	

	if(alfa<270) alfa=270;
	if(alfa>360)	alfa=360;
}

void Pierna::setMaterial(Material mat){
	muslo->setMaterial(mat);
	cadera->setMaterial(mat);
	pie->setMaterial(mat);
}
void Pierna::Pie::setMaterial(Material mat){
	pie->setMaterial(mat);
	rodilla->setMaterial(mat);
	pierna->setMaterial(mat);
}



